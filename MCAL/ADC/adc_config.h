/*
 * adc_config.h
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_


#include "adc_interface.h"

#define ADC_AREF_SOURCE       0
#define ADC_AVCC_SOURCE       1
#define ADC_INTERNAL_SOURCE  3


#define ADC_VOLTAGE_REF    ADC_AREF_SOURCE


#define ADC_PRESCALER_2       1
#define ADC_PRESCALER_4       2
#define ADC_PRESCALER_8       3
#define ADC_PRESCALER_16      4
#define ADC_PRESCALER_32      5
#define ADC_PRESCALER_64      6
#define ADC_PRESCALER_128     7


#define ADC_PRESCALER   ADC_PRESCALER_128

#define ADC_RIGHT_ADJUST_READ   0
#define ADC_LEFT_ADJUST_READ    1

#define ADC_READ_ADJEST  ADC_RIGHT_ADJUST_READ


#endif /* MCAL_ADC_ADC_CONFIG_H_ */
