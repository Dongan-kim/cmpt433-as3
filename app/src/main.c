#define _POSIX_C_SOURCE 200809L
#include "audioMixer.h"
#include "beatbox.h"
#include "hal/joystick.h"
#include "hal/joystick_press.h"
#include "hal/lcd_display.h"
#include "hal/rotary_encoder.h"
#include "hal/accelerometer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <gpiod.h>
#include <signal.h>
#include <periodTimer.h>



static volatile int keepRunning = 1;
static long lastPrintTime = 0;

long getCurrentTimeMs() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

void handleSigint(int sig) {
    (void)sig;
    printf("\nShutting down BeatBox...\n");
    keepRunning = 0;
}

int main() {
    // Register signal handler to gracefully exit on Ctrl+C
    signal(SIGINT, handleSigint);
    printf("Playing BeatBox\n");
    AudioMixer_init();
    BeatBox_init();  // Starts beatbox thread
    joystick_init();
    joystick_press_init();
    lcd_display_init();
    RotaryEncoder_init();
    accelerometer_init();
    periodTimer_init();

    printf("Press Ctrl+C to exit.\n");

    // Explicitly set mode and BPM to ensure beats play
    setMode(1);  // Rock mode
    setBPM(120); // Default BPM
    lcd_display_screen(1);

    // Main loop
    while (keepRunning) { 
        long currentTime = getCurrentTimeMs();
        if (currentTime - lastPrintTime >= 1000) {
            lastPrintTime = currentTime;
            int mode = getMode();
            if(mode == 0){
                accelerometer_start();
            }
            int bpm = getBPM();
            int volume = AudioMixer_getVolume();
            printf("Current Mode: %d | BPM: %d | Volume: %d\n", mode, bpm, volume);
            lcd_display_screen(getScreen());

        
            int dir = joystick_get_dir();
            int cur_vol = AudioMixer_getVolume(); 
            if(dir == 0){
                AudioMixer_setVolume(cur_vol += 5);   //volume up
            }else if(dir == 1){
                AudioMixer_setVolume(cur_vol -= 5);   //volume down
            }
        }

        int new_bpm = RotaryEncoder_getValue();
        if(new_bpm != getBPM()){
            setBPM(new_bpm);
        }

    }
    
    // Cleanup
    joystick_cleanup();
    joystick_press_cleanup();
    BeatBox_cleanup();
    AudioMixer_cleanup();
    lcd_display_cleanup();
    RotaryEncoder_cleanup();
    accelerometer_cleanup();
    periodTimer_cleanup();
    
    printf("Exited Cleanly.\n");
    return 0;
}