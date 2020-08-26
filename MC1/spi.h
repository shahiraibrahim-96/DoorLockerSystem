/*
 * spi.h
 *
 *  Created on: Apr 30, 2019
 *      Author: shahira ibrahim
 */

#ifndef SPI_H_
#define SPI_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/***********************************function prototypes******************************************/


/*function description :this function is used for setting SPI as a master
 * SPIE=0,disabling SPI interrupts
 * CPHA=0,CPOL=0 leading edge'rising edge' and sampling at the leading edge
 * DORD=0 sending out the MSB first
 * SPI2X=0 USING THe normal speed of SPI
 * using F_CPU/4 prescaler
 */
void SPI_initMaster(void);

/*function description :this function is used to set SPI as a slave */
void SPI_initSlave(void);

/*this function is for sending a byte of data through SPI */
void SPI_sendByte(uint8 data);

/*this function is for sending a string of data byte by byte through SPI */
void SPI_sendString(const uint8 *str);

/*this function is for receiving a byte of data through SPI */
uint8 SPI_receiveByte(void);

/*this function is for receiving a string of data byte by byte through SPI */
void SPI_receiveString(uint8 *str);


#endif /* SPI_H_ */
