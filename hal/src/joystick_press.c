#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "periodTimer.h"

#define DEBOUNCE_DELAY_MS 50   // Adjust debounce time
#define GPIO_CHIP "/dev/gpiochip2"
#define GPIO_BUTTON 15

static struct gpiod_chip *chip;
static struct gpiod_line *button_line;

void joystick_press_init() {
    chip = gpiod_chip_open(GPIO_CHIP);
    if (!chip) {
        perror("Failed to open GPIO chip");
        return;
    }

    button_line = gpiod_chip_get_line(chip, GPIO_BUTTON);
    if (!button_line) {
        perror("Failed to get GPIO line");
        return;
    }

    gpiod_line_request_both_edges_events(button_line, "joystick_btn");
}

int joystick_pressed() {
    static int lastState = 1; // Assume HIGH (not pressed) initially
    static long lastPressTime = 0;

    if (!button_line) return 0; // Ensure button is initialized

    int currentState = gpiod_line_get_value(button_line);
    long currentTime = periodTimer_getCurrentTimeMs();

    if (lastState == 1 && currentState == 0) { // Detect falling edge
        if (currentTime - lastPressTime > 200) { // 200ms debounce
            lastPressTime = currentTime;
            lastState = currentState;
            return 1; // Valid press detected
        }
    }

    lastState = currentState;
    return 0; // No valid press detected
}

void joystick_press_cleanup() {
    if (button_line) {
        gpiod_line_release(button_line);
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
}