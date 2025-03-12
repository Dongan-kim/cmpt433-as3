#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

// Function prototypes
void accelerometer_init(void);
void accelerometer_cleanup(void);
//static int read_accel_data(int16_t *x, int16_t *y, int16_t *z);
//int16_t read_accel_axis(uint8_t reg_low, uint8_t reg_high);
void *accelerometer_listener(void *arg);

#endif // ACCELEROMETER_H