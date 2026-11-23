/*
 * global.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "global.h"

SystemMode system_mode = MODE_AUTO;
AutoState auto_state = AUTO_INIT;
ManualState manual_state = MAN_INIT;
TuningSelect tuning_select = TUNE_RED;
SaveNotification save_notification = NOTIF_NONE;

LightState road1_color = LIGHT_RED;
LightState road2_color = LIGHT_GREEN;

uint8_t time_red   = 5;
uint8_t time_amber = 2;
uint8_t time_green = 3;

uint8_t temp_red   = 5;
uint8_t temp_amber = 2;
uint8_t temp_green = 3;

uint8_t countdown_road1 = 5;
uint8_t countdown_road2 = 3;

float dht20_temperature = 0.0f;
float dht20_humidity    = 0.0f;
uint8_t dht20_read_success = 0;
