#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdint.h>

typedef enum{
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_NONE
} Joystick_dir;

void joystick_init(void);
Joystick_dir joystick_get_dir(void);
void joystick_cleanup(void);
int joystick_pressed();
uint16_t read_joystick_y();

#endif
