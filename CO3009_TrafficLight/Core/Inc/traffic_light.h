/*
 * traffic_light.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include "global.h"


void traffic_init();
void traffic_set(uint8_t roadNum, LightState color);
void traffic_toggle(uint8_t roadNum, LightState color);
void traffic_off_all(void);

#endif /* INC_TRAFFIC_LIGHT_H_ */
