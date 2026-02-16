/*
 * ssd1306.c
 *
 *  Created on: Jan 2, 2026
 *      Author: Matija
 */
#include "ssd1306.h"
#include "main.h"
#include "compass_frames.h"// zbog hi2c1

#define OLED_ADDR (0x3C << 1)
extern I2C_HandleTypeDef hi2c1;


static const uint8_t font6x8[11][6] = {
    {0x3E,0x51,0x49,0x45,0x3E,0x00}, // 0
    {0x00,0x42,0x7F,0x40,0x00,0x00}, // 1
    {0x42,0x61,0x51,0x49,0x46,0x00}, // 2
    {0x21,0x41,0x45,0x4B,0x31,0x00}, // 3
    {0x18,0x14,0x12,0x7F,0x10,0x00}, // 4
    {0x27,0x45,0x45,0x45,0x39,0x00}, // 5
    {0x3C,0x4A,0x49,0x49,0x30,0x00}, // 6
    {0x01,0x71,0x09,0x05,0x03,0x00}, // 7
    {0x36,0x49,0x49,0x49,0x36,0x00}, // 8
    {0x06,0x49,0x49,0x29,0x1E,0x00}, // 9
    {0x0C,0x12,0x12,0x0C,0x00,0x00}  // °
};


void OLED_Command(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, 2, HAL_MAX_DELAY);
}

void OLED_Data(uint8_t dataByte) {
    uint8_t data[2] = {0x40, dataByte};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, 2, HAL_MAX_DELAY);
}

void OLED_Init() {
    HAL_Delay(100);

    OLED_Command(0xAE); // Display OFF
    OLED_Command(0xD5); // Clock divide
    OLED_Command(0x80);
    OLED_Command(0xA8); // Multiplex
    OLED_Command(0x3F);
    OLED_Command(0xD3); // Display offset
    OLED_Command(0x00);
    OLED_Command(0x40); // Start line = 0
    OLED_Command(0xAD); // DC-DC control
    OLED_Command(0x8B); // Enable charge pump
    OLED_Command(0xA1); // Segment remap (SH1106)
    OLED_Command(0xC8); // COM scan direction (SH1106)
    OLED_Command(0xDA); // COM pins
    OLED_Command(0x12);
    OLED_Command(0x81); // Contrast
    OLED_Command(0x7F);
    OLED_Command(0xD9); // Pre-charge
    OLED_Command(0x22);
    OLED_Command(0xDB); // VCOM detect
    OLED_Command(0x35);
    OLED_Command(0xA4); // Display follows RAM
    OLED_Command(0xA6); // Normal display
    OLED_Command(0xAF); // Display ON
}

void OLED_DrawChar(uint8_t page, uint8_t col, uint8_t digit)
{
    const uint8_t *znak = font6x8[digit];

    OLED_SetPosition(page, col);

    for (int i = 0; i < 6; i++){
    	OLED_Data(znak[i]);
    }
}

void OLED_DrawAngle(int angle)
{
    angle = (angle % 360 + 360) % 360;


    int stot = angle / 100;
    int des = (angle / 10) % 10;
    int jed = angle % 10;
    OLED_SetPosition(7, 0);
    for (int i = 0; i < 30; i++)
        OLED_Data(0x00);

    uint8_t col = 0;

    if (stot > 0) {
        OLED_DrawChar(7, col, stot);
        col += 7;
    }
    if (stot > 0 || des >0) {
    	OLED_DrawChar(7, col, des);
    	col = col + 7;
    }

    OLED_DrawChar(7, col, jed);
    col += 7;
    OLED_DrawChar(7, col, 10);
}


void OLED_Fill(uint8_t pattern) {
    for (uint8_t page = 0; page < 8; page++) {
        OLED_Command(0xB0 + page);
        OLED_Command(0x00);
        OLED_Command(0x10);

        for (uint8_t col = 0; col < 132; col++) {
            OLED_Data(pattern);
        }
    }
}

void OLED_SetPosition(uint8_t page, uint8_t column)
{
    OLED_Command(0xB0 + page);                     // Page address
    OLED_Command(0x02 + (column & 0x0F));          // Lower column (SH1106 offset!)
    OLED_Command(0x10 + ((column >> 4) & 0x0F));   // Higher column
}

void OLED_DrawBitmap132(const uint8_t* bitmap)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        OLED_SetPosition(page, 0);

        const uint8_t* ptr = bitmap + (page * 132);

        for (uint16_t col = 0; col < 132; col++)
        {
            OLED_Data(ptr[col]);
        }
    }
}
void Compass_Draw(int angle)
{
    angle = angle % 360;
    int index = angle / 30;

    OLED_DrawBitmap132(compass_frames[index]);
}




