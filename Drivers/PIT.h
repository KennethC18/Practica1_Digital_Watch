/*
 * PIT.h
 *
 *  Created on: 23 sep. 2024
 *      Author: kenne
 */

#ifndef PIT_H_
#define PIT_H_

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"

#define PIT_BASEADDR PIT

/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void PIT0_IRQHandler(void);
void PIT1_IRQHandler(void);

void PIT_Start(void);

void PIT_Change_Period(uint16_t period, pit_chnl_t channel);

void PIT_SetCallback(void (*callback)(void), pit_chnl_t channel);

#endif /* PIT_H_ */
