#include "keypad.h"
#include "delay.h"

static const char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

static const uint16_t rows[4] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3
};

static const uint16_t cols[4] = {
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7
};

char Keypad_GetKey(void)
{
    for (uint32_t row = 0; row < 4; row++)
    {
        GPIOC->BSRR = GPIO_PIN_0 | GPIO_PIN_1 |
                      GPIO_PIN_2 | GPIO_PIN_3;

        GPIOC->BSRR = ((uint32_t)rows[row] << 16);
        Delay_ms(1);

        for (uint32_t col = 0; col < 4; col++)
        {
            if ((GPIOC->IDR & cols[col]) == 0U)
            {
                Delay_ms(20);

                if ((GPIOC->IDR & cols[col]) == 0U)
                {
                    while ((GPIOC->IDR & cols[col]) == 0U)
                    {
                    }
                    return keymap[row][col];
                }
            }
        }
    }
    return 0;
}
