/*
 * DAC.h
 *
 *  Created on: 23 sep. 2024
 *      Author: Kenneth
 */

#ifndef DAC_H_
#define DAC_H_

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_dac.h"
#include "fsl_common.h"

#define DAC_ADDR DAC0

void DAC_Start(void);

void DAC_Update_Val(uint32_t dacValue);

#endif /* DAC_H_ */
