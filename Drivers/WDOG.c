#include "WDOG.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_rcm.h"
#include "fsl_wdog.h"

// Variables estáticas para el WDOG y el RCM
static WDOG_Type *wdog_base = WDOG;
static RCM_Type *rcm_base   = RCM;

void (*wdog_callback)(void) = NULL;

static void WaitWctClose(WDOG_Type *base)
{
    for (uint32_t i = 0; i < WDOG_WCT_INSTRUCTION_COUNT; i++)
    {
        (void)base->RSTCNT;
    }
}

void WDOG_InitConfig(void)
{
    wdog_config_t config;

    // Obtener la configuración por defecto del WDOG
    WDOG_GetDefaultConfig(&config);

    // Configurar el timeout total y la ventana de actualización
    config.timeoutValue     = 0x7ffU;   // Timeout total (por ejemplo, ~2 segundos)

    // Configurar la ventana de actualización en 100 ms
    config.enableWindowMode = true;
    config.windowValue      = WDOG_WINDOW_VALUE;     // Ventana de actualización de 100 ms (100 ticks si el reloj del WDOG es 1 kHz)

    // Inicializar el WDOG con la configuración ajustada
    WDOG_Init(wdog_base, &config);

    // Esperar a que se cierre el temporizador del WDOG
    WaitWctClose(wdog_base);
}

void WDOG_SetCallback(void (*callback)(void)){
	wdog_callback = callback;
}

void CheckWdogReset(void)
{
    // Si el reinicio fue causado por el WDOG
    if (RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog)
    {
        if (wdog_callback != NULL){
           	wdog_callback();
        }
        WDOG_TriggerInfiniteLoop();
    }
}

void WDOG_RefreshWindow(void)
{
    uint32_t current_timer_value = ((uint32_t)wdog_base->TMROUTH << 16U) | wdog_base->TMROUTL;

    // Verificar si estamos dentro de la ventana de actualización
    if (current_timer_value >= WDOG_WINDOW_VALUE)
    {
        WDOG_Refresh(wdog_base);  // Refrescar el WDOG
    }
}

void WDOG_TriggerInfiniteLoop(void)
{
    // Entrar en un lazo infinito
    while (1)
    {
        // El microcontrolador queda bloqueado aquí
    }
}
