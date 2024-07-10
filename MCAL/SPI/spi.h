/*
 * spi.h
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_


#include <avr/io.h>

void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);



#endif /* MCAL_SPI_SPI_H_ */
