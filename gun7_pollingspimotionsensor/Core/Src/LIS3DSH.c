/*
 * LIS3DSH.c
 *
 *  Created on: 7 Tem 2022
 *      Author: Azime
 */

#include "main.h"
#include "LIS3DSH.h"

#include "spi.h"

uint8_t transmitBuffer[16];
uint8_t transmitBufLen;

uint8_t LIS3DSH_HAL_ReadReg8(uint8_t reg)
{
	transmitBuffer[0] = 0x80 | reg;
	transmitBufLen = 1;

	HAL_GPIO_WritePin(ACC_CS_GPIO_Port,ACC_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1,transmitBuffer,transmitBufLen,5000);
	while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_TX) {}

	HAL_SPI_Receive(&hspi1,transmitBuffer,transmitBufLen,5000);
	while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_RX){}

	HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);

	return(transmitBuffer[0]);
}

uint16_t LIS3DSH_HAL_ReadReg16(uint8_t reg)
{
	 transmitBuffer[0] = 0x80 | reg;
	 static uint8_t r1,r2;

	 HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET);

	 HAL_SPI_Transmit(&hspi1,transmitBuffer,1,5000);
	 while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_TX) {}

	 HAL_SPI_Receive(&hspi1,&r1,1,5000);
	 while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_RX){}

	 HAL_SPI_Receive(&hspi1,&r2,1,5000);
	 while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_RX){}

	 HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);

	 return(r1|(r2<<8));

}

uint8_t LIS3DSH_HAL_WriteReg8(uint8_t reg,uint8_t val)
{
	transmitBuffer[0] = ( ~0x80 & reg );
    transmitBuffer[1] = ( val );
	transmitBufLen = 1;

	HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1,transmitBuffer,transmitBufLen,5000);
	while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_TX) {}
	transmitBuffer[0] = transmitBuffer[1];
	HAL_SPI_Transmit(&hspi1,transmitBuffer,transmitBufLen,5000);
	while(HAL_SPI_GetState(&hspi1)== HAL_SPI_STATE_BUSY_TX) {}

	HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);

	return(transmitBuffer[0]);
}

uint8_t LIS3DSH_HAL_ReadTemp(void)
{
    return(LIS3DSH_HAL_ReadReg8(LIS3DSH_REG_OUTT));
}



