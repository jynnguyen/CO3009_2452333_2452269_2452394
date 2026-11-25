/*
 * lcd.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include "global.h"

#define LCD_I2C_ADDR    (0x21 << 1)

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print_string(char *str);
void lcd_display_task(void);

#endif /* INC_LCD_H_ */
