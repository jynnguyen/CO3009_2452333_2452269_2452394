/*
 * software_timer.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>
#define TIMER_TICK_MS   10
#define MAX_TIMERS      4

#define TIMER_TRAFFIC   0
#define TIMER_COUNTDOWN 1
#define TIMER_BLINK     2
#define TIMER_TIMEOUT   3
extern volatile uint8_t timer_flag[MAX_TIMERS];

void setTimer(uint8_t index, uint32_t duration_ms);

void timer_run(void);

uint8_t isTimerExpired(uint8_t index);

#endif /* INC_SOFTWARE_TIMER_H_ */
