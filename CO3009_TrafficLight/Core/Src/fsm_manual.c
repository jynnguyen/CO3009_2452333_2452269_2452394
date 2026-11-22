/*
 * fsm_manual.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */
#include "fsm_manual.h"
void fsm_manual_init(void)
{
    manual_state = MAN_INIT;
}
void fsm_manual_run(void)
{
    if (system_mode != MODE_MANUAL)
    {
        return;
    }
    switch (manual_state)
    {
        case MAN_INIT:
            if (road1_color == LIGHT_GREEN || road1_color == LIGHT_AMBER)
            {
                manual_state = MAN_GREEN1_RED2;
                traffic_set(ROAD_1, LIGHT_GREEN);
                traffic_set(ROAD_2, LIGHT_RED);
            }
            else
            {
                manual_state = MAN_RED1_GREEN2;
                traffic_set(ROAD_1, LIGHT_RED);
                traffic_set(ROAD_2, LIGHT_GREEN);
            }
            break;
        case MAN_RED1_GREEN2:
            traffic_set(ROAD_1, LIGHT_RED);
            traffic_set(ROAD_2, LIGHT_GREEN);
            if (isButtonPressed(BTN_INDEX_2))
            {
                manual_state = MAN_RED1_AMBER2;
            }
            break;
        case MAN_RED1_AMBER2:
            traffic_set(ROAD_1, LIGHT_RED);
            traffic_set(ROAD_2, LIGHT_AMBER);
            if (isButtonPressed(BTN_INDEX_2))
            {
                manual_state = MAN_GREEN1_RED2;
            }
            break;
        case MAN_GREEN1_RED2:
            traffic_set(ROAD_1, LIGHT_GREEN);
            traffic_set(ROAD_2, LIGHT_RED);
            if (isButtonPressed(BTN_INDEX_2))
            {
                manual_state = MAN_AMBER1_RED2;
            }
            break;
        case MAN_AMBER1_RED2:
            traffic_set(ROAD_1, LIGHT_AMBER);
            traffic_set(ROAD_2, LIGHT_RED);
            if (isButtonPressed(BTN_INDEX_2))
            {
                manual_state = MAN_RED1_GREEN2;
            }
            break;
        default:
            manual_state = MAN_INIT;
            break;
    }
    if (isButtonPressed(BTN_INDEX_1))
    {
        system_mode = MODE_TUNING;
        tuning_mode = TUNING_INIT;
    }
}

