#include "main.h"

int main(void)
{
    GPIO_Init();
    Delay_Init();

    Green_LED_Off();
    Red_LED_Off();
    Buzzer_Off();

    while (1)
    {
        Access_Control_Run();
        Delay_ms(50);
    }
}
