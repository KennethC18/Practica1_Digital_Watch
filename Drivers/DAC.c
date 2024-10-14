/*
 * DAC.c
 *
 *  Created on: 23 sep. 2024
 *      Author: Kenneth
 */

#include "DAC.h"

/*!
 * @brief Default configuration and initialisation for DAC.
 */
void DAC_Start(void){
	/* Configuration options for DAC */
	dac_config_t dacConfigStruct;
	/*
	* dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
	* dacConfigStruct.enableLowPowerMode = false;
	*/

	BOARD_InitBootPins();
	BOARD_InitBootClocks();

    /* Configure the DAC. */
	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DAC_ADDR, &dacConfigStruct);
	DAC_Enable(DAC_ADDR, true);             /* Enable output. */
	DAC_SetBufferReadPointer(DAC_ADDR, 0U);
}

/*!
 * @brief Sets the new value for the DAC buffer.
 *
 * @param dacValue Setting the value for the next item in the buffer.
 */
void DAC_Update_Val(uint32_t dacValue){
	DAC_SetBufferValue(DAC_ADDR, 0U, dacValue);
}
