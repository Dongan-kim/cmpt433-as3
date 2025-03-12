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
// #define OUTX_H 0x29
// #define OUTY_L 0x2A
// #define OUTY_H 0x2B
// #define OUTZ_L 0x2C
// #define OUTZ_H 0x2D

// Thresholds for detecting air drumming movement
#define THRESHOLD_X 12000 
#define THRESHOLD_Y 8000
#define THRESHOLD_Z 12000
#define DEAD_ZONE 20000  // Ignore small variations below this value

#define DEBOUNCE_TIME_X 400 // Longer debounce time for X-axis
#define DEBOUNCE_TIME_Y 300 // Medium debounce time for Y-axis
#define DEBOUNCE_TIME_Z 350 // Shorter debounce time for Z-axis

static int i2c_fd;
static pthread_t accelThread;
static int running = 1;

static int read_accel_data(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t buffer[6];
    uint8_t reg = OUTX_L;

    if (write(i2c_fd, &reg, 1) != 1) {
        perror("Failed to write register address");
        return -1;
    }
    if (read(i2c_fd, buffer, 6) != 6) {
        perror("Failed to read accelerometer data");
        return -1;
    }

    *x = (int16_t)((buffer[1] << 8) | buffer[0]);
    *y = (int16_t)((buffer[3] << 8) | buffer[2]);
    *z = (int16_t)((buffer[5] << 8) | buffer[4]);

    return 0;  
}

// int16_t read_accel_axis(uint8_t reg_low, uint8_t reg_high) {
//     int16_t raw = (int16_t)((i2c_read_register(reg_high) << 8) | i2c_read_register(reg_low));
//     return raw; 
// }

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

    uint8_t reg = WHO_AM_I_REG;
    uint8_t who_am_i;
    
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("Failed to write WHO_AM_I register address");
        close(i2c_fd);
        return;
    }
    if (read(i2c_fd, &who_am_i, 1) != 1) {
        perror("Failed to read WHO_AM_I register");
        close(i2c_fd);
        return;
    }

    if (who_am_i != 0x44) {
        printf("Accelerometer not detected! WHO_AM_I = 0x%X\n", who_am_i);
        close(i2c_fd);
        return;
    }

    // Configure accelerometer
    uint8_t ctrl1 = 0x60; // High-performance mode, 200 Hz
    uint8_t ctrl6 = 0x00; // ±2g full-scale range
    write(i2c_fd, (uint8_t[]){CTRL1_REG, ctrl1}, 2);
    write(i2c_fd, (uint8_t[]){CTRL6_REG, ctrl6}, 2);

    pthread_create(&accelThread, NULL, accelerometer_listener, NULL);
    pthread_detach(accelThread);
}

// Thread function to detect air-drumming
void *accelerometer_listener(void *arg) {
    (void)arg;

    long lastXTime = 0, lastYTime = 0, lastZTime = 0;
    int16_t prevX = 0, prevY = 0, prevZ = 0;

    // **Ensure accelerometer is working**
    if (read_accel_data(&prevX, &prevY, &prevZ) == -1) {
        perror("Failed to initialize accelerometer readings");
        return NULL;
    }

    while (running) {
        if (i2c_fd == -1) {
            usleep(100000);
            continue;
        }

        int16_t x, y, z;
        if (read_accel_data(&x, &y, &z) == -1) {
            continue;
        }

        long currentTime = periodTimer_getCurrentTimeMs();

        float xG = x / 16384.0;
        float yG = y / 16384.0;
        float zG = z / 16384.0;

        int16_t deltaX = abs(x - prevX);
        int16_t deltaY = abs(y - prevY);
        int16_t deltaZ = abs(z - prevZ);

        // **Apply Debounce & Dead Zones**
        if (deltaX > THRESHOLD_X && deltaX > DEAD_ZONE && (currentTime - lastXTime > DEBOUNCE_TIME_X)) {
            printf("🥁 Air-Drum X (Snare)");
            printf("🛠️ Raw: X: %d Y: %d Z: %d | 📏 G-Force: X: %.2fg Y: %.2fg Z: %.2fg\n", x, y, z, xG, yG, zG);
            playSnare();
            lastXTime = currentTime;
            prevX = x; 
        }

        if (deltaY > THRESHOLD_Y && deltaY > DEAD_ZONE && (currentTime - lastYTime > DEBOUNCE_TIME_Y)) {
            printf("🥁 Air-Drum Y (HiHat)");
            printf("🛠️ Raw: X: %d Y: %d Z: %d | 📏 G-Force: X: %.2fg Y: %.2fg Z: %.2fg\n", x, y, z, xG, yG, zG);
            playHiHat();
            lastYTime = currentTime;
            prevY = y;  
        }

        if (deltaZ > THRESHOLD_Z && deltaZ > DEAD_ZONE && (currentTime - lastZTime > DEBOUNCE_TIME_Z)) {
            printf("🥁 Air-Drum Z (Bass Drum)");
            printf("🛠️ Raw: X: %d Y: %d Z: %d | 📏 G-Force: X: %.2fg Y: %.2fg Z: %.2fg\n", x, y, z, xG, yG, zG);
            playBassDrum();
            lastZTime = currentTime;
            prevZ = z;  
        }

        usleep(10000); // **100Hz polling rate**
    }
    return NULL;
}

// Cleanup function
void accelerometer_cleanup() {
    running = 0;
    close(i2c_fd);
}