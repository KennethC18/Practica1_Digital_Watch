/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Practica1.c
 * @brief   Application entry point.
 */

#include "math.h"
#include "Drivers/PIT.h"
#include "Drivers/DAC.h"
#include "Drivers/LED_RGB.h"
#include "Drivers/display.h"
#include "Drivers/WDOG.h"
#include "Drivers/GPIO.h"

#define PI 3.1416

// Variables for timekeeping
uint16_t us, ms, sec, min, hour;

// DAC and sine wave variables
uint32_t dacValue;
uint32_t sineValues[360];
uint8_t index;

// Alarm variables
uint8_t alarmHour, alarmMin;
uint8_t alarmEnable;
bool alarm_enabled = false;

// Stopwatch variables
uint16_t us_stpwtch, ms_stpwtch, sec_stpwtch, min_stpwtch;

// Display refresh time
uint16_t refreshTime;

// Display selection states
uint8_t dispClock;
uint8_t dispStp;
uint8_t dispAlarm;
uint8_t displaySelection;

// Button states
bool stpwtchBtnState = false;
bool alarmBtnState = false;
bool stpwtchStart = false;
bool configBtnState = false;

// Enum for display selection
typedef enum _kDisplay_Select {
    display_Clock = 0U,
    display_Stopwatch,
    display_Alarm,
} kDisplay_Select;

/*!
 * @brief Function to handle time incrementation for the clock.
 */
void Clock_Time(void) {
    us++;
    if (us == 175) {
        us = 0;
        ms++;
    }
    if (ms == 1000) {
        ms = 0;
        sec++;
    }
    if (sec == 60) {
        sec = 0;
        min++;
    }
    if (min == 60) {
        min = 0;
        hour++;
    }
    if (hour == 24) {
        hour = 0;
    }
}

/*!
 * @brief Function to handle time incrementation for the stopwatch.
 */
void Stopwatch_Time() {
    us_stpwtch++;
    if (us_stpwtch == 175) {
        us_stpwtch = 0;
        ms_stpwtch++;
    }
    if (ms_stpwtch == 1000) {
        ms_stpwtch = 0;
        sec_stpwtch++;
    }
    if (sec_stpwtch == 60) {
        sec_stpwtch = 0;
        min_stpwtch++;
    }
    if (min_stpwtch == 60) {
        min_stpwtch = 0;
    }
}

/*!
 * @brief Function to increment alarm hours and minutes.
 */
void Alarm_Time(void) {
    if (alarmMin == 60) {
        alarmMin = 0;
        alarmHour++;
    }
    if (alarmHour == 24) {
        alarmHour = 0;
    }
}

/*!
 * @brief Function to populate an array with pre-calculated sine wave values.
 */
void Get_Sine_Values(void) {
    for (int i = 0; i < 360; ++i) {
        sineValues[i] = (uint32_t)floor(2047.5 * sinf(i * (PI / 30)) + 2047.5);
    }
}

/*!
 * @brief Function to generate an alarm sound using the DAC and sine wave values.
 */
void Alarm_Sound(void) {
    if (((ms >= 250) && (ms <= 500)) || ((ms >= 750) && (ms <= 1000))) {
        dacValue = 0;
    } else {
        dacValue = sineValues[index];
    }
    DAC_Update_Val(dacValue);
    (index == 360) ? (index = 0) : (index += 5);
}

/*!
 * @brief Function to enable or disable the alarm system.
 */
void Alarm_Enable() {
    alarmEnable = !alarmEnable;
    if (alarmEnable == 1) {
        RED_LED();
    } else {
        LED_OFF();
    }
}

/*!
 * @brief Function to check if the alarm should sound and trigger the alarm system.
 */
void Alarm(void) {
    if ((alarmEnable == 1) && (hour == alarmHour) && (min == alarmMin)) {
        Alarm_Sound();
        MAGENTA_LED();
    }
}

/*!
 * @brief Function to show the current time on the display.
 */
void Show_Time(void) {
    switch (dispClock) {
        case 0:
            SHOW_NUMBER((sec % 10), 0);
            break;
        case 1:
            SHOW_NUMBER((sec / 10), 1);
            break;
        case 2:
            SHOW_NUMBER((min % 10), 2);
            break;
        case 3:
            SHOW_NUMBER((min / 10), 3);
            break;
        case 4:
            SHOW_NUMBER((hour % 10), 4);
            break;
        case 5:
            SHOW_NUMBER((hour / 10), 5);
            break;
        default:
            break;
    }
    (dispClock == 5) ? (dispClock = 0) : (dispClock++);
}

/*!
 * @brief Function to show the stopwatch time on the display.
 */
