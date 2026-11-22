/*
 * traffic_light.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "traffic_light.h"

static void traffic_write(uint8_t roadNum, uint8_t signalAB)
{
	uint8_t signalA = signalAB / 10;
	uint8_t signalB = signalAB % 10;

	if(roadNum == 1)
	{
		HAL_GPIO_WritePin(TL1_A_GPIO_Port, TL1_A_Pin, signalA ? GPIO_PIN_SET : GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TL1_B_GPIO_Port, TL1_B_Pin, signalB ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}
	else if(roadNum == 2)
	{
		HAL_GPIO_WritePin(TL2_A_GPIO_Port, TL2_A_Pin, signalA ? GPIO_PIN_SET : GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TL2_B_GPIO_Port, TL2_B_Pin, signalB ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}
}

void traffic_init()
{
	traffic_set(1, LIGHT_OFF);
	traffic_set(2, LIGHT_OFF);
}

void traffic_set(uint8_t roadNum, LightState color)
{
	switch(color)
	{
		case LIGHT_OFF:
			traffic_write(roadNum, 00);
			break;

		case LIGHT_AMBER:
			traffic_write(roadNum, 01);
			break;

		case LIGHT_GREEN:
			traffic_write(roadNum, 10);
			break;

		case LIGHT_RED:
			traffic_write(roadNum, 11);
			break;
	}
}
