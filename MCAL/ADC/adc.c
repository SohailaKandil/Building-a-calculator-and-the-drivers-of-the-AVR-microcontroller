/*
 * adc.c
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */


#include "adc.h"

static void (*ADC_InterruptHandler)(void)= NULL;
void ADC_Init() {
		#if ADC_VOLTAGE_REF == ADC_AREF_SOURCE
			CLEAR_BIT(ADMUX, REFS0);
			CLEAR_BIT(ADMUX, REFS1);
		#elif ADC_VOLTAGE_REF == ADC_AVCC_SOURCE
			SET_BIT(ADMUX,REFS0);
			CLEAR_BIT(ADMUX,REFS1);
		#elif ADC_VOLTAGE_REF == 5_INTER_SOURCE
			SET_BIT(ADMUX,REFS0);
			SET_BIT(ADMUX,REFS1);
		#endif
		#if ADC_READ_ADJEST == ADC_RIGHT_ADJUST_READ
			CLEAR_BIT(ADMUX, ADLAR);
		#elif ADC_READ_ADJEST == ADC_LEFT_ADJUST_READ
			SET_BIT(ADMUX, ADLAR);
		#endif
		#if ADC_PRESCALER == ADC_PRESCALER_2
			CLEAR_BIT(SFIOR, ADTS0);
			CLEAR_BIT(SFIOR, ADTS1);
			CLEAR_BIT(SFIOR, ADTS2);
		#elif ADC_PRESCALER == ADC_PRESCALER_4
			CLEAR_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			CLEAR_BIT(SFIOR, ADTS2);
		#elif ADC_PRESCALER == ADC_PRESCALER_8
			SET_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			CLEAR_BIT(SFIOR, ADTS2);
		#elif ADC_PRESCALER == ADC_PRESCALER_16
			CLEAR_BIT(SFIOR, ADTS0);
			CLEAR_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
		#elif ADC_PRESCALER == ADC_PRESCALER_32
			SET_BIT(SFIOR, ADTS0);
			CLEAR_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
		#elif ADC_PRESCALER == ADC_PRESCALER_64
			CLEAR_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
		#elif ADC_PRESCALER == ADC_PRESCALER_128
			SET_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
		#endif

		CLEAR_BIT(ADCSRA, ADATE);
		SET_BIT(ADCSRA, ADEN);

}
uint16 ADC_Read(ADC_chanel ch) {
	uint16 ADC_Value=0;
	ADMUX &=0xE0;
	ADMUX |=ch;
	SET_BIT(ADCSRA, ADSC);
	while(0 == READ_BIT(ADCSRA, ADIF));
	SET_BIT(ADCSRA, ADIF);
#if ADC_READ_ADJEST == ADC_RIGHT_ADJUST_READ
	ADC_Value = ADCL;
	ADC_Value |=(ADCH<<8);
#elif ADC_READ_ADJEST == ADC_LEFT_ADJUST_READ
	ADC_Value = ADCH<<2;
	ADC_Value |=(ADCL>>6);
#endif

	return ADC_Value;
}



void ADC_Intrrupt_Enable(){

	SET_BIT(ADCSRA, ADIE);
}


void ADC_Intrrupt_Disable(){

	CLEAR_BIT(ADCSRA, ADIE);
}

/**
 *
 * @param ptfHandler
 */
void ADC_SetCallBack(void (*ptfHandler)(void))
{
	ADC_InterruptHandler = ptfHandler;
}

/**
 *
 *
 */
ISR(ADC_vect)
{
	if(ADC_InterruptHandler)
		ADC_InterruptHandler();
}

