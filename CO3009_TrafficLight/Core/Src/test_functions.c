/*
 * test_functions.c
 *
 *  Created on: Nov 4, 2026
 *      Author: jynng
 */


#include "main.h"
#include "test_functions.h"

uint8_t i2c_found[8];
extern I2C_HandleTypeDef hi2c1;

void test_blink()
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(500);
}

void test_signal_combinations()
{
	// Try the 4 combinations (0,0) (0,1) (1,0) (1,1) in turn, holding each for 2 seconds
	for (int i = 0; i < 4; i++)
	{
		// D3 - D4
		HAL_GPIO_WritePin(TL1_A_GPIO_Port, TL1_A_Pin, (i >> 1) & 1);
		HAL_GPIO_WritePin(TL1_B_GPIO_Port, TL1_B_Pin, i & 1);

		// D5 - D6
		HAL_GPIO_WritePin(TL2_A_GPIO_Port, TL2_A_Pin, (i >> 1) & 1);
		HAL_GPIO_WritePin(TL2_B_GPIO_Port, TL2_B_Pin, i & 1);

		HAL_Delay(2000);
	}

}

void test_buttons()
{
    if (HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(BTN_4_GPIO_Port, BTN_4_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}

void test_i2c()
{
    int i2c_count = 0;

    for (uint8_t addr = 1; addr < 128; addr++)
    {
        if (HAL_I2C_IsDeviceReady(&hi2c1, addr << 1, 1, 10) == HAL_OK)
            if (i2c_count < 8)
                i2c_found[i2c_count++] = addr;
    }

    // LED PA5 blinks 3 times if found
    if (i2c_count >= 2)
    {
        for (int k = 0; k < 3; k++)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            HAL_Delay(100);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            HAL_Delay(100);
        }
    }
}
