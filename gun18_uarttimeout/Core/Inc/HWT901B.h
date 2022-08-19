/*
 * HWT901B.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Azime
 */

/*****************************************************************
 *
 * HWT901B REGİSTER MAP
 *
 *********************
 * Time Output Register
 *
 * 0x55 - 0x50 - YY - MM - DD - hh - mm - ss - msL - msH - SUM
 *
 * YY: Year
 * MM: Month
 * DD: Day
 * hh: hour
 * mm: minute
 * ss: second
 * ms: milisecond
 *
 * milisecond calculate formula:
 * ms = ((msH<<8|msL)
 *
 * Sum:0x55+0x50+YY+MM+DD+hh+ss+msL+msH
 *
 * ********************
 * Acceleration Output Register
 *
 * 0x55 - 0x51 - AxL - AxH - AyL - AyH - AzL - AzH - TL - TH - SUM
 *
 * Calculate formula:
 *
 * ax = ((AxH<<8)|AxL)/32768*16g(g is Gravity acceleration, 9.8m/s^2)
 * ay = ((AyH<<8)|AyL)/32768*16g(g is Gravity acceleration, 9.8m/s^2)
 * az = ((AzH<<8)|AzL)/32768*16g(g is Gravity acceleration, 9.8m/s^2)
 *
 *
 */

#ifndef INC_HWT901B_H_
#define INC_HWT901B_H_

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

void configbuf(void);
void send(void);

#endif /* INC_HWT901B_H_ */
