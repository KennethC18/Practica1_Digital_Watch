/*
 * GPIO.h
 *
 *  Created on: 26 Sept 2024
 *      Author: Kenneth
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#define TIME_STOPWATCH_BTN_PORT PORTC
#define TIME_ALARM_BTN_PORT PORTC
#define CONFIG_BTN_PORT PORTB
#define HOUR_START_BTN_PORT PORTB
#define MIN_STOP_BTN_PORT PORTB
#define CLEAR_BTN_PORT PORTB
#define ALARM_ON_BTN_PORT PORTA
#define STOP_BTN_PORT PORTC

typedef enum _btn_pin
{
	CLEAR_BTN_PIN = 2U,
	MIN_STOP_BTN_PIN = 3U,
	ALARM_ON_BTN_PIN = 4U,
	STOP_BTN_PIN = 6U,
	TIME_STOPWATCH_BTN_PIN = 10U,
	HOUR_START_BTN_PIN = 10U,
	TIME_ALARM_BTN_PIN = 11U,
	CONFIG_BTN_PIN = 11U,
} btn_pin_t;

typedef void (*GPIO_Callback_t)(uint32_t);

void GPIO_Start(void);
void GPIO_Set_Callback(GPIO_Callback_t callback, GPIO_Type *GPIO);

void PORTA_IRQHandler(void);
void PORTB_IRQHandler(void);
void PORTC_IRQHandler(void);

#endif /* GPIO_H_ */
