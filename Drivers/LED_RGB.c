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

	/* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortE);

	/* PORTB22 (pin 68) is configured as PTB22 */
	PORT_SetPinMux(PORTB, 22U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTE, 26U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, 21U, kPORT_MuxAsGpio);

	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
}

void LED_OFF(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 1);
}

void RED_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
}

void GREEN_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
}

void BLUE_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}

void MAGENTA_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}

void YELLOW_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
}

void CIAN_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}

void WHITE_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}
