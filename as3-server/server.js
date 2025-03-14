"use strict";

// Server for HTTP and loading other server modules
// Install modules:
//   $ npm install
//
// Launch server with:
//   $ node server.js
// 

var PORT_NUMBER = 8088;

var http = require('http');
var fs   = require('fs');
var path = require('path');
var mime = require('mime');

var socketio = require('socket.io'); // <-- Add WebSockets
var dgram = require('dgram'); // <-- Add UDP for shutdown signal


/* 
 * Create the static web server
 */
var server = http.createServer(function(request, response) {
	var filePath = false;
	
	if (request.url == '/') {
		filePath = 'public/index.html';
	} else {
		filePath = 'public' + request.url;
	}
	
	var absPath = './' + filePath;
	serveStatic(response, absPath);
});

server.listen(PORT_NUMBER, function() {
	console.log("Server listeneing on port " + PORT_NUMBER);
});

function serveStatic(response, absPath) {
	fs.exists(absPath, function(exists) {
		if (exists) {
			fs.readFile(absPath, function(err, data) {
				if (err) {
					send404(response);
				} else {
					sendFile(response, absPath, data);
				}
			});
		} else {
			send404(response);
		}
	});
}

function send404(response) {
	response.writeHead(404, {'Content-Type': 'text/plain'});
	response.write('Error 404: resource not found.');
	response.end();
}

function sendFile(response, filePath, fileContents) {
	response.writeHead(
			200,
			{"content-type": mime.lookup(path.basename(filePath))}
		);
	response.end(fileContents);
}


var io = socketio(server);
var procServer = require('./lib/beatbox_server');
procServer.listen(server);

/*
 * Create the beatbox server to listen for the websocket
 */

const shutdownSocket = dgram.createSocket('udp4');

shutdownSocket.on('message', (msg, rinfo) => {
    if (msg.toString().trim() === "shutdown") {
        console.log("Stopping Node.js server...");

        // Ensure the shutdown order is correct
        shutdownSocket.close(() => console.log("Shutdown socket closed."));
        
        if (io) {
            io.close(() => console.log("WebSockets closed."));
        }

        server.close(() => {
            console.log("HTTP server closed.");
            
            // **Force Exit After 1 Second (Ensures All Resources Are Freed)**
            setTimeout(() => {
                console.log("exit");
                process.exit(0);
            }, 1000);
        });

        // **Failsafe: Force Exit After 3 Seconds If Stuck**
        setTimeout(() => {
            console.log("exit");
            process.exit(1);
        }, 3000);
    }
});

// Listen for shutdown signal on UDP port 8089
shutdownSocket.bind(8089, () => {
    console.log("Shutdown listener running on port 8089");
});