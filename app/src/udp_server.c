#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "audioMixer.h"
#include "beatbox.h"
#include "udp_server.h"
#include "hal/accelerometer.h"
#include "hal/joystick_press.h"
#include "hal/joystick.h"
#include "hal/lcd_display.h"
#include "hal/rotary_encoder.h"
#include "periodTimer.h"

#define PORT 12345
#define BUFFER_SIZE 1024

extern volatile int keepRunning;

static int sockfd = -1;  // Global UDP socket
static struct sockaddr_in clientAddr; // Store client info for replies
static socklen_t addrLen;  // Store client address length

void processCommand(char *command);

void* udp_server_main(void* arg) {
    (void)arg;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    addrLen = sizeof(clientAddr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("UDP Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    // Configure server settings
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("UDP Socket bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP BeatBox Server started on port %d\n", PORT);

    while (1) {
        // Receive data from client
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addrLen);
        if (n > 0) {
            buffer[n] = '\0'; // Null-terminate received string
            processCommand(buffer);
        }
    }

    close(sockfd);
    return NULL;
}

// Function to process received commands
void processCommand(char *command) {
    char cmd[BUFFER_SIZE];
    int value;
    int numScanned;

    // Extract command and optional value
    numScanned = sscanf(command, "%s %d", cmd, &value);

    if (numScanned < 1) {
        printf("ERROR: Invalid command format.\n");
        return;
    }


    if (strcmp(cmd, "mode") == 0) {
        if (numScanned == 2 && value >= 0 && value <= 2) {
            setMode(value);
            printf("Mode changed to %d\n", value);
            char response[BUFFER_SIZE];
            sprintf(response, "%d", value);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } else if (numScanned == 1) {  // Request current mode
            int currentMode = getMode();
            char response[BUFFER_SIZE];
            sprintf(response, "%d", currentMode);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } else {
            printf("ERROR: Mode must be between 0 and 2.\n");
        }
    }

    else if (strcmp(cmd, "volume") == 0) {
        if (numScanned == 2 && value >= 0 && value <= 100) {
            AudioMixer_setVolume(value);
            printf("Volume set to %d\n", value);
            char response[BUFFER_SIZE];
            sprintf(response, "%d", value);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } else if (numScanned == 1) {  // Request current volume
            int currentVolume = AudioMixer_getVolume();
            char response[BUFFER_SIZE];
            sprintf(response, "%d", currentVolume);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } else {
            printf("ERROR: Volume must be between 0 and 100.\n");
        }
    }

    else if (strcmp(cmd, "tempo") == 0) {
        if (numScanned == 2 && value >= 40 && value <= 300) {
            setBPM(value);
            printf("Tempo set to %d BPM\n", value);
            char response[BUFFER_SIZE];
            sprintf(response, "%d", value);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } else if (numScanned == 1) {  // Request current tempo
            int currentBPM = getBPM();
            char response[BUFFER_SIZE];
            sprintf(response, "%d", currentBPM);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } else {
            printf("ERROR: Tempo must be between 40 and 300 BPM.\n");
        }
    }

    else if (strcmp(cmd, "play") == 0) {
        char response[BUFFER_SIZE];
    
        if (numScanned == 2 && value >= 0 && value <= 2) {
            if (value == 0) {
                playBassDrum();
                sprintf(response, "Played Bass Drum");
            } else if (value == 1) {
                playHiHat();
                sprintf(response, "Played Hi-Hat");
            } else if (value == 2) {
                playSnare();
                sprintf(response, "Played Snare");
            }
    
            printf("%s\n", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        } 
        else {
            sprintf(response, "ERROR: Invalid sound selection. Use 0 (Bass), 1 (HiHat), or 2 (Snare).");
            printf("%s\n", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);
        }
    }

    else if (strcmp(cmd, "stop") == 0) {
        // Send confirmation to the web UI before shutting down
        char response[] = "Shutdown initiated...";
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&clientAddr, addrLen);

        int shutdownSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (shutdownSocket >= 0) {
            struct sockaddr_in nodeServerAddr;
            memset(&nodeServerAddr, 0, sizeof(nodeServerAddr));
            nodeServerAddr.sin_family = AF_INET;
            nodeServerAddr.sin_port = htons(8089);
            inet_pton(AF_INET, "127.0.0.1", &nodeServerAddr.sin_addr);
        
            char shutdownMessage[] = "shutdown";
            
            int retries = 3;
            for (int i = 0; i < retries; i++) {
                ssize_t sent = sendto(shutdownSocket, shutdownMessage, strlen(shutdownMessage), 0,
                                      (struct sockaddr *)&nodeServerAddr, sizeof(nodeServerAddr));
                if (sent < 0) {
                    perror("❌ UDP sendto failed");
                } else {
                    printf("✅ Sent shutdown signal to Node.js server.\n");
                    break;
                }
                sleep(1);  // Wait 1 sec before retry
            }
        
            close(shutdownSocket);
        }

        keepRunning = 0;
        //cleanup_resources();

        printf("All resources cleaned up. Exiting now.\n");
        //exit(0);
    }

    else {
        printf("ERROR: Unknown command: %s\n", cmd);
    }
}

// Cleanup function to close the socket
void udp_server_cleanup(void) {
    if (sockfd != -1) {
        printf("Closing UDP server...\n");
        close(sockfd);
        sockfd = -1;
    }
}