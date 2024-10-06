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

#define PI 3.1416
#define PERIODO_ALARMA 5

uint16_t us, ms, sec, min, hour;
uint32_t dacValue;
uint32_t sineValues [360];
uint8_t index;

uint8_t alarmHour, alarmMin;
uint8_t alarmEnable;

void Clock_Time(void){
	us++;
	if(us == 100){
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
    (index == 360) ? (index = 0) : (index+=6);
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
	if((alarmEnable == 1) && (alarmHour == hour) && (alarmMin == min)){
		Alarm_Sound();
		MAGENTA_LED();
	}
}

void Show_Time(void){
	for (int i = 0; i < 6; i++) {
		switch (i) {
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
	}
}

void func(void){
	Clock_Time();
	if(us % 2 == 0){
		Alarm_Sound();
	}
	Show_Time();
}

int main(void) {
	PIT_Start();
	DAC_Start();
	LED_Init();
	DISPLAY_INIT();
	Get_Sine_Values();

	LED_OFF();

	PIT_Change_Period(USEC_TO_COUNT(1U, PIT_SOURCE_CLOCK), kPIT_Chnl_0);
	PIT_SetCallback(func, kPIT_Chnl_0);

	while(1);
	return 0;
}
