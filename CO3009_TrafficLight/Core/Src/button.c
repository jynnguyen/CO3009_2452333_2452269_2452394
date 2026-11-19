/*
 * button.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */
#include "button.h"
static GPIO_TypeDef* const buttonPorts[BUTTON_COUNT] = {
    BTN_1_GPIO_Port,
    BTN_2_GPIO_Port,
    BTN_3_GPIO_Port,
    BTN_4_GPIO_Port
};
static const uint16_t buttonPins[BUTTON_COUNT] = {
    BTN_1_Pin,
    BTN_2_Pin,
    BTN_3_Pin,
    BTN_4_Pin
};

static GPIO_PinState debounceBuffer0[BUTTON_COUNT];
static GPIO_PinState debounceBuffer1[BUTTON_COUNT];
static GPIO_PinState debounceBuffer2[BUTTON_COUNT];

static GPIO_PinState buttonState[BUTTON_COUNT];

static volatile uint8_t flagForButtonPress[BUTTON_COUNT] = {0};
static volatile uint8_t flagForButtonPress1s[BUTTON_COUNT] = {0};

static uint16_t pressCounter[BUTTON_COUNT] = {0};
void button_read(void)
{
    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
    {

    	debounceBuffer2[i] = debounceBuffer1[i];
        debounceBuffer1[i] = debounceBuffer0[i];
        debounceBuffer0[i] = HAL_GPIO_ReadPin(buttonPorts[i], buttonPins[i]);

        if ((debounceBuffer0[i] == debounceBuffer1[i]) && (debounceBuffer1[i] == debounceBuffer2[i]))
        {

        	if (buttonState[i] == BUTTON_IS_RELEASED && debounceBuffer0[i] == BUTTON_IS_PRESSED)
            {
                flagForButtonPress[i] = 1;
                pressCounter[i] = 0;
            }
            buttonState[i] = debounceBuffer0[i];
            if (buttonState[i] == BUTTON_IS_PRESSED)
            {
                if (pressCounter[i] < DURATION_FOR_AUTO_INCREASING)
                {
                    pressCounter[i]++;
                }
                else
                {
                    flagForButtonPress1s[i] = 1;
                    pressCounter[i] = DURATION_FOR_AUTO_INCREASING - SPEED_FOR_INCREASING;
                }
            }
            else
            {
                pressCounter[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}
uint8_t isButtonPressed(uint8_t index)
{
    if (index >= BUTTON_COUNT) return 0;
    if (flagForButtonPress[index] == 1)
    {
        flagForButtonPress[index] = 0;
        return 1;
    }
    return 0;
}
uint8_t isButtonPressed1s(uint8_t index)
{
    if (index >= BUTTON_COUNT) return 0;
    if (flagForButtonPress1s[index] == 1)
    {
        flagForButtonPress1s[index] = 0;
        return 1;
    }
    return 0;
}

