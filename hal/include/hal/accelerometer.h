#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

// Function prototypes
void accelerometer_init(void);
void accelerometer_start(void);
void accelerometer_cleanup(void);
int16_t read_accel_axis(uint8_t reg_low, uint8_t reg_high);
void *accelerometer_listener(void *arg);

#endif // ACCELEROMETER_H