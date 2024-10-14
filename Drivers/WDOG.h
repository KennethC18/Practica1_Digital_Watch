/*
 * WDOG.h
 *
 *  Created on: 5 oct. 2024
 *      Author: kenneth
 */
#ifndef _WDOG_H_
#define _WDOG_H_

#include "fsl_wdog.h"
#include "fsl_rcm.h"

#define WDOG_TIMEOUT_VALUE (0x7ffU)      // Timeout value (~2 seconds)
#define WDOG_WINDOW_VALUE (100U)         // Window value (100 ms)
#define WDOG_WCT_INSTRUCTION_COUNT 256U

// Watchdog callback type
typedef void (*WDOG_Callback_t)(void);

void WDOG_InitConfig(void);
void CheckWdogReset(void);
void WDOG_RefreshWindow(void);
void WDOG_TriggerInfiniteLoop(void);
void WDOG_SetCallback(WDOG_Callback_t callback);

#endif // _WDOG_H_
