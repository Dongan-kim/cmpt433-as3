#define _POSIX_C_SOURCE 200809L
#include "periodTimer.h"
#include "hal/lcd_display.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct timespec startTimes[PERIOD_TIMER_COUNT];
static double minTimes[PERIOD_TIMER_COUNT] = {9999, 9999};
static double maxTimes[PERIOD_TIMER_COUNT] = {0, 0};
static double totalTimes[PERIOD_TIMER_COUNT] = {0, 0};
static int countTimes[PERIOD_TIMER_COUNT] = {0, 0};

void periodTimer_init(void) {
    for (int i = 0; i < PERIOD_TIMER_COUNT; i++) {
        minTimes[i] = 9999;
        maxTimes[i] = 0;
        totalTimes[i] = 0;
        countTimes[i] = 0;
    }
}

void periodTimer_start(periodTimer_t timer) {
    clock_gettime(CLOCK_MONOTONIC, &startTimes[timer]);
}

void periodTimer_stop(periodTimer_t timer) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - startTimes[timer].tv_sec) * 1000.0;
    elapsed += (end.tv_nsec - startTimes[timer].tv_nsec) / 1000000.0;

    if (elapsed < minTimes[timer]) minTimes[timer] = elapsed;
    if (elapsed > maxTimes[timer]) maxTimes[timer] = elapsed;

    totalTimes[timer] += elapsed;
    countTimes[timer]++;
}

double periodTimer_getMinTime(periodTimer_t timer) {
    return minTimes[timer];
}

double periodTimer_getMaxTime(periodTimer_t timer) {
    return maxTimes[timer];
}

double periodTimer_getAvgTime(periodTimer_t timer) {
    return (countTimes[timer] > 0) ? (totalTimes[timer] / countTimes[timer]) : 0;
}

void periodTimer_cleanup(void) {
    for (int i = 0; i < PERIOD_TIMER_COUNT; i++) {
        minTimes[i] = 9999;
        maxTimes[i] = 0;
        totalTimes[i] = 0;
        countTimes[i] = 0;
    }
}
