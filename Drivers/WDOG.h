#ifndef _WDOG_H_
#define _WDOG_H_

#include "fsl_wdog.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#define WDOG_TIMEOUT_VALUE (0x7ffU)     // Valor del timeout
#define WDOG_WINDOW_VALUE  (100U)     // Valor de la ventana (100 ms)
#define WDOG_WCT_INSTRUCTION_COUNT 256U

// Inicializa el WDOG.
void WDOG_InitConfig(void);

// Rutina para verificar si el reinicio fue por el WDOG y encender el LED amarillo.
void CheckWdogReset(void);

// Refresca el WDOG dentro de la ventana de actualización.
void WDOG_RefreshWindow(void);

// Función que detiene el programa al activarse el callback desde un botón (e.g., botón STOP).
void WDOG_TriggerInfiniteLoop(void);

void WDOG_SetCallback(void (*callback)(void));

#endif // _WDOG_H_
