/*
 * checksum.c
 *
 *  Created on: Jun 24, 2022
 *      Author: Azime
 */

//dockligten gönderilen 6 karakterli(son karakteri checksum olan) char dizisi alınarak ilk  5 karakterinin checksumu hesaplandı.Docklightın hesapladığı değer ile
//karşılaştırıldı.(son indexe bakarak)Eğer değerler eşitse onay mesajı göndeildi.(bana mi dedin)

#include "main.h"
#include "checksum.h"


extern char rbuffer[6];
extern char tbuffer[6];
extern UART_HandleTypeDef huart2;

extern uint8_t toplam;
extern uint8_t i;
uint8_t checksumd =0;
uint8_t deger = 0;
uint8_t durum = 0;


int status(int size,char a[size])
{

	for(i=0;i<5;i++)
	{
		deger = a[i];
		toplam = toplam + deger;
	}

	checksumd = toplam % 256;

	if (rbuffer[5] == checksumd)
	{
		durum = 1;
	}

	else
	{
		durum = 0;
	}

	return durum;


}

void checksum(void)
{
	if (HAL_UART_Receive(&huart2, (uint8_t*) rbuffer, 6, 1000)==HAL_OK)
	{

		if (status(6,rbuffer) ==  1 )
			{

				HAL_UART_Transmit(&huart2,(uint8_t*)tbuffer,sprintf(tbuffer,"Bana mi dedin\n"),1000);
				toplam = 0;

			}
	}


}


