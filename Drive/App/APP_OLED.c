#include "OLED.h"
#include "APP_OLED.h"
#include "APP_SHT30.h"

void APP_OLED_init()
{
    OLED_Init();
}

void APP_OLED_refresh()
{
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

    
    SysTick->CTRL &= SysTick_CTRL_TICKINT_Msk;
}