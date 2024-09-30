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

uint8_t sec, min, hour;
uint32_t dacValue;
uint32_t sineValues [20];

void Clock_Time(void){
	sec++;
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

void Get_Sine_Values(void){
	for (int i = 0; i < 360; ++i) {
		if(i % (360 / 20) != 0){
			sineValues[i] = (uint32_t)floor(2047 * sin(i) + 2047);
		}
	}
}

void Alarm(void){
	uint8_t i = 0;

	//10khz, 5us por muestra, 20 muestras
	dacValue = sineValues[(i == 20) ? (i = 0) : (i++)];
	DAC_Update_Val(dacValue);
}

int main(void) {
	PIT_Start();
	DAC_Start();
	Get_Sine_Values();

	PIT_Change_Period(USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK), kPIT_Chnl_0);
	PIT_SetCallback(Clock_Time, kPIT_Chnl_0);

	PIT_Change_Period(USEC_TO_COUNT(5U, PIT_SOURCE_CLOCK), kPIT_Chnl_1);
	PIT_SetCallback(Alarm, kPIT_Chnl_1);

	return 0;
}
