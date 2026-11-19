/*
 * fsm_tuning.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "fsm_tuning.h"
#define BLINK_HALF_PERIOD_MS    250
void fsm_tuning_init(void)
{
    tuning_mode = TUNING_INIT;
}
void fsm_tuning_run(void)
{
    if (system_mode != MODE_TUNING)
    {
        return;
    }
    switch (tuning_mode)
    {
        case TUNING_INIT:
            tuning_mode = TUNING_RED;
            temp_duration = time_red;
            traffic_off_all();
            setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            break;
        case TUNING_RED:
            if (isTimerExpired(TIMER_BLINK))
            {
                traffic_toggle(ROAD_1, LIGHT_RED);
                traffic_toggle(ROAD_2, LIGHT_RED);
                setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            }
            if (isButtonPressed(BTN_INDEX_2))
            {
                tuning_mode = TUNING_AMBER;
                temp_duration = time_amber;
                traffic_off_all();
                setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            }
            if (isButtonPressed(BTN_INDEX_4))
            {
                time_red = temp_duration;
            }
            break;
        case TUNING_AMBER:
            if (isTimerExpired(TIMER_BLINK))
            {
                traffic_toggle(ROAD_1, LIGHT_AMBER);
                traffic_toggle(ROAD_2, LIGHT_AMBER);
                setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            }
            if (isButtonPressed(BTN_INDEX_2))
            {
                tuning_mode = TUNING_GREEN;
                temp_duration = time_green;
                traffic_off_all();
                setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            }
            if (isButtonPressed(BTN_INDEX_4))
            {
                time_amber = temp_duration;
            }
            break;
        case TUNING_GREEN:
            if (isTimerExpired(TIMER_BLINK))
            {
                traffic_toggle(ROAD_1, LIGHT_GREEN);
                traffic_toggle(ROAD_2, LIGHT_GREEN);
                setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            }
            if (isButtonPressed(BTN_INDEX_2))
            {
                tuning_mode = TUNING_RED;
                temp_duration = time_red;
                traffic_off_all();
                setTimer(TIMER_BLINK, BLINK_HALF_PERIOD_MS);
            }
            if (isButtonPressed(BTN_INDEX_4))
            {
                time_green = temp_duration;
            }
            break;
        default:
            tuning_mode = TUNING_INIT;
            break;
    }
    if (isButtonPressed(BTN_INDEX_3) || isButtonPressed1s(BTN_INDEX_3))
    {
        temp_duration++;
        if (temp_duration > 99)
        {
            temp_duration = 1;
        }
    }
    if (isButtonPressed(BTN_INDEX_1))
    {
        if (time_red != (time_green + time_amber))
        {
            time_red = time_green + time_amber;
        }
        if (time_green == 0) time_green = 3;
        if (time_amber == 0) time_amber = 2;
        if (time_red == 0)   time_red   = 5;
        system_mode = MODE_AUTO;
        fsm_automatic_init();
    }
}
