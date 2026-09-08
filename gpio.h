#ifndef GPIO_H
#define GPIO_H
#include "stm32f446xx.h"

#define IR_PORT GPIOB
#define IR_PIN GPIO_PIN_0
#define GREEN_PORT GPIOA
#define GREEN_PIN GPIO_PIN_6
#define RED_PORT GPIOB
#define RED_PIN GPIO_PIN_5
#define BUZZER_PORT GPIOB
#define BUZZER_PIN GPIO_PIN_10

void GPIO_Init(void);
void Green_LED_On(void);
void Green_LED_Off(void);
void Red_LED_On(void);
void Red_LED_Off(void);
void Buzzer_On(void);
void Buzzer_Off(void);
uint8_t IR_Detected(void);
#endif
