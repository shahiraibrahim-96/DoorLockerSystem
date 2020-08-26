/*
 * eeprom.h
 *
 *  Created on: May 7, 2019
 *      Author: shahira ibrahim
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "i2c.h"

/***************************************preprocessors*********************************************/

#define ERROR 0   /*it's used as an indication in case of some thing went wrong through transaction process*/
#define SUCCESS 1 /*it's used as an indication that the process of sending or receiving data is correct*/
/****************************************************************************************************/


/********************************************functions prototypes***********************************/

/* function description: initiating EEPROM by initiating I2C module*/
void EEPROM_init(void);

/*function description: function for receiving one byte of data through EEPROM*/
uint8 EEPROM_readByte(uint16 address,uint8*data);

/*function description: function for sending one byte of data through EEPROM*/
uint8 EEPROM_writeByte(uint16 address,uint8 data);

#endif /* EEPROM_H_ */
