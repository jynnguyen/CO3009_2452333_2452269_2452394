/*
 * lcd.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "lcd.h"
#include <stdio.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;
static uint8_t is_lcd_connected = 0;

static void lcd_send_cmd(char cmd)
{
    if (!is_lcd_connected) return;
    char data_u = (cmd & 0xf0);
    char data_l = ((cmd << 4) & 0xf0);
    uint8_t data_t[4] = {
        (uint8_t)(data_u | 0x0C),
        (uint8_t)(data_u | 0x08),
        (uint8_t)(data_l | 0x0C),
        (uint8_t)(data_l | 0x08)
    };
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, data_t, 4, 20);
}

static void lcd_send_data(char data)
{
    if (!is_lcd_connected) return;
    char data_u = (data & 0xf0);
    char data_l = ((data << 4) & 0xf0);
    uint8_t data_t[4] = {
        (uint8_t)(data_u | 0x0D),
        (uint8_t)(data_u | 0x09),
        (uint8_t)(data_l | 0x0D),
        (uint8_t)(data_l | 0x09)
    };
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, data_t, 4, 20);
}

void lcd_init(void)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, LCD_I2C_ADDR, 2, 20) != HAL_OK)
    {
        is_lcd_connected = 0;
        return;
    }
    is_lcd_connected = 1;

    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);
    HAL_Delay(10);

    lcd_send_cmd(0x28);
    HAL_Delay(1);
    lcd_send_cmd(0x08);
    HAL_Delay(1);
    lcd_send_cmd(0x01);
    HAL_Delay(2);
    lcd_send_cmd(0x06);
    HAL_Delay(1);
    lcd_send_cmd(0x0C);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(address);
}

void lcd_print_string(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}

static const char* color_to_str_r1(LightState c)
{
    switch (c)
    {
        case LIGHT_RED:   return "R1";
        case LIGHT_AMBER: return "Y1";
        case LIGHT_GREEN: return "G1";
        default:          return "--";
    }
}

static const char* color_to_str_r2(LightState c)
{
    switch (c)
    {
        case LIGHT_RED:   return "R2";
        case LIGHT_AMBER: return "Y2";
        case LIGHT_GREEN: return "G2";
        default:          return "--";
    }
}

void lcd_display_task(void)
{
    if (!is_lcd_connected) return;

    char line1[20];
    char line2[20];

    switch (system_mode)
    {
        case MODE_AUTO:
            snprintf(line1, sizeof(line1), "AUTO %s:%02d %s:%02d",
                     color_to_str_r1(road1_color), countdown_road1,
                     color_to_str_r2(road2_color), countdown_road2);
            break;

        case MODE_MANUAL:
            snprintf(line1, sizeof(line1), "MAN     %s    %s  ",
                     color_to_str_r1(road1_color), color_to_str_r2(road2_color));
            break;

        case MODE_TUNING:
			if (save_notification == NOTIF_SAVED)
			{
				snprintf(line1, sizeof(line1), "TUN    SAVED!   ");
			}
			else if (save_notification == NOTIF_SYNCED)
			{
				snprintf(line1, sizeof(line1), "TUN Saved&Synced");
			}
			else
			{
				if (tuning_select == TUNE_RED)
					snprintf(line1, sizeof(line1), "TUN RED_t: %02ds  ", temp_red);
				else if (tuning_select == TUNE_AMBER)
					snprintf(line1, sizeof(line1), "TUN YEL_t: %02ds  ", temp_amber);
				else
					snprintf(line1, sizeof(line1), "TUN GRN_t: %02ds  ", temp_green);
			}
			break;
    }

    if (dht20_read_success)
    {
        int t_int = (int)dht20_temperature;
        int t_dec = (int)((dht20_temperature - t_int) * 10);
        if (t_dec < 0) t_dec = -t_dec;
        int h_int = (int)dht20_humidity;

        snprintf(line2, sizeof(line2), "T:%d.%dC  H:%d%%   ", t_int, t_dec, h_int);
    }
    else
    {
        snprintf(line2, sizeof(line2), "T:--.-C  H:--%%   ");
    }

    lcd_set_cursor(0, 0);
    lcd_print_string(line1);

    lcd_set_cursor(1, 0);
    lcd_print_string(line2);
}
