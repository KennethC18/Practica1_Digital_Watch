/*
 * PIT.c
 *
 *  Created on: 23 sep. 2024
 *      Author: kenne
 */
#include "PIT.h"

void (*pit0_callback)(void) = NULL;
void (*pit1_callback)(void) = NULL;

void PIT0_IRQHandler(void)
{
    PIT_ClearStatusFlags(PIT_BASEADDR, kPIT_Chnl_0, kPIT_TimerFlag);
    if (pit0_callback != NULL){
    	pit0_callback();
	}
    __DSB();
}

void PIT1_IRQHandler(void)
{
    PIT_ClearStatusFlags(PIT_BASEADDR, kPIT_Chnl_1, kPIT_TimerFlag);
    if (pit1_callback != NULL){
    	pit1_callback();
	}
    __DSB();
}

void PIT_Start(void){
	/* Structure of initialize PIT */
	pit_config_t pitConfig;

	/* Board pin, clock, debug console init */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	/*
	* pitConfig.enableRunInDebug = false;
	*/
	PIT_GetDefaultConfig(&pitConfig);

	/* Init pit module */
	PIT_Init(PIT_BASEADDR, &pitConfig);

	/* Set timer period for channels*/
	PIT_SetTimerPeriod(PIT_BASEADDR, kPIT_Chnl_0, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK));
	PIT_SetTimerPeriod(PIT_BASEADDR, kPIT_Chnl_1, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK));

	/* Enable timer interrupts for channels*/
	PIT_EnableInterrupts(PIT_BASEADDR, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	PIT_EnableInterrupts(PIT_BASEADDR, kPIT_Chnl_1, kPIT_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(PIT0_IRQn);
	EnableIRQ(PIT1_IRQn);

	PIT_StartTimer(PIT_BASEADDR, kPIT_Chnl_0);
	PIT_StartTimer(PIT_BASEADDR, kPIT_Chnl_1);
}

void PIT_Change_Period(uint16_t period, pit_chnl_t channel){
	PIT_SetTimerPeriod(PIT_BASEADDR, channel, period);
}

void PIT_SetCallback(void (*callback)(void), pit_chnl_t channel)
{
    (channel == kPIT_Chnl_0) ? (pit0_callback = callback) : (pit1_callback = callback);
}
