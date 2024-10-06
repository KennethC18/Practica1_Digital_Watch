#include "display.h"

gpio_pin_config_t segment_config = {
    kGPIO_DigitalOutput,
    0,
};

void DISPLAY_INIT(){
	//Relojes
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);

	//Configuración segmentos A ... G
	PORT_SetPinMux(PORTD, 0U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 1U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 2U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 3U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 4U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 5U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 6U, kPORT_MuxAsGpio);

	//Configuración ánodos 0 ... 5
	PORT_SetPinMux(PORTC, 0U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, 1U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, 2U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, 3U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, 4U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, 5U, kPORT_MuxAsGpio);

	//Inicialización segmentos A ... G
	GPIO_PinInit(GPIOD, 0u, &segment_config);
	GPIO_PinInit(GPIOD, 1u, &segment_config);
	GPIO_PinInit(GPIOD, 2u, &segment_config);
	GPIO_PinInit(GPIOD, 3u, &segment_config);
	GPIO_PinInit(GPIOD, 4u, &segment_config);
	GPIO_PinInit(GPIOD, 5u, &segment_config);
	GPIO_PinInit(GPIOD, 6u, &segment_config);

	//Inicialización ánodos 0 ... 5
	GPIO_PinInit(GPIOC, 0u, &segment_config);
	GPIO_PinInit(GPIOC, 1u, &segment_config);
	GPIO_PinInit(GPIOC, 2u, &segment_config);
	GPIO_PinInit(GPIOC, 3u, &segment_config);
	GPIO_PinInit(GPIOC, 4u, &segment_config);
	GPIO_PinInit(GPIOC, 5u, &segment_config);
	};

const uint8_t numbers[10] = {
    0b00111111,  // 0 -> a, b, c, d, e, f
    0b00000110,  // 1 -> b, c
    0b01011011,  // 2 -> a, b, d, e, g
    0b01001111,  // 3 -> a, b, c, d, g
    0b01100110,  // 4 -> b, c, f, g
    0b01101101,  // 5 -> a, c, d, f, g
    0b01111101,  // 6 -> a, c, d, e, f, g
    0b00000111,  // 7 -> a, b, c
    0b01111111,  // 8 -> a, b, c, d, e, f, g
    0b01101111   // 9 -> a, b, c, d, f, g
};

//Funci
void SHOW_NUMBER(uint8_t number, uint8_t display){
	//Apaga los segmentos
	GPIO_PortSet(GPIOD, 0x7F);

	//Enciende los segmentos para el número
	GPIO_PortClear(GPIOD, numbers[number]);

	//Apaga los ánodos
	GPIO_PortClear(GPIOC, 0x3F);  // Apagar PTC0-PTC5 (ánodos)

	//Enciende el ánodo correspondiente
	GPIO_PortSet(GPIOC, (1 << display));

}
