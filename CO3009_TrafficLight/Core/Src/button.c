/*
 * button.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "button.h"

#define BUTTON_PRESSED  GPIO_PIN_RESET
#define BUTTON_RELEASED GPIO_PIN_SET

static GPIO_TypeDef* btn_ports[BUTTONS_COUNT] = {BTN_1_GPIO_Port, BTN_2_GPIO_Port, BTN_3_GPIO_Port, BTN_4_GPIO_Port};
static uint16_t btn_pins[BUTTONS_COUNT] = {BTN_1_Pin, BTN_2_Pin, BTN_3_Pin, BTN_4_Pin};

static GPIO_PinState btn_reg0[BUTTONS_COUNT];
static GPIO_PinState btn_reg1[BUTTONS_COUNT];
static GPIO_PinState btn_reg2[BUTTONS_COUNT];
static GPIO_PinState btn_reg3[BUTTONS_COUNT];

static uint8_t btn_pressed_flag[BUTTONS_COUNT] = {};
static uint8_t btn_held_flag[BUTTONS_COUNT] = {};
static uint16_t btn_held_time[BUTTONS_COUNT] = {};

static void button_update_reg(uint8_t btnId)
{
	btn_reg0[btnId] = btn_reg1[btnId];
	btn_reg1[btnId] = btn_reg2[btnId];
	btn_reg2[btnId] = HAL_GPIO_ReadPin(btn_ports[btnId], btn_pins[btnId]);
}

void button_init()
{
	 for (uint8_t i = 0; i < BUTTONS_COUNT; i++)
	 {
		 btn_reg0[i] = BUTTON_RELEASED;
		 btn_reg1[i] = BUTTON_RELEASED;
		 btn_reg2[i] = BUTTON_RELEASED;
		 btn_reg3[i] = BUTTON_RELEASED;
		 btn_pressed_flag[i] = 0;
		 btn_held_flag[i] = 0;
		 btn_held_time[i] = 0;
	}
}

void button_read()
{
	for(uint8_t i = 0;i < BUTTONS_COUNT; i++)
	{
		button_update_reg(i);

		if(btn_reg0[i] == btn_reg1[i] && btn_reg1[i] == btn_reg2[i])
		{
			if(btn_reg2[i] != btn_reg3[i])
			{
				btn_reg3[i] = btn_reg2[i];
				if (btn_reg3[i] == BUTTON_PRESSED)
				{
					btn_pressed_flag[i] = 1;
					btn_held_time[i] = 0;
				}
			}

			else if(btn_reg3[i] == BUTTON_PRESSED)
			{
				btn_held_time[i]++;
				if(btn_held_time[i] >= 100)
				{
					btn_held_flag[i] = 1;
					btn_held_time[i] -= 50;
				}
			}
		}
	}
}

uint8_t button_is_pressed(uint8_t btnId)
{
	if (btnId >= BUTTONS_COUNT)
		return 0;
	if (btn_pressed_flag[btnId] == 1)
	{
		btn_pressed_flag[btnId] = 0;
		return 1;
	}

	return 0;
}

uint8_t button_is_held(uint8_t btnId)
{
	if (btnId >= BUTTONS_COUNT)
			return 0;
	if (btn_held_flag[btnId] == 1)
	{
		btn_held_flag[btnId] = 0;
		return 1;
	}

	return 0;
}
