/*
 * GPIO.c
 *
 *  Created on: 26 Sept 2024
 *      Author: kenneth
 */
#include "GPIO.h"

void (*Port_A_Callback)(uint32_t) = NULL;
void (*Port_B_Callback)(uint32_t) = NULL;
void (*Port_C_Callback)(uint32_t) = NULL;

uint32_t PORTA_flags, PORTB_flags, PORTC_flags;

void GPIO_Set_Callback(void (*callback)(uint32_t), GPIO_Type *base){
	if(base == GPIOA){
		Port_A_Callback = callback;
	}
	else if(base == GPIOB){
		Port_B_Callback = callback;
	}
	else if(base == GPIOC){
		Port_C_Callback = callback;
	}
	else{
		Port_A_Callback = NULL;
		Port_B_Callback = NULL;
		Port_C_Callback = NULL;
	}
}

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

void GPIO_Start(void){
	/* Define the init structure for the input switch pin */
	gpio_pin_config_t sw_config = {
		kGPIO_DigitalInput,
		0,
	};

	const port_pin_config_t pcr_port_sw_config = {
		kPORT_PullUp,
		kPORT_FastSlewRate,
		kPORT_PassiveFilterEnable,
		kPORT_OpenDrainDisable,
		kPORT_LowDriveStrength,
		kPORT_MuxAsGpio,
		kPORT_UnlockRegister
	};

	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);

	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	PORT_SetPinConfig(TIME_STOPWATCH_BTN_PORT, TIME_STOPWATCH_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(TIME_ALARM_BTN_PORT, TIME_ALARM_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(CONFIG_BTN_PORT, CONFIG_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(HOUR_START_BTN_PORT, HOUR_START_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(MIN_STOP_BTN_PORT, MIN_STOP_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(CLEAR_BTN_PORT, CLEAR_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(ALARM_ON_BTN_PORT, ALARM_ON_BTN_PIN, &pcr_port_sw_config);
	PORT_SetPinConfig(STOP_BTN_PORT, STOP_BTN_PIN, &pcr_port_sw_config);

	PORT_SetPinInterruptConfig(TIME_STOPWATCH_BTN_PORT, TIME_STOPWATCH_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(TIME_ALARM_BTN_PORT, TIME_ALARM_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(CONFIG_BTN_PORT, CONFIG_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(HOUR_START_BTN_PORT, HOUR_START_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(MIN_STOP_BTN_PORT, MIN_STOP_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(CLEAR_BTN_PORT, CLEAR_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(ALARM_ON_BTN_PORT, ALARM_ON_BTN_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(STOP_BTN_PORT, STOP_BTN_PIN, kPORT_InterruptFallingEdge);

    EnableIRQ(PORTA_IRQn);
    EnableIRQ(PORTB_IRQn);
    EnableIRQ(PORTC_IRQn);

    /*buttons INIT*/
    GPIO_PinInit(TIME_STOPWATCH_BTN_PORT, TIME_STOPWATCH_BTN_PIN, &sw_config);
    GPIO_PinInit(TIME_ALARM_BTN_PORT, TIME_ALARM_BTN_PIN, &sw_config);
    GPIO_PinInit(CONFIG_BTN_PORT, CONFIG_BTN_PIN, &sw_config);
    GPIO_PinInit(HOUR_START_BTN_PORT, HOUR_START_BTN_PIN, &sw_config);
    GPIO_PinInit(MIN_STOP_BTN_PORT, MIN_STOP_BTN_PIN, &sw_config);
    GPIO_PinInit(CLEAR_BTN_PORT, CLEAR_BTN_PIN, &sw_config);
    GPIO_PinInit(ALARM_ON_BTN_PORT, ALARM_ON_BTN_PIN, &sw_config);
    GPIO_PinInit(STOP_BTN_PORT, STOP_BTN_PIN, &sw_config);
}
