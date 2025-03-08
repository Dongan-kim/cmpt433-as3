#include "audioMixer.h"
#include "beatbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

static volatile int keepRunning = 1;

void handleSigint(int sig) {
    (void)sig;
    printf("\nShutting down BeatBox...\n");
    keepRunning = 0;
}

int main() {
    // Register signal handler to gracefully exit on Ctrl+C
    signal(SIGINT, handleSigint);
    
    printf("Initializing Audio Mixer and BeatBox...\n");
    AudioMixer_init();
    BeatBox_init();  // Starts beatbox thread

    printf("Press Ctrl+C to exit.\n");

    // Explicitly set mode and BPM to ensure beats play
    setMode(1);  // Rock mode
    setBPM(120); // Default BPM

    // Main loop
    while (keepRunning) {
        pthread_mutex_lock(&beatMutex); 
        int mode = currentMode;
        pthread_mutex_unlock(&beatMutex);

        int bpm = getBPM();

        printf("Current Mode: %d | BPM: %d\n", mode, bpm);
        sleep(2);
    }
    
    // Cleanup
    BeatBox_cleanup();
    AudioMixer_cleanup();
    
    printf("Exited Cleanly.\n");
    return 0;
}