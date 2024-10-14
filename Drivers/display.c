#include "display.h"

// Define macros for magic numbers
#define ALL_SEGMENTS (0x7F)  // All segments: A-G
#define ALL_ANODES   (0x3F)  // All anodes: 0-5

/*!
 * @brief Initialises the display.
 *
 * Enables clocks for PORTD and PORTC, configures pins for segments A-G and anodes 0-5.
 */
void DISPLAY_INIT(void) {
	// Configuration for segment pins
	SegmentConfig segment_config = {
	    .config = { kGPIO_DigitalOutput, 0 }
	};

    // Clocks
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortC);

    // Configuration segments A ... G
    PORT_SetPinMux(PORTD, 0U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 1U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 2U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 3U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 4U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 5U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 6U, kPORT_MuxAsGpio);

    // Configuration anodes 0 ... 5
    PORT_SetPinMux(PORTC, 0U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 1U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 2U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 3U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 4U, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 5U, kPORT_MuxAsGpio);

    // Initialise segments A ... G
    GPIO_PinInit(GPIOD, 0U, &segment_config.config);
    GPIO_PinInit(GPIOD, 1U, &segment_config.config);
    GPIO_PinInit(GPIOD, 2U, &segment_config.config);
    GPIO_PinInit(GPIOD, 3U, &segment_config.config);
    GPIO_PinInit(GPIOD, 4U, &segment_config.config);
    GPIO_PinInit(GPIOD, 5U, &segment_config.config);
    GPIO_PinInit(GPIOD, 6U, &segment_config.config);

    // Initialise anodes 0 ... 5
    GPIO_PinInit(GPIOC, 0U, &segment_config.config);
    GPIO_PinInit(GPIOC, 1U, &segment_config.config);
    GPIO_PinInit(GPIOC, 2U, &segment_config.config);
    GPIO_PinInit(GPIOC, 3U, &segment_config.config);
    GPIO_PinInit(GPIOC, 4U, &segment_config.config);
    GPIO_PinInit(GPIOC, 5U, &segment_config.config);
}

// Definition of numbers
const uint8_t numbers[] = {
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

/*!
 * @brief Displays a number on the 7-segment display.
 *
 * @param number Number to display (0-9).
 * @param display Position of the display to use.
 */
void SHOW_NUMBER(uint8_t number, uint8_t display) {
    // Turn off all segments
    GPIO_PortSet(GPIOD, ALL_SEGMENTS);

    // Turn on the segments for the number
    GPIO_PortClear(GPIOD, numbers[number]);

    // Turn off all anodes
    GPIO_PortClear(GPIOC, ALL_ANODES);  // Turn off PTC0-PTC5 (anodes)

    // Turn on the corresponding anode
    GPIO_PortSet(GPIOC, (1 << display));
}

/*!
 * @brief Turns off the display.
 */
void DISPLAY_OFF(void) {
    GPIO_PortSet(GPIOD, ALL_SEGMENTS);
    GPIO_PortClear(GPIOC, ALL_ANODES);  // Turn off PTC0-PTC5 (anodes)
}
