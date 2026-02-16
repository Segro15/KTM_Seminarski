/*
 * HMC5883L.c
 *
 *  Created on: Jan 3, 2026
 *      Author: Matija
 */
#include "HMC5883L.h"


#define QMC5883L_ADDR  (0x0D << 1)
extern I2C_HandleTypeDef hi2c2;

uint8_t config1 = 0x49; //0b11011101 Registar 1 za konfiguraciju
uint8_t config2 = 0x01;
uint8_t config3 = 0x01;

float x_min =  32767;
float x_max = -32768;
float y_min =  32767;
float y_max = -32768;



void I2C_Scan(I2C_HandleTypeDef *hi2c) {
    HAL_StatusTypeDef res;
    uint8_t i;
    printf("Scanning I2C bus...\r\n");

    for (i = 1; i < 127; i++) {
        res = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i << 1), 1, 50);
        if (res == HAL_OK) {
            printf("Device found at 0x%02X\r\n", i);
        }
    }
}


HAL_StatusTypeDef QMC5883L_Initialize(void){
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c2,QMC5883L_ADDR,0x0B,1,&config2,1,50); // Set/Reset Period
	if(ret != HAL_OK)
			return ret;
	ret = HAL_I2C_Mem_Write(&hi2c2,QMC5883L_ADDR,0x09,1,&config1,1,50); // OSR|ODR|
	if(ret != HAL_OK)
		return ret;

	return HAL_OK;
}
HAL_StatusTypeDef QMC5883L_Read_Data(int16_t *raw_x,int16_t *raw_y){
	HAL_StatusTypeDef ret;
	uint8_t raw[6];

	if(QMC5883L_Status() != HAL_OK){
		printf("Novi podaci nisu spremni \n ");
        return HAL_ERROR;
	}
	ret = HAL_I2C_Mem_Read(&hi2c2,QMC5883L_ADDR,data_output_X_LSB_reg,1,raw,6,10);
	if(ret != HAL_OK){
			return ret;
	}
	*raw_x=(int16_t)(raw[1]<<8|raw[0]);
	*raw_y=(int16_t)(raw[3]<<8|raw[2]);


	return HAL_OK;
		  }


HAL_StatusTypeDef QMC5883L_Status(void){

	uint8_t status=0;
	HAL_I2C_Mem_Read(&hi2c2, QMC5883L_ADDR, 0x06, 1, &status, 1, 50);
	if(status & 0x01)
	    return HAL_OK;
	else
		return(HAL_BUSY);
	return status;
}
uint8_t QMC5883L_Continous_Check(void){
	uint8_t status=0;
		HAL_I2C_Mem_Read(&hi2c2, QMC5883L_ADDR, 0x09, 1, &status, 1, 50);
		return status;
}

float QMC5883L_Heading(int16_t raw_x, int16_t raw_y){
	float x=(float)raw_x, y=(float)raw_y, heading;

	if(x < x_min)
			x_min = x;
		else if(x > x_max)
			x_max = x;
		if(y < y_min)
			y_min = y;
		else if(y > y_max)
			y_max = y;

		x -= (x_max+x_min)/2;
		y -= (y_max+y_min)/2;

		x = x/(x_max-x_min);
		y = y/(y_max-y_min);

		heading = atan2(y,x);
		heading += QMC5883L_declination;

			if(heading < 0)
				heading += 2*M_PI;
			else if(heading > 2*M_PI)
				heading -= 2*M_PI;

	return heading;
}






