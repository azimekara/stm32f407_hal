/*
 * button.c
 *
 *  Created on: Jun 27, 2022
 *      Author: Azime
 */

// buton ile tbuffer (tbufferdaki değerlerin hesaplanan checksumu son indexe eklenerek) gönderildi.

#include "main.h"
#include "button.h"

int8_t checksumd1=0;
extern uint8_t i;
uint8_t j=0;
uint8_t deger1 = 0;
uint8_t durum1 = 0;
uint8_t toplam1 = 0;

extern char rbuffer[6];
extern char tbuffer[6];
extern UART_HandleTypeDef huart2;

void status2(int size,char a[size])
{

	for(i=0;i<5;i++)
	{
		deger1 = a[i];
		toplam1 = toplam1 + deger1;
	}

	checksumd1 = toplam1 % 256;
	toplam1=0;
}

void button(void)
{

	status2(6,tbuffer);
	tbuffer[5]=checksumd1;

	HAL_UART_Transmit(&huart2,(uint8_t*)tbuffer,6,100);
}
