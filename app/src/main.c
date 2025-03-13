#define _POSIX_C_SOURCE 200809L
#include "audioMixer.h"
#include "beatbox.h"
#include "udp_server.h"
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
static pthread_t udpThreadId;

void* udp_server_thread(void* arg) {
    (void)arg;
    udp_server_main(NULL);
    return NULL;
}


long getCurrentTimeMs() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

void handleSigint(int sig) {
    (void)sig;
    printf("\nShutting down BeatBox...\n");
    keepRunning = 0;
    udp_server_cleanup();
}

int main() {
    // Register signal handler to gracefully exit on Ctrl+C
    signal(SIGINT, handleSigint);
    printf("Playing BeatBox\n");
    Period_init();
    AudioMixer_init();
    BeatBox_init();  // Starts beatbox thread
    joystick_init();
    joystick_press_init();
    lcd_display_init();
    RotaryEncoder_init();
    accelerometer_init();

    pthread_create(&udpThreadId, NULL, udp_server_thread, NULL);
    pthread_detach(udpThreadId);

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
            int bpm = getBPM();
            int volume = AudioMixer_getVolume();

            // Capture event timing data
            Period_statistics_t audioStats;
            Period_statistics_t accelStats;

            Period_getStatisticsAndClear(PERIOD_EVENT_AUDIO_BUFFER_FILL, &audioStats);
            Period_getStatisticsAndClear(PERIOD_EVENT_ACCELEROMETER_SAMPLE, &accelStats);

            // Print system status
            printf("M%d %dbpm vol:%d Audio[%.3f, %.3f] avg %.3f/%d Accel[%.3f, %.3f] avg %.3f/%d\n",
                   mode, bpm, volume,
                   audioStats.minPeriodInMs, audioStats.maxPeriodInMs, audioStats.avgPeriodInMs, audioStats.numSamples,
                   accelStats.minPeriodInMs, accelStats.maxPeriodInMs, accelStats.avgPeriodInMs, accelStats.numSamples);

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
    Period_cleanup();
    
    printf("Exited Cleanly.\n");
    return 0;
}