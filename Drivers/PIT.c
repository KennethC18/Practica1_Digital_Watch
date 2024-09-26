/*
 * PIT.c
 *
 *  Created on: 23 sep. 2024
 *      Author: kenne
 */
#include "PIT.h"

void (*pit_callback)(void) = NULL;
volatile bool pitIsrFlag = false;

void PIT_HANDLER(void)
{
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag);
    if (pit_callback != NULL){
    	pit_callback();
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
	PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

	/* Set timer period for channel 0 */
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK));

	/* Enable timer interrupts for channel 0 */
	PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(PIT_IRQ_ID);

	PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);
}

void PIT_Change_Period(uint16_t period){
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, period);
}

void PIT_SetCallback(void (*callback)(void))
{
    pit_callback = callback;
}
