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

uint16_t us, ms, sec, min, hour;
uint8_t dispClock;

uint32_t dacValue;
uint32_t sineValues [360];
uint8_t index;

uint8_t alarmHour, alarmMin;
uint8_t dispAlarm;
uint8_t alarmEnable;
bool alarm_enabled = false;

uint16_t us_stpwtch, ms_stpwtch, sec_stpwtch, min_stpwtch, hour_stpwtch;
uint8_t dispStp;

uint16_t refreshTime;

void Clock_Time(void){
	us++;
	if(us == 250){
		ms++;
		us = 0;
		if(ms == 1000){
			sec++;
			ms = 0;
			if(sec == 60){
				min++;
				sec = 0;
				if(min == 60){
					hour++;
					min = 0;
					if(hour == 24){
						hour = 0;
					}
				}
			}
		}
	}
}

void Stopwatch_Time(){
	us_stpwtch++;
	if(us_stpwtch == 250){
		ms_stpwtch++;
		us_stpwtch = 0;
		if(ms_stpwtch == 1000){
			sec_stpwtch++;
			ms_stpwtch = 0;
			if(sec_stpwtch == 60){
				min_stpwtch++;
				sec_stpwtch = 0;
				if(min_stpwtch == 60){
				}
			}
		}
	}
}

void Get_Sine_Values(void){
	for (int i = 0; i < 360; ++i) {
		sineValues[i] = (uint32_t)floor(2047.5 * sinf(i * (PI / 30)) + 2047.5);
	}
}

void Alarm_Sound(void){
    if(((ms >= 250) && (ms <= 500)) || ((ms >= 750) && (ms <= 1000))){
    	dacValue = 0;
    }
    else{
    	dacValue = sineValues[index];
    }
	DAC_Update_Val(dacValue);
    (index == 360) ? (index = 0) : (index += 5);
}

void Alarm_Enable(){
	alarmEnable = !alarmEnable;
	if(alarmEnable == 1){
		RED_LED();
	}
	else{
		LED_OFF();
	}
}

void Alarm(void){
	if((alarmEnable == 1) && (hour >= alarmHour) && (min >= alarmMin)){
		Alarm_Sound();
		MAGENTA_LED();
	}
}

void Show_Time(void){
	switch (dispClock) {
		case 0:
			SHOW_NUMBER((sec%10), 0);
			break;
		case 1:
			SHOW_NUMBER((sec/10), 1);
			break;
		case 2:
			SHOW_NUMBER((min%10), 2);
			break;
		case 3:
			SHOW_NUMBER((min/10), 3);
			break;
		case 4:
			SHOW_NUMBER((hour%10), 4);
			break;
		case 5:
			SHOW_NUMBER((hour/10), 5);
			break;
		default:
			break;
	}
	(dispClock == 5) ? (dispClock = 0) : (dispClock++);
}

void Show_Stopwatch(void){
	switch (dispStp) {
		case 0:
			SHOW_NUMBER(((ms_stpwtch%100)/10), 0);
			break;
		case 1:
			SHOW_NUMBER((ms_stpwtch/100), 1);
			break;
		case 2:
			SHOW_NUMBER((sec_stpwtch%10), 2);
			break;
		case 3:
			SHOW_NUMBER((sec_stpwtch/10), 3);
			break;
		case 4:
			SHOW_NUMBER((min_stpwtch%10), 4);
			break;
		case 5:
			SHOW_NUMBER((min_stpwtch/10), 5);
			break;
		default:
			break;
	}
	(dispStp == 5) ? (dispStp = 0) : (dispStp++);
}

void Show_Alarm(void){
	switch (dispAlarm) {
		case 2:
			SHOW_NUMBER((alarmMin%10), 2);
			break;
		case 3:
			SHOW_NUMBER((alarmMin/10), 3);
			break;
		case 4:
			SHOW_NUMBER((alarmHour%10), 4);
			break;
		case 5:
			SHOW_NUMBER((alarmHour/10), 5);
			break;
		default:
			break;
	}
	(dispAlarm == 5) ? (dispAlarm = 2) : (dispAlarm++);
}

void func(void) {
    Clock_Time();
    Stopwatch_Time();
    if(ms % refreshTime == 0){
    	WDOG_RefreshWindow();
    }
    if (us % 8 == 0) {
        Alarm();
    }
    if (ms % 1 == 0) {
    	if((sec < 20)){
    		Show_Time();
    	}
    	if((sec >= 20) && (sec < 40)){
    		Show_Alarm();
    	}
    	if((sec >= 40) && (sec <= 59)){
    	   	Show_Stopwatch();
     	}
    }
    CheckWdogReset();
}

void PORTA_BTNS(uint32_t flags){
	if(flags == (1 << ALARM_ON_BTN_PIN)){
		if (!alarm_enabled) {
		    Alarm_Enable();
		    alarm_enabled = true;
		}
	}
}

int main(void) {
	PIT_Start();
	DAC_Start();
	LED_Init();
	DISPLAY_INIT();
	WDOG_InitConfig();

	Get_Sine_Values();
	LED_OFF();

	alarmMin = 1;
	sec = 0;

	refreshTime = 300;

	WDOG_SetCallback(YELLOW_LED);

	PIT_Change_Period(USEC_TO_COUNT(1U, PIT_SOURCE_CLOCK), kPIT_Chnl_0);
	PIT_SetCallback(func, kPIT_Chnl_0);

	while(1);
	return 0;
}
