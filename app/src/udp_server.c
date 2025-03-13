#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "audioMixer.h"
#include "beatbox.h"
#include "udp_server.h"

#define PORT 12345
#define BUFFER_SIZE 1024

static int sockfd = -1;

void processCommand(char *command);

void* udp_server_main(void* arg) {
    (void)arg;
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addrLen = sizeof(clientAddr);

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

    printf("🎵 UDP BeatBox Server started on port %d\n", PORT);

    while (1) {
        // Receive data from client
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addrLen);
        if (n > 0) {
            buffer[n] = '\0'; // Null-terminate received string
            printf("📩 Received: %s\n", buffer);
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

    // Extract command and optional value
    if (sscanf(command, "%s %d", cmd, &value) >= 1) {
        if (strcmp(cmd, "mode") == 0) {
            setMode(value);
            printf("🎵 Mode changed to %d\n", value);
        } else if (strcmp(cmd, "volume") == 0) {
            AudioMixer_setVolume(value);
            printf("🔊 Volume set to %d\n", value);
        } else if (strcmp(cmd, "tempo") == 0) {
            setBPM(value);
            printf("⏱️ Tempo set to %d BPM\n", value);
        } else if (strcmp(cmd, "play") == 0) {
            if (value == 0) playBassDrum();
            else if (value == 1) playHiHat();
            else if (value == 2) playSnare();
            printf("🥁 Played sound %d\n", value);
        } else if (strcmp(cmd, "stop") == 0) {
            printf("🛑 Shutting down...\n");
            exit(0);
        } else {
            printf("⚠️ Unknown command: %s\n", cmd);
        }
    }
}

// Cleanup function to close the socket
void udp_server_cleanup(void) {
    if (sockfd != -1) {
        printf("🔌 Closing UDP server...\n");
        close(sockfd);
        sockfd = -1;
    }
}