#include "hal/lcd_display.h"
#include "hal/rotary_encoder.h"
#include "DEV_Config.h"
#include "LCD_1in54.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "periodTimer.h"
#include "audioMixer.h"
#include "beatbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static UWORD *s_fb;
static int currentScreen = 1; // Start on Screen 1

void lcd_display_init() {
    if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }

    // LCD Init
    LCD_1IN54_Init(HORIZONTAL);
    LCD_1IN54_Clear(WHITE);
    LCD_SetBacklight(1023);

    UDOUBLE Imagesize = LCD_1IN54_HEIGHT * LCD_1IN54_WIDTH * 2;
    if((s_fb = (UWORD *)malloc(Imagesize)) == NULL) {
        perror("LCD: Failed to allocate memory");
        exit(0);
    }
}

// 🚀 Function to switch between 3 screens when joystick is pressed
void lcd_display_screen(int screen) {
    currentScreen = screen; // Store the current screen state
    LCD_1IN54_Clear(WHITE);

    if (screen == 1) {
        lcd_display_status_screen(getMode(), getBPM(), AudioMixer_getVolume());
    } else if (screen == 2) {
        Period_statistics_t audioStats;
        Period_getStatisticsAndClear(PERIOD_EVENT_AUDIO_BUFFER_FILL, &audioStats);

        lcd_display_timing_screen("Audio Timing",
            audioStats.minPeriodInMs,
            audioStats.maxPeriodInMs,
            audioStats.avgPeriodInMs);
    } else if (screen == 3) {
        Period_statistics_t accelStats;
        Period_getStatisticsAndClear(PERIOD_EVENT_ACCELEROMETER_SAMPLE, &accelStats);

        lcd_display_timing_screen("Accel. Timing",
            accelStats.minPeriodInMs,
            accelStats.maxPeriodInMs,
            accelStats.avgPeriodInMs);
    }
}

void setScreen(int screen) {
    if (screen < 1 || screen > 3) {
        printf("Invalid screen number: %d\n", screen);
        return;
    }
    currentScreen = screen;
}

int getScreen() {
    return currentScreen;
}

// ✅ Screen 1: Beat Name, BPM, and Volume
void lcd_display_status_screen(int mode, int bpm, int volume) {
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    // Display Beat Name
    const char *modeNames[] = {"None", "Rock", "Custom"};
    int modeIndex = mode;
    if (modeIndex < 0 || modeIndex > 2) {
        modeIndex = 2;
    }
    Paint_DrawString_EN(90, 30, modeNames[modeIndex], &Font24, WHITE, BLACK);

    // Display Volume and BPM
    char volText[20], bpmText[20];
    snprintf(volText, sizeof(volText), "Vol: %d", volume);
    snprintf(bpmText, sizeof(bpmText), "BPM: %d", bpm);

    Paint_DrawString_EN(10, 100, volText, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(140, 100, bpmText, &Font16, WHITE, BLACK);

    LCD_1IN54_Display(s_fb);
}

// ✅ Screen 2 & 3: Display Timing Info
void lcd_display_timing_screen(const char *title, double minMs, double maxMs, double avgMs) {
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    // Title
    Paint_DrawString_EN(30, 20, title, &Font16, WHITE, BLACK);

    // Min, Max, Avg Times
    char minStr[30], maxStr[30], avgStr[30];
    snprintf(minStr, sizeof(minStr), "Min: %.2fms", minMs);
    snprintf(maxStr, sizeof(maxStr), "Max: %.2fms", maxMs);
    snprintf(avgStr, sizeof(avgStr), "Avg: %.2fms", avgMs);

    Paint_DrawString_EN(10, 60, minStr, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(10, 80, maxStr, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(10, 100, avgStr, &Font16, WHITE, BLACK);

    LCD_1IN54_Display(s_fb);
}

// Cleanup Function
void lcd_display_cleanup() {
    free(s_fb);
    s_fb = NULL;
    DEV_ModuleExit();
}