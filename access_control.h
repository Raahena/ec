#ifndef ACCESS_CONTROL_H
#define ACCESS_CONTROL_H
#include "stm32f446xx.h"
#define PASSWORD_LENGTH 4
#define MAX_ATTEMPTS 3
#define ACCESS_TIME_MS 3000
#define WRONG_TIME_MS 1000
#define LOCKOUT_TIME_MS 10000
void Access_Control_Run(void);
#endif
