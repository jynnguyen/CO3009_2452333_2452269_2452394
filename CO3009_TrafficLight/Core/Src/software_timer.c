/*
 * software_timer.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */
#include "software_timer.h"
static volatile int32_t timer_counter[MAX_TIMERS] = {0};
volatile uint8_t timer_flag[MAX_TIMERS] = {0};
void setTimer(uint8_t index, uint32_t duration_ms)
{
    if (index >= MAX_TIMERS) return;
    timer_counter[index] = duration_ms / TIMER_TICK_MS;
    timer_flag[index] = 0;
}
void timer_run(void)
{
    for (uint8_t i = 0; i < MAX_TIMERS; i++)
    {
        if (timer_counter[i] > 0)
        {
            timer_counter[i]--;
            if (timer_counter[i] <= 0)
            {
                timer_flag[i] = 1;
            }
        }
    }
}
uint8_t isTimerExpired(uint8_t index)
{
    if (index >= MAX_TIMERS) return 0;
    if (timer_flag[index] == 1)
    {
        timer_flag[index] = 0;
        return 1;
    }
    return 0;
}

