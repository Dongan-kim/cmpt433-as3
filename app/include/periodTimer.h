#ifndef PERIOD_TIMER_H
#define PERIOD_TIMER_H

typedef enum {
    PERIOD_TIMER_AUDIO = 0,  // Timing for audio processing
    PERIOD_TIMER_ACCEL,  // Timing for accelerometer
    PERIOD_TIMER_COUNT
} periodTimer_t;

void periodTimer_init(void);
void periodTimer_start(periodTimer_t timer);
void periodTimer_stop(periodTimer_t timer);
unsigned long long periodTimer_getCurrentTimeMs(void);
double periodTimer_getMinTime(periodTimer_t timer);
double periodTimer_getMaxTime(periodTimer_t timer);
double periodTimer_getAvgTime(periodTimer_t timer);
void periodTimer_cleanup(void);

#endif // PERIOD_TIMER_H