#include "audioMixer.h"
#include "beatbox.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BPM_DEFAULT 120
#define BPM_MIN 40
#define BPM_MAX 300

static int bpm = BPM_DEFAULT;
int currentMode; // 0: None, 1: Rock, 2: Custom
static _Bool isRunning = true;
static pthread_t beatThreadId;
pthread_mutex_t beatMutex = PTHREAD_MUTEX_INITIALIZER;

static wavedata_t bassDrum, hiHat, snare;

void* beatThread(void* arg);
void playRockBeat();
void playCustomBeat();

void BeatBox_init() {
    char path[256];

    strcpy(path, "/mnt/remote/myApps/beatbox-wave-files/100051__menegass__gui-drum-bd-hard.wav");
    AudioMixer_readWaveFileIntoMemory(path, &bassDrum);

    strcpy(path, "/mnt/remote/myApps/beatbox-wave-files/100053__menegass__gui-drum-cc.wav");
    AudioMixer_readWaveFileIntoMemory(path, &hiHat);

    strcpy(path, "/mnt/remote/myApps/beatbox-wave-files/100059__menegass__gui-drum-snare-soft.wav");
    AudioMixer_readWaveFileIntoMemory(path, &snare);

    pthread_create(&beatThreadId, NULL, beatThread, NULL);
}

void BeatBox_cleanup() {
    isRunning = false;
    pthread_join(beatThreadId, NULL);
    AudioMixer_freeWaveFileData(&bassDrum);
    AudioMixer_freeWaveFileData(&hiHat);
    AudioMixer_freeWaveFileData(&snare);
    pthread_mutex_destroy(&beatMutex);
}

void setBPM(int newBPM) {
    pthread_mutex_lock(&beatMutex);
    if (newBPM >= BPM_MIN && newBPM <= BPM_MAX) {
        bpm = newBPM;
    }
    pthread_mutex_unlock(&beatMutex);
}

int getBPM() {
    pthread_mutex_lock(&beatMutex);
    int currentBPM = bpm;
    pthread_mutex_unlock(&beatMutex);
    return currentBPM;
}

void setMode(int mode) {
    pthread_mutex_lock(&beatMutex);
    if (mode >= 0 && mode <= 2) {
        currentMode = mode;
    }
    pthread_mutex_unlock(&beatMutex);
}

void* beatThread(void* arg) {
    (void)arg;
    while (isRunning) {
        pthread_mutex_lock(&beatMutex);
        int mode = currentMode;
        pthread_mutex_unlock(&beatMutex);

        switch (mode) {
            case 1: playRockBeat(); break;
            case 2: playCustomBeat(); break;
            default: usleep(500000); break; // No beat (sleep to avoid CPU usage)
        }
    }
    return NULL;
}

void playRockBeat() {
    int localBPM;

    // Only lock to read BPM, then unlock immediately
    pthread_mutex_lock(&beatMutex);
    localBPM = bpm;
    pthread_mutex_unlock(&beatMutex);

    double halfBeatTime = (60.0 / localBPM) / 2 * 1000000; // Convert to microseconds

    AudioMixer_queueSound(&bassDrum);
    AudioMixer_queueSound(&hiHat);
    usleep(halfBeatTime);

    AudioMixer_queueSound(&hiHat);
    usleep(halfBeatTime);

    AudioMixer_queueSound(&snare);
    AudioMixer_queueSound(&hiHat);
    usleep(halfBeatTime);

    AudioMixer_queueSound(&hiHat);
    usleep(halfBeatTime);
}

void playCustomBeat() {
    int localBPM;

    pthread_mutex_lock(&beatMutex);
    localBPM = bpm;
    pthread_mutex_unlock(&beatMutex);

    double beatTime = (60.0 / localBPM) * 1000000; // Convert to microseconds

    AudioMixer_queueSound(&hiHat);
    usleep(beatTime / 4);

    AudioMixer_queueSound(&bassDrum);
    usleep(beatTime / 2);

    AudioMixer_queueSound(&snare);
    usleep(beatTime / 4);
}
