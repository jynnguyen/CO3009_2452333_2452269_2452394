/*
 * fsm_automatic.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "fsm_automatic.h"

void fsm_automatic_init(void)
{
    auto_state = AUTO_INIT;
}

void fsm_automatic_run(void)
{
    if (system_mode != MODE_AUTO)
    {
        return;
    }

    if (isTimerExpired(TIMER_COUNTDOWN))
    {
        if (countdown_road1 > 0) countdown_road1--;
        if (countdown_road2 > 0) countdown_road2--;
        setTimer(TIMER_COUNTDOWN, 1000);
    }

    switch (auto_state)
    {
        case AUTO_INIT:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_GREEN);

            countdown_road1 = time_red;
            countdown_road2 = time_green;

            setTimer(TIMER_TRAFFIC, (uint32_t)time_green * 1000);
            setTimer(TIMER_COUNTDOWN, 1000);

            auto_state = AUTO_RED1_GREEN2;
            break;

        case AUTO_RED1_GREEN2:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_GREEN);

            if (isTimerExpired(TIMER_TRAFFIC))
            {
                auto_state = AUTO_RED1_AMBER2;
                traffic_set(1, LIGHT_RED);
                traffic_set(2, LIGHT_AMBER);
                countdown_road2 = time_amber;
                setTimer(TIMER_TRAFFIC, (uint32_t)time_amber * 1000);
            }
            break;

        case AUTO_RED1_AMBER2:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_AMBER);

            if (isTimerExpired(TIMER_TRAFFIC))
            {
                auto_state = AUTO_GREEN1_RED2;
                traffic_set(1, LIGHT_GREEN);
                traffic_set(2, LIGHT_RED);
                countdown_road1 = time_green;
                countdown_road2 = time_red;
                setTimer(TIMER_TRAFFIC, (uint32_t)time_green * 1000);
            }
            break;

        case AUTO_GREEN1_RED2:
            traffic_set(1, LIGHT_GREEN);
            traffic_set(2, LIGHT_RED);

            if (isTimerExpired(TIMER_TRAFFIC))
            {
                auto_state = AUTO_AMBER1_RED2;
                traffic_set(1, LIGHT_AMBER);
                traffic_set(2, LIGHT_RED);
                countdown_road1 = time_amber;
                setTimer(TIMER_TRAFFIC, (uint32_t)time_amber * 1000);
            }
            break;

        case AUTO_AMBER1_RED2:
            traffic_set(1, LIGHT_AMBER);
            traffic_set(2, LIGHT_RED);

            if (isTimerExpired(TIMER_TRAFFIC))
            {
                auto_state = AUTO_RED1_GREEN2;
                traffic_set(1, LIGHT_RED);
                traffic_set(2, LIGHT_GREEN);
                countdown_road1 = time_red;
                countdown_road2 = time_green;
                setTimer(TIMER_TRAFFIC, (uint32_t)time_green * 1000);
            }
            break;

        default:
            auto_state = AUTO_INIT;
            break;
    }

    if (button_is_pressed(BTN_INDEX_1))
    {
        system_mode = MODE_MANUAL;
        manual_state = MAN_INIT;
    }
}
