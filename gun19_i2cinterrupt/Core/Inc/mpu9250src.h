/*
 * mpu9250src.h
 *
 *  Created on: Jul 4, 2022
 *      Author: Azime
 */

#ifndef INC_MPU9250SRC_H_
#define INC_MPU9250SRC_H_

extern I2C_HandleTypeDef hi2c3;
//extern UART_HandleTypeDef huart2;
extern uint8_t pData[6];

void setupr(void);
//void readr(void);
void uart(void);

void accl(void);
void gyro(void);
void magn(void);

#endif /* INC_MPU9250SRC_H_ */
