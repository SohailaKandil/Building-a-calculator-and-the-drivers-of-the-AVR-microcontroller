/*
 * Dio_Config.c
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */

#include "Dio_Config.h"
/*
#include "avr/io.h"
#include "Dio.h"
#include "../../Bit_math.h"
*/

Dio_pin_config pin[PIN_COUNT]={
		//{PORT_D,PIN_7,OUTPUT},
		//pins of lcd
		{PORT_A,PIN_4,OUTPUT},
		{PORT_A,PIN_5,OUTPUT},
		{PORT_A,PIN_6,OUTPUT},
		{PORT_A,PIN_7,OUTPUT},
		{PORT_B,PIN_0,OUTPUT},
		{PORT_B,PIN_1,OUTPUT},
		{PORT_B,PIN_2,OUTPUT},
		//pins of keypad
		{PORT_C,PIN_0,OUTPUT},
		{PORT_C,PIN_1,OUTPUT},
		{PORT_C,PIN_2,OUTPUT},
		{PORT_C,PIN_3,OUTPUT},
		{PORT_C,PIN_4,INPUT},
		{PORT_C,PIN_5,INPUT},
		{PORT_C,PIN_6,INPUT},
		{PORT_C,PIN_7,INPUT},

		{PORT_B,PIN_4,OUTPUT},
		//{PORT_B,PIN_5,OUTPUT},
		{PORT_D,PIN_7,OUTPUT},

};


