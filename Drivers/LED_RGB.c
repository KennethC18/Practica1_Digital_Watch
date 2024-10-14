/*
 * LED_RGB.c
 *
 *  Created on: 26 Sept 2024
 *      Author: Kenneth
 */
#include "LED_RGB.h"

/*!
 * @brief Initialise board RGB LED with default configurations.
 */
void LED_Init(void){
	// Configuration for LED pins
	LedConfig led_config = {
	    .config = { kGPIO_DigitalOutput, 1 }  // Pin direction as output, Initial logic state = 1 (off)
	};

	/* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortE);

	/* PORTB22 (pin 68) is configured as PTB22 */
	PORT_SetPinMux(PORTB, 22U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTE, 26U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, 21U, kPORT_MuxAsGpio);

	BOARD_InitBootClocks();

	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
}

/*!
 * @brief Turns off the board LED entirely.
 */
void LED_OFF(void){
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 1);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 1);
}

/*!
 * @brief Turns on only the red board LED.
 */
void RED_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
}

/*!
 * @brief Turns on only the green board LED.
 */
void GREEN_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
}

/*!
 * @brief Turns on only the blue board LED.
 */
void BLUE_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}

/*!
 * @brief Turns on both the red and blue board LED's to display magenta.
 */
void MAGENTA_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}

/*!
 * @brief Turns on both the red and green board LED's to display yellow.
 */
void YELLOW_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
}

/*!
 * @brief Turns on both the green and blue board LED's to display cian.
 */
void CIAN_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}

/*!
 * @brief Turns on all board LED's to display white.
 */
void WHITE_LED(void){
	LED_OFF();
	GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, 0);
	GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, 0);
}
