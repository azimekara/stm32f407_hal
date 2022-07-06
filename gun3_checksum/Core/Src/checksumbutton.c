/*
 * button.c
 *
 *  Created on: Jun 22, 2022
 *      Author: Azime
 */

#include "main.h"
#include "checksumbutton.h"
#include "stdio.h"

extern uint8_t tbuffer[10];
extern uint8_t toplam;
extern uint8_t checksum;
extern uint8_t i;

extern UART_HandleTypeDef huart2;


void button (void)
{
	for(i=0;i<9;i++)
	{
		toplam += tbuffer[i];
	}

	checksum = toplam % 256;

	tbuffer[9] = checksum;

	HAL_Delay(150);
	HAL_UART_Transmit(&huart2,(uint8_t*)tbuffer,10,100);
}

