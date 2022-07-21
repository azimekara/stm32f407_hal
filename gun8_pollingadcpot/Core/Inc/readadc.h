/*
 * readadc.h
 *
 *  Created on: Jul 18, 2022
 *      Author: Azime
 */

#ifndef INC_READADC_H_
#define INC_READADC_H_

extern ADC_HandleTypeDef hadc1;

extern uint16_t adc_value;
extern float adc_vol;

void Read_ADC(void);

#endif /* INC_READADC_H_ */
