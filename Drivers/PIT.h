/*
 * PIT.h
 *
 *  Created on: 23 sep. 2024
 *      Author: Kenneth
 */

#ifndef PIT_H_
#define PIT_H_

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"

#define PIT_ADDR PIT
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

typedef void (*PIT_Callback_t)(void);

void PIT0_IRQHandler(void);
void PIT_Start(void);
void PIT_Change_Period(uint16_t period);
void PIT_SetCallback(PIT_Callback_t callback);

#endif /* PIT_H_ */
