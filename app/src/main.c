#include "audioMixer.h"
#include "beatbox.h"
#include "hal/joystick.h"
#include <hal/lcd_display.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <gpiod.h>
#include <signal.h>
#include <periodTimer.h>

static volatile int keepRunning = 1;

static int currentScreen = 1;

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
    lcd_display_init();
    periodTimer_init();

    printf("Press Ctrl+C to exit.\n");

    // Explicitly set mode and BPM to ensure beats play
    setMode(1);  // Rock mode
    setBPM(120); // Default BPM

    // Main loop
    while (keepRunning) { 
        int mode = getMode();
        int bpm = getBPM();
        printf("Current Mode: %d | BPM: %d\n", mode, bpm);

        // periodTimer_start(PERIOD_TIMER_AUDIO);
        // BeatBox_process();
        // periodTimer_stop(PERIOD_TIMER_AUDIO);

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

        if (joystick_pressed() == 1) {
            printf("🕹️ Joystick Pressed! Cycling Screens...\n");
            currentScreen = (currentScreen % 3) + 1;
            lcd_display_screen(currentScreen);
            usleep(100000); // Simple debounce (100ms)
        }

        int volume = AudioMixer_getVolume(); 
        if (currentScreen == 1) {
            lcd_display_status_screen(getMode(), bpm, volume);
        } else if (currentScreen == 2) {
            lcd_display_timing_screen("Audio Timing", 
                                       periodTimer_getMinTime(PERIOD_TIMER_AUDIO),
                                       periodTimer_getMaxTime(PERIOD_TIMER_AUDIO),
                                       periodTimer_getAvgTime(PERIOD_TIMER_AUDIO));
        } else if (currentScreen == 3) {
            periodTimer_start(PERIOD_TIMER_ACCEL);
            // Accel processing should go here (Placeholder)
            periodTimer_stop(PERIOD_TIMER_ACCEL);
            
            lcd_display_timing_screen("Accel. Timing", 
                                       periodTimer_getMinTime(PERIOD_TIMER_ACCEL),
                                       periodTimer_getMaxTime(PERIOD_TIMER_ACCEL),
                                       periodTimer_getAvgTime(PERIOD_TIMER_ACCEL));
        }

        sleep(1);
    }
    
    // Cleanup
    joystick_cleanup();
    BeatBox_cleanup();
    AudioMixer_cleanup();
    lcd_display_cleanup();
    periodTimer_cleanup();
    
    printf("Exited Cleanly.\n");
    return 0;
}