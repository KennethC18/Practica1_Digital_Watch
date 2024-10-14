/*
 * PIT.c
 *
 *  Created on: 23 sep. 2024
 *      Author: Kenneth
 */
#include "PIT.h"

PIT_Callback_t PIT0_Callback = NULL;

/*!
 * @brief Handle interruptions from channel 0 of the PIT.
 */
void PIT0_IRQHandler(void)
{
    PIT_ClearStatusFlags(PIT_ADDR, kPIT_Chnl_0, kPIT_TimerFlag);
    if (PIT0_Callback != NULL){
    	PIT0_Callback();
	}
    __DSB();
}

/*!
 * @brief Default configuration and initialisation for PIT.
 */
void PIT_Start(void){
	/* Structure to initialise PIT */
	pit_config_t pitConfig;
	/*
	* pitConfig.enableRunInDebug = false;
	*/

	/* Board pin and SIM initialisation */
	CLOCK_EnableClock(kCLOCK_PortA);
	PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt7);

	BOARD_InitBootClocks();

	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(PIT_ADDR, &pitConfig);
	PIT_SetTimerPeriod(PIT_ADDR, kPIT_Chnl_0, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK));

	/* Enable timer interrupts for channels*/
	PIT_EnableInterrupts(PIT_ADDR, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	/* Set priority at the NVIC */
	NVIC_SetPriority(PIT0_IRQn, 2);
	EnableIRQ(PIT0_IRQn);

	PIT_StartTimer(PIT_ADDR, kPIT_Chnl_0);
}

/*!
 * @brief Sets the new value for the PIT channel 0 timer period count.
 *
 * @param peiod Setting the value for the new timer period count.
 */
void PIT_Change_Period(uint16_t period){
	PIT_SetTimerPeriod(PIT_ADDR, kPIT_Chnl_0, period);
}

/*!
 * @brief Sets the callback function for the PIT channel 0.
 *
 * @param callback Setting the callback function address.
 */
void PIT_SetCallback(PIT_Callback_t callback)
{
    PIT0_Callback = callback;
}
