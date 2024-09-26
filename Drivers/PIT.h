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

#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0
#define PIT_HANDLER   PIT0_IRQHandler
#define PIT_IRQ_ID        PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void PIT_HANDLER(void);

void PIT_Start(void);

void PIT_Change_Period(uint16_t period);

void PIT_SetCallback(void (*callback)(void));

#endif /* PIT_H_ */
