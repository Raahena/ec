#include "access_control.h"
#include "gpio.h"
#include "keypad.h"
#include "delay.h"

static const char correct_password[PASSWORD_LENGTH + 1] = "1234";

static uint8_t CheckPassword(void)
{
    char entered[PASSWORD_LENGTH + 1];
    char key;
    uint8_t index = 0;

    while (1)
    {
        key = Keypad_GetKey();
        if (key == 0)
            continue;

        if (key >= '0' && key <= '9')
        {
            if (index < PASSWORD_LENGTH)
                entered[index++] = key;
        }
        else if (key == '*')
        {
            index = 0;
        }
        else if (key == '#')
        {
            if (index != PASSWORD_LENGTH)
                return 0;

            entered[index] = '\0';

            for (index = 0; index < PASSWORD_LENGTH; index++)
            {
                if (entered[index] != correct_password[index])
                    return 0;
            }
            return 1;
        }
    }
}

static void Wrong_Attempt(void)
{
    Green_LED_Off();
    Red_LED_On();
    Buzzer_On();
    Delay_ms(WRONG_TIME_MS);
    Red_LED_Off();
    Buzzer_Off();
    Delay_ms(500);
}

static void Lockout(void)
{
    Green_LED_Off();
    Red_LED_On();
    Buzzer_On();
    Delay_ms(LOCKOUT_TIME_MS);
    Red_LED_Off();
    Buzzer_Off();
}

void Access_Control_Run(void)
{
    uint8_t attempts = 0;

    if (!IR_Detected())
        return;

    Green_LED_On();
    Delay_ms(500);

    while (attempts < MAX_ATTEMPTS)
    {
        if (CheckPassword())
        {
            Green_LED_On();
            Red_LED_Off();
            Buzzer_Off();
            Delay_ms(ACCESS_TIME_MS);
            Green_LED_Off();
            return;
        }

        attempts++;
        Wrong_Attempt();

        if (attempts >= MAX_ATTEMPTS)
        {
            Lockout();
            return;
        }
    }
}
