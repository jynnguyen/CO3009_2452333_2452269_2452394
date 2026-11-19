/*
 * global.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>

typedef enum
{
    MODE_AUTO = 0,
    MODE_MANUAL,
    MODE_TUNING
} SystemMode;

typedef enum
{
    LIGHT_OFF = 0,
    LIGHT_GREEN,
    LIGHT_AMBER,
    LIGHT_RED
} LightColor;

typedef enum
{
    AUTO_INIT = 0,
    AUTO_RED1_GREEN2,
    AUTO_RED1_AMBER2,
    AUTO_GREEN1_RED2,
    AUTO_AMBER1_RED2
} AutoState;

typedef enum
{
    MAN_INIT = 0,
    MAN_RED1_GREEN2,
    MAN_RED1_AMBER2,
    MAN_GREEN1_RED2,
    MAN_AMBER1_RED2
} ManualState;

typedef enum
{
    TUNING_INIT = 0,
    TUNING_RED,
    TUNING_AMBER,
    TUNING_GREEN
} TuningMode;

extern SystemMode system_mode;
extern AutoState auto_state;
extern ManualState manual_state;
extern TuningMode tuning_mode;

extern LightColor road1_color;
extern LightColor road2_color;

extern uint8_t time_red;
extern uint8_t time_amber;
extern uint8_t time_green;

extern uint8_t temp_duration;

extern uint8_t countdown_road1;
extern uint8_t countdown_road2;

extern float dht20_temperature;
extern float dht20_humidity;
extern uint8_t dht20_read_success;

#endif /* INC_GLOBAL_H_ */
