#include "audioMixer.h"
#include "beatbox.h"
#include "hal/joystick.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <gpiod.h>
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
    joystick_init();

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

        int dir = joystick_get_dir();
        int cur_vol = AudioMixer_getVolume(); 
        if(dir == 0){
            AudioMixer_setVolume(cur_vol += 5);   //volume up
            int tmp = AudioMixer_getVolume();
            printf("current volume: %d\n", tmp);
        }else if(dir == 1){
            AudioMixer_setVolume(cur_vol -= 5);   //volume down
            int tmp = AudioMixer_getVolume();
            printf("current volume: %d\n", tmp);
        }

        if (joystick_pressed()) {
            printf("🕹️ Joystick Pressed! Cycling Screens...\n");
            //currentScreen = (currentScreen % 3) + 1;
            //lcd_display_screen(currentScreen);
            //usleep(300000); // Simple debounce (300ms)
        }

        sleep(1);
    }
    
    // Cleanup
    joystick_cleanup();
    BeatBox_cleanup();
    AudioMixer_cleanup();
    
    printf("Exited Cleanly.\n");
    return 0;
}