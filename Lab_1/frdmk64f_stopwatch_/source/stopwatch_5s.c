#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_CoreSysClk)
volatile uint32_t g_systickCounter;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void convert(int sec)
{
	char und_hr[50] = "0";

	int hr = floor(sec/3600);
	char hour[50];
	sprintf(hour, "%d", hr);
	if(strlen(hour) < 2) PRINTF(strcat(und_hr, hour));
	else PRINTF(hour);
	PRINTF(":");

	char und_min[50] = "0";
	sec = sec - hr * 3600;
	int min = floor(sec/60);
	char minute[50];
	sprintf(minute, "%d", min);
	if(strlen(minute) < 2) PRINTF(strcat(und_min, minute));
	else PRINTF(minute);
	PRINTF(":");

	char und_sec[50] = "0";
	sec = sec - min * 60;
	char second[50];
	sprintf(second, "%d", sec);
	if(strlen(second) < 2) PRINTF(strcat(und_sec, second));
	else PRINTF(second);

}


void SysTick_Handler(void)
{
    if (g_systickCounter != 0U) g_systickCounter--;
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U) {}
}

int main(void)
{
    char ch;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

	if (SysTick_Config(SystemCoreClock / 1000U))
	{
		while (1)
		{
		}
	}

    int count = 0;
    while (1)
    {
    	if(count%5 == 0) {
    		convert(count);
    		PRINTF("\n");
    	}
    	SysTick_DelayTicks(1000U);
    	count++;
    }
}
