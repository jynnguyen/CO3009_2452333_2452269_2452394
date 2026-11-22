/*
 * button.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define BUTTONS_COUNT 4

void button_init();
void button_read();
uint8_t button_is_pressed(uint8_t btnId);
uint8_t button_is_held(uint8_t btnId);

#endif /* INC_BUTTON_H_ */
