/*
 * ssd1306.h
 *
 *  Created on: Jan 2, 2026
 *      Author: Matija
 */

#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_

#include  "stm32f4xx_hal.h"

void OLED_Command(uint8_t cmd);
void OLED_Data(uint8_t dataByte);
void OLED_Init(void);
void OLED_DrawChar(uint8_t page, uint8_t col, uint8_t digit);
void OLED_DrawAngle(int angle);
void OLED_Fill(uint8_t pattern);
void OLED_SetPosition(uint8_t page, uint8_t column);
void OLED_DrawBitmap132(const uint8_t* bitmap);
void Compass_Draw(int angle);

#endif /* INC_SSD1306_H_ */
