/*
 * WDOG.c
 *
 *  Created on: 5 oct. 2024
 *      Author: Kenneth
 */

#include "WDOG.h"

// Static variables for WDOG and RCM
static WDOG_Type *wdog_base = WDOG;
static RCM_Type *rcm_base = RCM;

// Callback function
typedef void (*WDOG_Callback_t)(void);
WDOG_Callback_t wdog_callback = NULL;

// Macro for WDOG window value
#define WDOG_WINDOW_VALUE (100U)

/*!
 * @brief Waits for the WDOG window close timeout.
 *
 * @param base Base address of the WDOG peripheral.
 */
static void WaitWctClose(WDOG_Type *base) {
    for (uint32_t i = 0; i < WDOG_WCT_INSTRUCTION_COUNT; i++) {
        (void)base->RSTCNT;
    }
}

/*!
 * @brief Initializes the WDOG with the default configuration.
 */
void WDOG_InitConfig(void) {
    wdog_config_t config;

    // Get the default configuration of the WDOG
    WDOG_GetDefaultConfig(&config);

    // Configure the total timeout and the refresh window
    config.timeoutValue = 0x7ffU;  // Total timeout (~2 seconds)
    config.enableWindowMode = true;
    config.windowValue = WDOG_WINDOW_VALUE;  // Refresh window of 100 ms (100 ticks if WDOG clock is 1 kHz)

    // Initialize the WDOG with the configured settings
    WDOG_Init(wdog_base, &config);

    // Wait for the WDOG timer to close
    WaitWctClose(wdog_base);
}

/*!
 * @brief Sets the callback function for WDOG reset.
 *
 * @param callback Pointer to the callback function.
 */
void WDOG_SetCallback(WDOG_Callback_t callback) {
    wdog_callback = callback;
}

/*!
 * @brief Checks if the last reset was caused by WDOG and triggers the callback if so.
 */
void CheckWdogReset(void) {
    // If the reset was caused by WDOG
    if (RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog) {
        if (wdog_callback != NULL) {
            wdog_callback();
        }
        WDOG_TriggerInfiniteLoop();
    }
}

/*!
 * @brief Refreshes the WDOG within the allowed window.
 */
void WDOG_RefreshWindow(void) {
    uint32_t current_timer_value = ((uint32_t)wdog_base->TMROUTH << 16U) | wdog_base->TMROUTL;

    // Check if we are within the refresh window
    if (current_timer_value >= WDOG_WINDOW_VALUE) {
        WDOG_Refresh(wdog_base);  // Refresh the WDOG
    }
}

/*!
 * @brief Triggers an infinite loop to halt the microcontroller.
 */
void WDOG_TriggerInfiniteLoop(void) {
    // Enter an infinite loop
    while (1) {
        // The microcontroller stays here
    }
}
