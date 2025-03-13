#ifndef UDP_SERVER_H
#define UDP_SERVER_H

// Function to start the UDP server (runs in a separate thread)
void* udp_server_main(void* arg);
void udp_server_cleanup(void);

#endif // UDP_SERVER_H