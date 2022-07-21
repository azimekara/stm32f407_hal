/*
 * readadc.c
 *
 *  Created on: Jul 18, 2022
 *      Author: Azime
*/

#include "main.h"
#include "readadc.h"

extern ADC_HandleTypeDef hadc1;

uint16_t adc_value;
float adc_vol;

void Read_ADC(void)
{
	HAL_ADC_Start(&hadc1);

	if(HAL_ADC_PollForConversion(&hadc1, 1000) == HAL_OK)
	{
		adc_value = HAL_ADC_GetValue(&hadc1);
		adc_vol = 3.3*adc_value/4095;
	}

	HAL_ADC_Stop(&hadc1);
}