void Show_Stopwatch(void) {
    switch (dispStp) {
        case 0:
            SHOW_NUMBER(((ms_stpwtch % 100) / 10), 0);
            break;
        case 1:
            SHOW_NUMBER((ms_stpwtch / 100), 1);
            break;
        case 2:
            SHOW_NUMBER((sec_stpwtch % 10), 2);
            break;
        case 3:
            SHOW_NUMBER((sec_stpwtch / 10), 3);
            break;
        case 4:
            SHOW_NUMBER((min_stpwtch % 10), 4);
            break;
        case 5:
            SHOW_NUMBER((min_stpwtch / 10), 5);
            break;
        default:
            break;
    }
    (dispStp == 5) ? (dispStp = 0) : (dispStp++);
}

/*!
 * @brief Function to show the alarm time on the display.
 */
void Show_Alarm(void) {
    switch (dispAlarm) {
        case 0:
            DISPLAY_OFF();
            break;
        case 1:
            DISPLAY_OFF();
            break;
        case 2:
            SHOW_NUMBER((alarmMin % 10), 2);
            break;
        case 3:
            SHOW_NUMBER((alarmMin / 10), 3);
            break;
        case 4:
            SHOW_NUMBER((alarmHour % 10), 4);
            break;
        case 5:
            SHOW_NUMBER((alarmHour / 10), 5);
            break;
        default:
            break;
    }
    (dispAlarm == 5) ? (dispAlarm = 0) : (dispAlarm++);
}

/*!
 * @brief Function to select which display mode to show (Clock, Stopwatch, or Alarm).
 */
void Display_Select(void) {
    switch (displaySelection) {
        case display_Clock:
            Show_Time();
            break;
        case display_Stopwatch:
            Show_Stopwatch();
            break;
        case display_Alarm:
            Show_Alarm();
            break;
        default:
            break;
    }
}

/*!
 * @brief Callback function to handle button presses on port A.
 */
void PORTA_BTNS(uint32_t flags) {
    if (flags == (1 << ALARM_ON_BTN_PIN)) {
        if (!alarm_enabled) {
            Alarm_Enable();
            alarm_enabled = true;
        }
    }
}

/*!
 * @brief Callback function to handle button presses on port B.
 */
void PORTB_BTNS(uint32_t flags) {
    switch (flags) {
        case (1 << CONFIG_BTN_PIN):
            configBtnState = !configBtnState;
            (configBtnState) ? (CIAN_LED()) : (LED_OFF());
            break;
        case (1 << HOUR_START_BTN_PIN):
            if (alarmBtnState) {
                alarmHour++;
                Alarm_Time();
            }
            if (stpwtchBtnState) {
                stpwtchStart = true;
            }
            if (configBtnState) {
                hour++;
            }
            break;
        case (1 << MIN_STOP_BTN_PIN):
            if (alarmBtnState) {
                alarmMin++;
                Alarm_Time();
            }
            if (stpwtchBtnState) {
                stpwtchStart = false;
            }
            if (configBtnState) {
                min++;
            }
            break;
        case (1 << CLEAR_BTN_PIN):
            if (alarm_enabled) {
                Alarm_Enable();
                alarm_enabled = false;
            }
            if (stpwtchBtnState) {
                us_stpwtch = 0;
                ms_stpwtch = 0;
                sec_stpwtch = 0;
                min_stpwtch = 0;
            }
            break;
        default:
            break;
    }
}

/*!
 * @brief Callback function to handle button presses on port C.
 */
void PORTC_BTNS(uint32_t flags) {
    switch (flags) {
        case (1 << TIME_STOPWATCH_BTN_PIN):
            if (displaySelection != display_Stopwatch) {
                displaySelection = display_Stopwatch;
                stpwtchBtnState = true;
            } else {
                stpwtchBtnState = false;
                displaySelection = display_Clock;
            }
            break;
        case (1 << TIME_ALARM_BTN_PIN):
            if (displaySelection != display_Alarm) {
                displaySelection = display_Alarm;
                alarmBtnState = true;
            } else {
                alarmBtnState = false;
                displaySelection = display_Clock;
            }
            break;
        case (1 << STOP_BTN_PIN):
            STOP();
            break;
        default:
            break;
    }
}

/*!
 * @brief Main function that initializes the system and runs the application.
 */
int main(void) {
    /* Init board hardware. */
    Get_Sine_Values();
    PIT_Init();
    DAC_Init();
    LED_Init();
    WDOG_Disable();
    DISPLAY_Init();
    GPIO_Init();
    WDOG_Init();

    while (1) {
        Display_Select();
    }
    return 0;
}
