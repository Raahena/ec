#include "gpio.h"

void GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN |
                    RCC_AHB1ENR_GPIOBEN |
                    RCC_AHB1ENR_GPIOCEN;
    (void)RCC->AHB1ENR;

    /* PA6 green LED, PB5 red LED, PB10 buzzer = outputs */
    GPIOA->MODER &= ~(3U << 12);
    GPIOA->MODER |=  (1U << 12);
    GPIOB->MODER &= ~((3U << 10) | (3U << 20));
    GPIOB->MODER |=  ((1U << 10) | (1U << 20));

    GPIOA->OTYPER &= ~(1U << 6);
    GPIOB->OTYPER &= ~((1U << 5) | (1U << 10));

    GPIOA->PUPDR &= ~(3U << 12);
    GPIOB->PUPDR &= ~((3U << 10) | (3U << 20));

    /* PB0 IR input, active LOW */
    GPIOB->MODER &= ~(3U << 0);
    GPIOB->PUPDR &= ~(3U << 0);

    /* PC0-PC3 keypad rows = outputs */
    for (uint32_t pin = 0; pin < 4; pin++)
    {
        GPIOC->MODER &= ~(3U << (pin * 2));
        GPIOC->MODER |=  (1U << (pin * 2));
        GPIOC->OTYPER &= ~(1U << pin);
        GPIOC->PUPDR &= ~(3U << (pin * 2));
    }

    /* PC4-PC7 keypad columns = inputs with pull-ups */
    for (uint32_t pin = 4; pin < 8; pin++)
    {
        GPIOC->MODER &= ~(3U << (pin * 2));
        GPIOC->PUPDR &= ~(3U << (pin * 2));
        GPIOC->PUPDR |=  (1U << (pin * 2));
    }

    GPIOC->BSRR = GPIO_PIN_0 | GPIO_PIN_1 |
                  GPIO_PIN_2 | GPIO_PIN_3;

    Green_LED_Off();
    Red_LED_Off();
    Buzzer_Off();
}

void Green_LED_On(void)  { GREEN_PORT->BSRR = GREEN_PIN; }
void Green_LED_Off(void) { GREEN_PORT->BSRR = ((uint32_t)GREEN_PIN << 16); }
void Red_LED_On(void)    { RED_PORT->BSRR = RED_PIN; }
void Red_LED_Off(void)   { RED_PORT->BSRR = ((uint32_t)RED_PIN << 16); }
void Buzzer_On(void)     { BUZZER_PORT->BSRR = BUZZER_PIN; }
void Buzzer_Off(void)    { BUZZER_PORT->BSRR = ((uint32_t)BUZZER_PIN << 16); }

uint8_t IR_Detected(void)
{
    return ((IR_PORT->IDR & IR_PIN) == 0U);
}
