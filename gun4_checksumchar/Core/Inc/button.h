/*
 * button.h
 *
 *  Created on: Jun 27, 2022
 *      Author: Azime
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

extern char rbuffer[6];
extern char tbuffer[6];
extern UART_HandleTypeDef huart2;

extern uint8_t deger1;
extern uint8_t durum1;
extern uint8_t toplam1;

void button(void);

#endif /* INC_BUTTON_H_ */
