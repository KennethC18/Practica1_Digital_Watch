/*
 * LED_RGB.c
 *
 *  Created on: 26 Sept 2024
 *      Author: kenneth
 */
#include "LED_RGB.h"

void LED_Init(void){
	/* Define the init structure for the output LED pin*/
	gpio_pin_config_t led_config = {
		kGPIO_DigitalOutput,
	    0,
	};

	/* Board pin, clock, debug console init */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
}

void LED_OFF(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN, 1);
}

void RED_LED(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN, 1);
}

void GREEN_LED(void){
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN, 1);
}

void BLUE_LED(void){
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN, 1);
}

void MAGENTA_LED(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN, 1);
}

void YELLOW_LED(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN, 1);
}

void CIAN_LED(void){
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN, 1);
}

void WHITE_LED(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN, 1);
}
