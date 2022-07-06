/*
 * pollinguart.c
 *
 *  Created on: Jun 21, 2022
 *      Author: Azime
 */

#include "main.h"
#include "stdio.h"
#include "pollinguart.h"

char buffer[100];
char rbuffer[50];
extern UART_HandleTypeDef huart2;

void uartt(void)
{
	 HAL_UART_Transmit(&huart2,(uint8_t*)buffer,sprintf(buffer,"Hello\n"),1000);
}

void uartr(void)
{
	HAL_UART_Receive(&huart2, (uint8_t*)rbuffer, 50, 1000);
	if (rbuffer[0] == 'a')
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(1000);

	}

	else
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(1000);
	}
}
