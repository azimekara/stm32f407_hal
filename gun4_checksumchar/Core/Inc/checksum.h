/*
 * checksum.h
 *
 *  Created on: Jun 24, 2022
 *      Author: Azime
 */

#ifndef INC_CHECKSUM_H_
#define INC_CHECKSUM_H_

extern char rbuffer[6];
extern char tbuffer[6];

extern uint8_t toplam;
extern UART_HandleTypeDef huart2;

void checksum(void);



#endif /* INC_CHECKSUM_H_ */
