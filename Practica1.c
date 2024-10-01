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

#define PI 3.1416
#define PERIODO_ALARMA 2

uint16_t ms, sec, min, hour;
uint32_t dacValue;
uint32_t sineValues [360];
uint8_t index;

void Clock_Time(void){
	ms++;
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

void Get_Sine_Values(void){
	for (int i = 0; i < 360; ++i) {
		sineValues[i] = (uint32_t)floor(2047.5 * sinf(i * (PI / 30)) + 2047.5);
	}
}

void Alarm(void){
	if(ms >= 500){
		dacValue = sineValues[(index == 360) ? (index = 0) : (index++)];
	}
	else{
		dacValue = 0;
	}
	DAC_Update_Val(dacValue);
}

int main(void) {
	PIT_Start();
	DAC_Start();
	Get_Sine_Values();

	PIT_Change_Period(USEC_TO_COUNT(1000U, PIT_SOURCE_CLOCK), kPIT_Chnl_0);
	PIT_SetCallback(Clock_Time, kPIT_Chnl_0);

	PIT_Change_Period(USEC_TO_COUNT(PERIODO_ALARMA, PIT_SOURCE_CLOCK), kPIT_Chnl_1);
	PIT_SetCallback(Alarm, kPIT_Chnl_1);

	while(1);

	return 0;
}
