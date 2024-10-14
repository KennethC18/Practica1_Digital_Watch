/*
 * LED_RGB.h
 *
 *  Created on: 26 Sept 2024
 *      Author: Kenneth
 */

#ifndef LED_RGB_H_
#define LED_RGB_H_

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

// Configuration for LED pins
typedef struct {
    gpio_pin_config_t config;
} LedConfig;

void LED_Init(void);

void LED_OFF(void);

void RED_LED(void);
void GREEN_LED(void);
void BLUE_LED(void);

void MAGENTA_LED(void);
void YELLOW_LED(void);
void CIAN_LED(void);

void WHITE_LED(void);

#endif /* LED_RGB_H_ */
