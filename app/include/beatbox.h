#ifndef BEATBOX_H
#define BEATBOX_H

#include <pthread.h>

// Initialize the BeatBox system (loads sounds, starts the beat thread)
void BeatBox_init(void);

// Cleanup BeatBox system (frees memory, stops the beat thread)
void BeatBox_cleanup(void);

// Set the BPM (Tempo) - must be in the range 40-300
void setBPM(int bpm);

int getBPM();

// Set the beat mode: 
// 0 - None (off), 1 - Rock, 2 - Custom
void setMode(int mode);

int getMode();

//void cycleBeatMode();

void playSnare();
void playBassDrum();
void playHiHat();

extern pthread_mutex_t beatMutex;
extern int currentMode; 

#endif