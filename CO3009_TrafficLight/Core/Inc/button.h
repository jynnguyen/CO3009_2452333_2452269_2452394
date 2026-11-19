/*
 * button.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#define BUTTON_COUNT                 4
#define BUTTON_IS_PRESSED            GPIO_PIN_RESET
#define BUTTON_IS_RELEASED           GPIO_PIN_SET
#define DURATION_FOR_AUTO_INCREASING 100
#define SPEED_FOR_INCREASING         20

enum ButtonIndex
{
    BTN_INDEX_1 = 0,
    BTN_INDEX_2,
    BTN_INDEX_3,
    BTN_INDEX_4
};

void button_read(void);

uint8_t isButtonPressed(uint8_t index);

uint8_t isButtonPressed1s(uint8_t index);

#define button_reading        button_read
#define is_button_pressed     isButtonPressed
#define is_button_pressed_1s  isButtonPressed1s

#endif /* INC_BUTTON_H_ */
