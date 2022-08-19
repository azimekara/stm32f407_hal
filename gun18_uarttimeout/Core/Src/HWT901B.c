/*
 * HWT901B.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Azime
 */

#include "main.h"
#include "HWT901B.h"
#include "stdio.h"
#include "string.h"

extern UART_HandleTypeDef huart3;

extern uint8_t uart_one_byte;
extern uint8_t uart_lenght;
extern uint8_t rxbuf[120];
extern uint8_t copyrxbuf[120];
extern uint8_t tbuffer[100];
extern uint8_t flagconfigbuf,flagsend;
extern uint8_t txbuf[11];
extern uint8_t timeout;
extern uint16_t count;
extern uint8_t i,j,x;;
extern uint8_t a;
extern double b,c,d,e;

void configbuf(void)
{

	memset(copyrxbuf,'\0',sizeof(copyrxbuf));
	memcpy(copyrxbuf,rxbuf,sizeof(rxbuf));
	memset(rxbuf,'\0',sizeof(rxbuf));
	flagconfigbuf=0;

}

void send(void)
{
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

	if (copyrxbuf[i] == 0x55)
	{

		for(j=0;j<11;j++)
		{
			txbuf[j] = copyrxbuf[i];
			i++;

		}

		if(txbuf[1]==0x50)
		{
			HAL_UART_Transmit(&huart3,(uint8_t*)tbuffer,sprintf(tbuffer,"Year:%d Month:%d Day:%d Hour:%d Minute:%d Second:%d Milisecond:%d ",txbuf[2],txbuf[3],txbuf[4],txbuf[5],txbuf[6],txbuf[7],(txbuf[9]<<8 | txbuf[8])),1000);

		}

		if(txbuf[1]==0x51)
		{
			a=0;b=0;
			a = txbuf[3]<<8 | txbuf[2];
			b = (double)a / 32768;
			c = b*156.8;

			a=0;b=0;
			a = txbuf[5]<<8 | txbuf[4];
			b = (double)a / 32768;
			d = b*156.8;

			a=0;b=0;
			a = txbuf[7]<<8 | txbuf[6];
			b = (double)a / 32768;
			e = b*156.8;

			HAL_UART_Transmit(&huart3,(uint8_t*)tbuffer,sprintf(tbuffer,"Ax:%f Ay:%f Az:%f Temperature:%d\n",c,d,e,((txbuf[9]<<8 | txbuf[8])/100)),1000);

		}

		if(txbuf[1]==0x52)
		{
			a=0;b=0;
			a = txbuf[3]<<8 | txbuf[2];
			b = (double)a / 32768;
			c = b*2000;

			a=0;b=0;
			a = txbuf[5]<<8 | txbuf[4];
			b = (double)a / 32768;
			d = b*2000;

			a=0;b=0;
			a = txbuf[7]<<8 | txbuf[6];
			b = (double)a / 32768;
			e = b*2000;

			HAL_UART_Transmit(&huart3,(uint8_t*)tbuffer,sprintf(tbuffer,"wx:%f wy:%f wz:%f Temperature:%d\n",c,d,e,((txbuf[9]<<8 | txbuf[8])/100)),1000);

		}

		if(txbuf[1]==0x53)
		{
			a=0;b=0;
			a = txbuf[3]<<8 | txbuf[2];
			b = (double)a / 32768;
			c = b*180;

			a=0;b=0;
			a = txbuf[5]<<8 | txbuf[4];
			b = (double)a / 32768;
			d = b*180;

			a=0;b=0;
			a = txbuf[7]<<8 | txbuf[6];
			b = (double)a / 32768;
			e = b*180;

			HAL_UART_Transmit(&huart3,(uint8_t*)tbuffer,sprintf(tbuffer,"Roll:%f Pitch:%f Yaw:%f Version:%d\n",c,d,e,((txbuf[9]<<8) | txbuf[8])),1000);

		}

		if(txbuf[1]==0x54)
		{
			c=0;d=0;e=0;
			c = txbuf[3]<<8 | txbuf[2];
			d = txbuf[5]<<8 | txbuf[4];
			e = txbuf[7]<<8 | txbuf[6];


			HAL_UART_Transmit(&huart3,(uint8_t*)tbuffer,sprintf(tbuffer,"Hx:%f Hy:%f Hz:%f Temperature:%d\n",c,d,e,((txbuf[9]<<8) | txbuf[8]/100)),1000);

		}

	/*	if(txbuf[1]==0x56)
		{
			c=0;d=0;e=0;
			c = txbuf[3]<<8 | txbuf[2];
			d = txbuf[5]<<8 | txbuf[4];
			e = txbuf[7]<<8 | txbuf[6];


			HAL_UART_Transmit(&huart3,(uint8_t*)tbuffer,sprintf(tbuffer,"Roll:%f Pitch:%f Yaw:%f Version:%d\n",c,d,e,((txbuf[9]<<8) | txbuf[8]/100)),1000);

		}*/

		j=0;
	}

	if (i>=110)
	{
		i=0;
	}

	flagsend = 0;

}

