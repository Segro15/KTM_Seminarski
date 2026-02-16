/*
 * HMC5883L.h
 *
 *  Created on: Jan 3, 2026
 *      Author: Matija
 */

#ifndef INC_QMC5883L_H_
#define INC_QMC5883L_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "math.h"
#include "compass_frames.h"
#include "stdbool.h"
#include <stdio.h>
#include <SH1106.h>

#define data_output_X_LSB_reg 0x00
#define data_output_X_MSB_reg 0x01
#define data_output_Y_LSB_reg 0x02
#define data_output_Y_MSB_reg 0x03
#define data_output_Z_LSB_reg 0x04
#define data_output_Z_MSB_reg 0x05

#define QMC5883L_status		        0x06
#define QMC5883L_config_1		0x09
#define QMC5883L_config_2		0x0A
#define QMC5883L_config_3		0x0B

#define QMC5883L_declination 0.086684 // Zagreb

void I2C_Scan();
void I2C_ResetBus();
HAL_StatusTypeDef QMC5883L_Initialize(void);
HAL_StatusTypeDef QMC5883L_Read_Data(int16_t *raw_x,int16_t *raw_y);
uint8_t QMC5883L_Status(void);
uint8_t QMC5883L_Continous_Check(void);
float QMC5883L_Heading(int16_t raw_x, int16_t raw_y);
#endif /* INC_QMC5883L_H_ */
