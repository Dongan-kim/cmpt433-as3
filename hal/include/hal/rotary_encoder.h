#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdbool.h>
extern volatile int rotaryButtonPressed;

// Initialize the rotary encoder
void RotaryEncoder_init(void);

// Get the current rotary encoder value
//int RotaryEncoder_getValue(void);

// Listen for rotary encoder events (runs in a separate thread)
void *RotaryEncoder_listen(void *arg);

int RotaryEncoder_buttonPressed(void);

void *RotaryEncoder_buttonListener(void *arg);

// Cleanup rotary encoder resources
void RotaryEncoder_cleanup(void);

#endif  // ROTARY_ENCODER_H