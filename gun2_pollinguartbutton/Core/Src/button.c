/*
 * button.c
 *
 *  Created on: Jun 21, 2022
 *      Author: Azime
 */

#include "main.h"
#include "button.h"
#include "stdio.h"

char tbuffer[5];
extern UART_HandleTypeDef huart2;


void button (void)
{
	HAL_Delay(150);
	HAL_UART_Transmit(&huart2,(uint8_t*)tbuffer,sprintf(tbuffer,"Hello\n"),100);
}

