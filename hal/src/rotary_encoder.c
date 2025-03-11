#define _POSIX_C_SOURCE 199309L  // Enable CLOCK_MONOTONIC
#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <pthread.h>
#include <gpiod.h>
#include <time.h>
#include <unistd.h>
#include "hal/rotary_encoder.h"
#include "beatbox.h"
#include "audioMixer.h"


#define GPIO_CHIP "/dev/gpiochip2"
#define GPIO_A 7  // GPIO16 -> A signal
#define GPIO_B 8  // GPIO17 -> B signal
#define DEBOUNCE_DELAY 500
#define MIN_BPM 40
#define MAX_BPM 300

static struct gpiod_chip *chip;
static struct gpiod_line *lineA, *lineB;
static pthread_mutex_t encoderMutex = PTHREAD_MUTEX_INITIALIZER;
static int encoderValue = 120;  // Default bpm
static int lastA = 0, lastB = 0;
static int lastState = 0;  // Stores previous state to prevent counting half steps
static int halfStepDetected = 0;  // Flags if halfway movement was detected
static long lastTimeUs = 0; // Last timestamp in microseconds

//Helper function: Get current time in microseconds
static long getCurrentTimeUs() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec * 1000000) + (now.tv_nsec / 1000);
}

void RotaryEncoder_init(void) {
    chip = gpiod_chip_open(GPIO_CHIP);
    if (!chip) {
        perror("Failed to open GPIO chip");
        return;
    }

    lineA = gpiod_chip_get_line(chip, GPIO_A);
    lineB = gpiod_chip_get_line(chip, GPIO_B);
    if (!lineA || !lineB) {
        perror("Failed to get GPIO lines for encoder");
        return;
    }

    gpiod_line_request_input(lineA, "encoderA");
    gpiod_line_request_input(lineB, "encoderB");

    lastA = gpiod_line_get_value(lineA);
    lastB = gpiod_line_get_value(lineB);
    lastState = (lastA << 1) | lastB;

    pthread_t encoderThreadId;
    if (pthread_create(&encoderThreadId, NULL, RotaryEncoder_listen, NULL) != 0) {
        perror("Failed to create Rotary Encoder thread");
    }
    pthread_detach(encoderThreadId);
}

int RotaryEncoder_getRotation(void) {
    int newA = gpiod_line_get_value(lineA);
    int newB = gpiod_line_get_value(lineB);
    long currentTime = getCurrentTimeUs();
    int currentState = (newA << 1) | newB;  // Encode state as 2-bit value


    // Debounce check
    if ((currentTime - lastTimeUs) < DEBOUNCE_DELAY) {
        return 0;
    }

    int count = 0;
    
    
    //Clockwise rotation
    if (lastState == 3 && currentState == 1) {  // A falls first
        halfStepDetected = 1;
    }
    else if (halfStepDetected == 1 && lastState == 1 && currentState == 0) {  // B falls
        halfStepDetected = 2;
    }
    else if (halfStepDetected == 2 && lastState == 0 && currentState == 2) {  // A rises
        halfStepDetected = 3;
    }
    else if (halfStepDetected == 3 && lastState == 2 && currentState == 3) {  // B rises
        count = 5;
        halfStepDetected = 0;
    }
    //Counterclockwise rotation
    else if (lastState ==2 && currentState ==0) {  // B falls first
        halfStepDetected = -1;
    }
    else if (halfStepDetected == -1 && lastState == 0 && currentState == 1) {  // A falls
        halfStepDetected = -2;
    }
    else if (halfStepDetected == -2 && lastState == 1 && currentState == 3) {  // B rises
        halfStepDetected = -3;
    }
    else if (halfStepDetected == -3 && lastState == 3 && currentState == 2) {  // A rises
        count = -5;  
        halfStepDetected = 0;
    }


    lastState = currentState;
    lastTimeUs = currentTime;

    return count;
}

//Thread function to track rotary encoder rotation
void *RotaryEncoder_listen(void *arg) {
    (void)arg;
    while (1) {
        int rotation = RotaryEncoder_getRotation();


        pthread_mutex_lock(&encoderMutex);
        if (rotation != 0) {
            encoderValue += rotation;
            if (encoderValue < MIN_BPM) encoderValue = MIN_BPM;
            if (encoderValue > MAX_BPM) encoderValue = MAX_BPM;
        }

        pthread_mutex_unlock(&encoderMutex);
    }
    return NULL;
}

// Get current encoder value
int RotaryEncoder_getValue(void) {
    pthread_mutex_lock(&encoderMutex);
    int value = encoderValue;
    pthread_mutex_unlock(&encoderMutex);
    return value;
}

void RotaryEncoder_cleanup(void) {
    gpiod_line_release(lineA);
    gpiod_line_release(lineB);
    gpiod_chip_close(chip);
}