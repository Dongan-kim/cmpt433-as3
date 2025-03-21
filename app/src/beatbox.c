#include "audioMixer.h"
#include "beatbox.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

//#define BPM_DEFAULT 120
#define BPM_MIN 40
#define BPM_MAX 300

static int bpm;
static int mode; //Default is 1, 0: None, 1: Rock, 2: Custom
static _Bool isRunning = true;
static pthread_t beatThreadId;
pthread_mutex_t beatMutex = PTHREAD_MUTEX_INITIALIZER;

static wavedata_t bassDrum, hiHat, snare, tom, splash;

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

    strcpy(path, "/mnt/remote/myApps/beatbox-wave-files/100063__menegass__gui-drum-tom-hi-soft.wav");
    AudioMixer_readWaveFileIntoMemory(path, &tom);

    strcpy(path, "/mnt/remote/myApps/beatbox-wave-files/100061__menegass__gui-drum-splash-soft.wav");
    AudioMixer_readWaveFileIntoMemory(path, &splash);

    pthread_create(&beatThreadId, NULL, beatThread, NULL);
}

void BeatBox_cleanup() {
    isRunning = false;
    pthread_join(beatThreadId, NULL);
    AudioMixer_freeWaveFileData(&bassDrum);
    AudioMixer_freeWaveFileData(&hiHat);
    AudioMixer_freeWaveFileData(&snare);
    AudioMixer_freeWaveFileData(&tom);
    AudioMixer_freeWaveFileData(&splash);
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

void setMode(int input_mode) {
    pthread_mutex_lock(&beatMutex);
    if (input_mode >= 0 && input_mode <= 2) {
        mode = input_mode;
    }
    pthread_mutex_unlock(&beatMutex);
}

int getMode() {
    pthread_mutex_lock(&beatMutex);
    int currentMode = mode;
    pthread_mutex_unlock(&beatMutex);

    return currentMode;
}

void* beatThread(void* arg) {
    (void)arg;
    while (isRunning) {
        int mode = getMode();

        if (mode == 1) {
            playRockBeat();
        } else if (mode == 2) {
            playCustomBeat();
        }
    }
    return NULL;
}

void cycleBeatMode() {
    int currentMode = getMode();
    currentMode = (currentMode % 3) + 1; // Cycle through modes
    
    if (currentMode == 3) {
        setMode(0);
    } else {
        setMode(currentMode);
    }
}

void playRockBeat() {
    int localBPM;

    pthread_mutex_lock(&beatMutex);
    localBPM = bpm;
    pthread_mutex_unlock(&beatMutex);

    double halfBeatTime = (60.0 / localBPM) / 2 * 1000000; 

    playBassDrum();
    playHiHat();
    usleep(halfBeatTime);

    playHiHat();
    usleep(halfBeatTime);

    playSnare();
    playHiHat();
    usleep(halfBeatTime);

    playHiHat();
    usleep(halfBeatTime);
}

void playCustomBeat() {
    int localBPM;

    pthread_mutex_lock(&beatMutex);
    localBPM = bpm;
    pthread_mutex_unlock(&beatMutex);


    double beatTime = (60.0 / localBPM) * 1000000;
    double quarterBeat = beatTime / 4;

 
    playBassDrum();   
    playHiHat();       
    usleep(quarterBeat);
    
    playSnare();   
    playTom();    
    usleep(quarterBeat);

    playBassDrum();    
    playHiHat();       
    usleep(quarterBeat);

    playSnare();       
    playTom(); 
    usleep(quarterBeat);

    playBassDrum();
    playHiHat();
    usleep(quarterBeat);

    playTom(); 
    usleep(quarterBeat);

    playHiHat();
    playSnare();
    usleep(quarterBeat);

    playSplash(); 
    usleep(quarterBeat);
}

void playSnare() {
    AudioMixer_queueSound(&snare);
}

void playBassDrum() {
    AudioMixer_queueSound(&bassDrum);
}

void playHiHat() {
    AudioMixer_queueSound(&hiHat);
}

void playTom() {
    AudioMixer_queueSound(&tom);
}

void playSplash() {
    AudioMixer_queueSound(&splash);
}