/*
 * led.c
 *
 *  Created on: Jun 22, 2022
 *      Author: Azime
 */

// tbufferdaki değerlerin checksumını hesaplayıp dizinin sonuna ekleyecek gönderiyoruz.Docklighttan checksum değerini geri gönderince
//ledi togglelıyoruz.

#include "main.h"
#include "checksumled.h"

extern uint8_t rbuffer[1];
extern UART_HandleTypeDef huart2;

void led (void)
{

	if(rbuffer[0] == 45)
	{

			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_Delay(1000);

	}

}

