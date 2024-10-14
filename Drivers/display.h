#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

// Configuration for segment pins
typedef struct {
    gpio_pin_config_t config;
} SegmentConfig;

void DISPLAY_INIT();

void SHOW_NUMBER(uint8_t number, uint8_t display);
void DISPLAY_OFF(void);
