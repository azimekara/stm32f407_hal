/*
 * mpu9250src.c
 *
 *  Created on: 4 Tem 2022
 *      Author: Azime
 */

#include "mpu9250.h"
#include "main.h"
#include "mpu9250src.h"
#include <stdio.h>
#include <stdlib.h>

extern I2C_HandleTypeDef hi2c3;
extern UART_HandleTypeDef huart2;
extern uint8_t pDataa[6];
extern uint8_t pDatag[6];
extern uint8_t pDatam[6];

int deger;
uint8_t deger1 = 0;
uint8_t deger2 = 2;
uint8_t deger3 = 5;
uint8_t deger4 = 15;
uint8_t deger5 = 22;

double accl_x, accl_y, accl_z;
double* accl_x_buff; double* accl_y_buff; double* accl_z_buff;
double gyro_x, gyro_y, gyro_z;
double* gyro_x_buff; double* gyro_y_buff; double* gyro_z_buff;
double magn_x, magn_y, magn_z;
double* magn_x_buff; double* magn_y_buff; double* magn_z_buff;
double magn_asax, magn_asay, magn_asaz;

double accl_scale, gyro_scale, magn_scale;

double tic, toc;

int mpu9250inst, ak8963inst;

char init_seq = 0;

void setupr(void)
{
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x6B, 1, &deger1, 1, 100);
	// Accel Range +-2g
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x1C, 1, &deger1, 1, 100);
	accl_scale = 16384.0;
	// Filter 420 Hz
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x1D, 1, &deger4, 1, 100);
	 // Gyro Range +-250 degrees/s
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x1B, 1, &deger1, 1, 100);
	gyro_scale = 131.0;
	// DLPF Bandwidth = 10
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x1A, 1, &deger3, 1, 100);
	// Enable Magnetometer (address 0x0c)
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x37, 1, &deger2, 1, 100);
	// Set power-down mode before the transition to another mode.
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x0A, 1, &deger1, 1, 100);
	// Set Continuous measurement mode 0x12 - 8Hz & 16-bit; 0x16 - 100 Hz & 16-bit
	HAL_I2C_Mem_Write(&hi2c3, 0xd0, 0x0A, 1, &deger5, 1, 100);
	magn_scale = 6826.7;

}

void readr(void)
{
	HAL_I2C_Mem_Read(&hi2c3, 0xd1, 0x3B, 1, pDataa, 6, 100);

	accl_x =(double) ((pDataa[0] << 8) | pDataa[1])/accl_scale;
	accl_y =(double) ((pDataa[2] << 8) | pDataa[3])/accl_scale;
	accl_z =(double) ((pDataa[4] << 8) | pDataa[5])/accl_scale;

	//memset(pDataa,'\0',sizeof(pDataa));

	HAL_I2C_Mem_Read(&hi2c3, 0xd1, 0x43, 1, pDatag, 6, 100);

	gyro_x =(double) ((pDatag[0] << 8) | pDatag[1])/gyro_scale;
	gyro_y =(double) ((pDatag[2] << 8) | pDatag[3])/gyro_scale;
	gyro_z =(double) ((pDatag[4] << 8) | pDatag[5])/gyro_scale;

//	memset(pDatam,'\0',sizeof(pDatam));

	HAL_I2C_Mem_Read(&hi2c3, 0xd1, 0x03, 1, pDatam, 6, 100);

	magn_x =(double) ((pDatam[0] << 8) | pDatam[1])/magn_scale;
	magn_y =(double) ((pDatam[2] << 8) | pDatam[3])/magn_scale;
	magn_z =(double) ((pDatam[4] << 8) | pDatam[5])/magn_scale;


//	memset(pDatam,'\0',sizeof(pDatam));
}

void uart(void)
{
	uint8_t uartb[9] = {accl_x,accl_y,accl_z,gyro_x,gyro_y,gyro_z,magn_x,magn_y,magn_z};
	HAL_UART_Transmit(&huart2, uartb, 9, 100);
	HAL_Delay(1000);
}
