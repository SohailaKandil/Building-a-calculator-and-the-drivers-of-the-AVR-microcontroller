/*
 * Dio.h
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_


#include <avr/io.h>
#include <util/delay.h>
#include "../../Bit_math.h"
#include "../../std_types.h"
#include "Dio_types.h"
#include "Dio_Config.h"






void Dio_init();
void Dio_Write(channel_t ch,Dio_state_t state);
void Dio_Pin_Toggle(channel_t ch);
Dio_state_t Dio_Read(channel_t ch);




#endif /* MCAL_DIO_DIO_H_ */
