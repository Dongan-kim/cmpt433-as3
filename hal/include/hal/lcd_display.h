#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <stdint.h>

// Initialize the LCD screen
void lcd_display_init(void);

// Change the screen based on joystick press
void lcd_display_screen(int screen);

void setScreen(int screen);

int getScreen();

// Display beat name, volume, and BPM on Screen 1
void lcd_display_status_screen(int mode, int bpm, int volume);

// Display Audio Timing or Accelerometer Timing on Screen 2 & 3
void lcd_display_timing_screen(const char *title, double minMs, double maxMs, double avgMs);

// Cleanup function for LCD
void lcd_display_cleanup(void);

#endif // LCD_DISPLAY_H