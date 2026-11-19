/*
 * dht20.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include "main.h"
#include "global.h"
#define DHT20_I2C_ADDR    (0x38 << 1)

uint8_t dht20_init(void);

void dht20_task(void);

#endif /* INC_DHT20_H_ */
