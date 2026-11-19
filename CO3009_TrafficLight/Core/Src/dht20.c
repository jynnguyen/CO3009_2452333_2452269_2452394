/*
 * dht20.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */
#include "dht20.h"
extern I2C_HandleTypeDef hi2c1;

typedef enum
{
    DHT20_STATE_TRIGGER = 0,
    DHT20_STATE_WAIT_AND_READ
} DHT20_State;
static DHT20_State dht_state = DHT20_STATE_TRIGGER;
static uint16_t dht_wait_counter = 0;
uint8_t dht20_init(void)
{
    uint8_t status = 0;
    HAL_Delay(100);
    if (HAL_I2C_Master_Receive(&hi2c1, DHT20_I2C_ADDR, &status, 1, 100) != HAL_OK)
    {
        return 0;
    }
    if ((status & 0x08) == 0)
    {
        uint8_t cmd_init[3];
        cmd_init[0] = 0x1B; cmd_init[1] = 0x00; cmd_init[2] = 0x00;
        HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, cmd_init, 3, 100);
        HAL_Delay(10);
        cmd_init[0] = 0x1C; cmd_init[1] = 0x00; cmd_init[2] = 0x00;
        HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, cmd_init, 3, 100);
        HAL_Delay(10);
        cmd_init[0] = 0x1E; cmd_init[1] = 0x00; cmd_init[2] = 0x00;
        HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, cmd_init, 3, 100);
        HAL_Delay(10);
    }
    return 1;
}
void dht20_task(void)
{
    switch (dht_state)
    {
        case DHT20_STATE_TRIGGER:
        {
            uint8_t trigger_cmd[3] = {0xAC, 0x33, 0x00};
            if (HAL_I2C_Master_Transmit(&hi2c1, DHT20_I2C_ADDR, trigger_cmd, 3, 50) == HAL_OK)
            {
                dht_wait_counter = 0;
                dht_state = DHT20_STATE_WAIT_AND_READ;
            }
            break;
        }
        case DHT20_STATE_WAIT_AND_READ:
        {
            uint8_t buffer[7] = {0};
            if (HAL_I2C_Master_Receive(&hi2c1, DHT20_I2C_ADDR, buffer, 7, 50) == HAL_OK)
            {
                if ((buffer[0] & 0x80) == 0)
                {
                    uint32_t raw_hum = ((uint32_t)buffer[1] << 12) |
                                       ((uint32_t)buffer[2] << 4)  |
                                       ((uint32_t)buffer[3] >> 4);
                    uint32_t raw_temp = (((uint32_t)buffer[3] & 0x0F) << 16) |
                                        ((uint32_t)buffer[4] << 8)            |
                                        ((uint32_t)buffer[5]);
                    dht20_humidity    = ((float)raw_hum / 1048576.0f) * 100.0f;
                    dht20_temperature = ((float)raw_temp / 1048576.0f) * 200.0f - 50.0f;
                    dht20_read_success = 1;
                }
            }
            dht_state = DHT20_STATE_TRIGGER;
            break;
        }
    }
}

