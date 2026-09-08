#include "delay.h"

/* Default reset clock: HSI = 16 MHz */
void Delay_Init(void)
{
    SysTick->LOAD = 16000U - 1U;
    SysTick->VAL = 0U;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U)
        {
        }
    }
}
