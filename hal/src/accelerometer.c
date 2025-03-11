#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "audioMixer.h"
#include "beatbox.h"
#include "hal/accelerometer.h"
#include "periodTimer.h"

#define I2C_BUS "/dev/i2c-1"
#define ACCEL_ADDR 0x19
#define WHO_AM_I_REG 0x0F
#define CTRL1_REG 0x20
#define CTRL6_REG 0x25
#define OUTX_L 0x28
#define OUTX_H 0x29
#define OUTY_L 0x2A
#define OUTY_H 0x2B
#define OUTZ_L 0x2C
#define OUTZ_H 0x2D

// Thresholds for detecting air drumming movement
#define THRESHOLD_X 5000   // Sensitivity for left/right motion
#define THRESHOLD_Y 5000   // Sensitivity for forward/backward motion
#define THRESHOLD_Z 7000   // Sensitivity for up/down motion
#define DEBOUNCE_TIME 200  // Debounce time in milliseconds

static int i2c_fd;
static pthread_t accelThread;
static int running = 1;

// Helper function: Read a register
static uint8_t i2c_read_register(uint8_t reg) {
    uint8_t value;
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("Failed to write register address");
        return -1;
    }
    if (read(i2c_fd, &value, 1) != 1) {
        perror("Failed to read register value");
        return -1;
    }
    return value;
}

// Helper function: Read acceleration values
int16_t read_accel_axis(uint8_t reg_low, uint8_t reg_high) {
    int16_t value = (i2c_read_register(reg_high) << 8) | i2c_read_register(reg_low);
    return value;
}

// Function to initialize accelerometer
void accelerometer_init() {
    i2c_fd = open(I2C_BUS, O_RDWR);
    if (i2c_fd < 0) {
        perror("Failed to open I2C bus");
        return;
    }

    if (ioctl(i2c_fd, I2C_SLAVE, ACCEL_ADDR) < 0) {
        perror("Failed to set I2C address");
        close(i2c_fd);
        return;
    }

    // Verify WHO_AM_I
    uint8_t who_am_i = i2c_read_register(WHO_AM_I_REG);
    if (who_am_i != 0x44) {
        printf("Accelerometer not detected! WHO_AM_I = 0x%X\n", who_am_i);
        close(i2c_fd);
        return;
    }

    // Set accelerometer configuration
    uint8_t ctrl1 = 0x60; // High-performance mode, 200 Hz
    uint8_t ctrl6 = 0x00; // ±2g full-scale range
    write(i2c_fd, (uint8_t[]){CTRL1_REG, ctrl1}, 2);
    write(i2c_fd, (uint8_t[]){CTRL6_REG, ctrl6}, 2);

    printf("Accelerometer initialized!\n");
}

// Thread function to detect air-drumming
void *accelerometer_listener(void *arg) {
    (void)arg;
    int16_t prevX = 0, prevY = 0, prevZ = 0;
    long lastXTime = 0, lastYTime = 0, lastZTime = 0;

    while (running) {
        int16_t x = read_accel_axis(OUTX_L, OUTX_H);
        int16_t y = read_accel_axis(OUTY_L, OUTY_H);
        int16_t z = read_accel_axis(OUTZ_L, OUTZ_H);

        long currentTime = periodTimer_getCurrentTimeMs();

        // Detect motion and debounce it
        if (abs(x - prevX) > THRESHOLD_X && currentTime - lastXTime > DEBOUNCE_TIME) {
            printf("🥁 Air-Drum X (Snare)\n");
            playSnare();
            lastXTime = currentTime;
        }

        if (abs(y - prevY) > THRESHOLD_Y && currentTime - lastYTime > DEBOUNCE_TIME) {
            printf("🥁 Air-Drum Y (HiHat)\n");
            playHiHat();
            lastYTime = currentTime;
        }

        if (abs(z - prevZ) > THRESHOLD_Z && currentTime - lastZTime > DEBOUNCE_TIME) {
            printf("🥁 Air-Drum Z (Bass Drum)\n");
            playBassDrum();
            lastZTime = currentTime;
        }

        prevX = x;
        prevY = y;
        prevZ = z;

        usleep(10000); // Sleep 10ms (100Hz polling)
    }
    return NULL;
}

// Start accelerometer thread
void accelerometer_start() {
    pthread_create(&accelThread, NULL, accelerometer_listener, NULL);
    pthread_detach(accelThread);
}

// Cleanup function
void accelerometer_cleanup() {
    running = 0;
    close(i2c_fd);
}