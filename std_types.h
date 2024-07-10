/*
 * std_types.h
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/*..........section:includes.........*/


/*.............section:data type declaration.......... */

typedef unsigned char       uint8;
typedef unsigned short       uint16;
typedef unsigned long       uint32;

typedef signed char       sint8;
typedef signed short       sint16;
typedef signed long      sint32;

//#define NULL         (void)(0)


typedef uint8     Std_ReturnType;


/*..........section:macro declaration ............*/
#define ZERO_INIT        0

#define E_OK       1
#define E_NOT_OK   0




#endif /* STD_TYPES_H_ */
