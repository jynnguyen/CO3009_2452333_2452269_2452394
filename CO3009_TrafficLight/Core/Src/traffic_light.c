/*
 * traffic_light.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */
#include "traffic_light.h"

#define SIG_OFF_A       0
#define SIG_OFF_B       0
#define SIG_AMBER_A     0
#define SIG_AMBER_B     1
#define SIG_GREEN_A     1
#define SIG_GREEN_B     0
#define SIG_RED_A       1
#define SIG_RED_B       1

static uint8_t toggle_state_road1 = 0;
static uint8_t toggle_state_road2 = 0;

static void set_light_signals(uint8_t road, uint8_t sig_a, uint8_t sig_b)
{
    if (road == ROAD_1)
    {
        HAL_GPIO_WritePin(TL1_A_GPIO_Port, TL1_A_Pin, sig_a ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(TL1_B_GPIO_Port, TL1_B_Pin, sig_b ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if (road == ROAD_2)
    {
        HAL_GPIO_WritePin(TL2_A_GPIO_Port, TL2_A_Pin, sig_a ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(TL2_B_GPIO_Port, TL2_B_Pin, sig_b ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}
void traffic_init(void)
{
	traffic_set(ROAD_1, LIGHT_OFF);
    traffic_set(ROAD_2, LIGHT_OFF);
}
void traffic_set(uint8_t road, LightColor color)
{
    if (road == ROAD_1) road1_color = color;
    else if (road == ROAD_2) road2_color = color;
    switch (color)
    {
        case LIGHT_GREEN:
            set_light_signals(road, SIG_GREEN_A, SIG_GREEN_B);
            break;
        case LIGHT_AMBER:
            set_light_signals(road, SIG_AMBER_A, SIG_AMBER_B);
            break;
        case LIGHT_RED:
            set_light_signals(road, SIG_RED_A, SIG_RED_B);
            break;
        case LIGHT_OFF:
        default:
            set_light_signals(road, SIG_OFF_A, SIG_OFF_B);
            break;
    }
}
void traffic_toggle(uint8_t road, LightColor color)
{
    if (road == ROAD_1)
    {
        toggle_state_road1 = !toggle_state_road1;
        if (toggle_state_road1)
        {
            traffic_set(ROAD_1, color);
        }
        else
        {
            traffic_set(ROAD_1, LIGHT_OFF);
        }
    }
    else if (road == ROAD_2)
    {
        toggle_state_road2 = !toggle_state_road2;
        if (toggle_state_road2)
        {
            traffic_set(ROAD_2, color);
        }
        else
        {
            traffic_set(ROAD_2, LIGHT_OFF);
        }
    }
}
void traffic_off_all(void)
{
    traffic_set(ROAD_1, LIGHT_OFF);
    traffic_set(ROAD_2, LIGHT_OFF);
}

