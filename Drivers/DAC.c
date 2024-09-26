/*
 * DAC.c
 *
 *  Created on: 23 sep. 2024
 *      Author: kenne
 */

#include "DAC.h"

void DAC_Start(void){
	dac_config_t dacConfigStruct;

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

    /* Configure the DAC. */
	/*
	* dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
	* dacConfigStruct.enableLowPowerMode = false;
	*/
	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
	DAC_Enable(DEMO_DAC_BASEADDR, true);             /* Enable output. */
	DAC_SetBufferReadPointer(DEMO_DAC_BASEADDR, 0U);
}

void DAC_Update_Val(uint32_t dacValue){
	DAC_SetBufferValue(DEMO_DAC_BASEADDR, 0U, dacValue);
}
