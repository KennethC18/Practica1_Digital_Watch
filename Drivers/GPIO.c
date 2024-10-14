/*
 * GPIO.c
 *
 *  Created on: 26 Sept 2024
 *      Author: Kenneth
 */
#include "GPIO.h"

GPIO_Callback_t Port_A_Callback = NULL;
GPIO_Callback_t Port_B_Callback = NULL;
GPIO_Callback_t Port_C_Callback = NULL;

uint32_t PORTA_flags, PORTB_flags, PORTC_flags;

/*!
 * brief Sets the callback function to the indicated GPIO port.
 *
 * param dacValue Setting the value for the next item in the buffer.
 */
void GPIO_Set_Callback(GPIO_Callback_t callback, GPIO_Type *GPIO){
	if(GPIO == GPIOA){
		Port_A_Callback = callback;
	}
	else if(GPIO == GPIOB){
		Port_B_Callback = callback;
	}
	else if(GPIO == GPIOC){
		Port_C_Callback = callback;
	}
	else{
		Port_A_Callback = NULL;
		Port_B_Callback = NULL;
		Port_C_Callback = NULL;
	}
}

/*!
 * @brief Handle interrupts from the GPIO Port A.
 */
void PORTA_IRQHandler(void)
{
	PORTA_flags = GPIO_PortGetInterruptFlags(GPIOA);

	if(Port_A_Callback != NULL){
		Port_A_Callback(PORTA_flags);
	}

	/* Clear external interrupt flag. */
	GPIO_PortClearInterruptFlags(GPIOA, PORTA_flags);

    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Handle interrupts from the GPIO Port B.
 */
void PORTB_IRQHandler(void)
{
	PORTB_flags = GPIO_PortGetInterruptFlags(GPIOB);

	if(Port_B_Callback != NULL){
		Port_B_Callback(PORTB_flags);
	}

	/* Clear external interrupt flag. */
	GPIO_PortClearInterruptFlags(GPIOB, PORTB_flags);

    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Handle interrupts from the GPIO Port C.
 */
void PORTC_IRQHandler(void)
{
	PORTC_flags = GPIO_PortGetInterruptFlags(GPIOC);

	if(Port_C_Callback != NULL){
		Port_C_Callback(PORTC_flags);
	}

	/* Clear external interrupt flag. */
	GPIO_PortClearInterruptFlags(GPIOC, PORTC_flags);

    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Set default configuration and initialise GPIO.
 */
void GPIO_Start(void){
	/* Define the init structure for the input switch pin */
	gpio_pin_config_t sw_config = {
		kGPIO_DigitalInput,
		0,
	};

	/* Configuration for input pin */
	const port_pin_config_t pcr_port_sw_config = {
		kPORT_PullUp,
		kPORT_FastSlewRate,
		kPORT_PassiveFilterEnable,
		kPORT_OpenDrainDisable,
		kPORT_LowDriveStrength,
		kPORT_MuxAsGpio,
		kPORT_UnlockRegister
	};

	/* Enable port clocks */
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);

	BOARD_InitBootClocks();

	/* Button pin input configuration*/
	PORT_SetPinConfig(TIME_STOPWATCH_BTN_PORT, TIME_STOPWATCH_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(TIME_ALARM_BTN_PORT, TIME_ALARM_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(CONFIG_BTN_PORT, CONFIG_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(HOUR_START_BTN_PORT, HOUR_START_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(MIN_STOP_BTN_PORT, MIN_STOP_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(CLEAR_BTN_PORT, CLEAR_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(ALARM_ON_BTN_PORT, ALARM_ON_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(STOP_BTN_PORT, STOP_BTN_PIN, &pcr_port_sw_config);

	/* Button pin interrupt configuration */
	PORT_SetPinInterruptConfig(TIME_STOPWATCH_BTN_PORT, TIME_STOPWATCH_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(TIME_ALARM_BTN_PORT, TIME_ALARM_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(CONFIG_BTN_PORT, CONFIG_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(HOUR_START_BTN_PORT, HOUR_START_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(MIN_STOP_BTN_PORT, MIN_STOP_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(CLEAR_BTN_PORT, CLEAR_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(ALARM_ON_BTN_PORT, ALARM_ON_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(STOP_BTN_PORT, STOP_BTN_PIN, kPORT_InterruptFallingEdge);

	/* Button ports interrupt priority configuration */
	NVIC_SetPriority(PORTA_IRQn, 0);
    EnableIRQ(PORTA_IRQn);
    NVIC_SetPriority(PORTB_IRQn, 0);
    EnableIRQ(PORTB_IRQn);
    NVIC_SetPriority(PORTC_IRQn, 0);
    EnableIRQ(PORTC_IRQn);

    /* Button pins initialisation */
    GPIO_PinInit(TIME_STOPWATCH_BTN_PORT, TIME_STOPWATCH_BTN_PIN, &sw_config);
    GPIO_PinInit(TIME_ALARM_BTN_PORT, TIME_ALARM_BTN_PIN, &sw_config);
    GPIO_PinInit(CONFIG_BTN_PORT, CONFIG_BTN_PIN, &sw_config);
    GPIO_PinInit(HOUR_START_BTN_PORT, HOUR_START_BTN_PIN, &sw_config);
    GPIO_PinInit(MIN_STOP_BTN_PORT, MIN_STOP_BTN_PIN, &sw_config);
    GPIO_PinInit(CLEAR_BTN_PORT, CLEAR_BTN_PIN, &sw_config);
    GPIO_PinInit(ALARM_ON_BTN_PORT, ALARM_ON_BTN_PIN, &sw_config);
    GPIO_PinInit(STOP_BTN_PORT, STOP_BTN_PIN, &sw_config);
}
