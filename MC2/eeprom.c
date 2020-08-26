/*
 * eeprom.c
 *
 *  Created on: May 7, 2019
 *      Author: shahira ibrahim
 */

#include "eeprom.h"

/* function description: initiating EEPROM by initiating I2C module*/
void EEPROM_init(void){
	I2C_init();
}


/*function description: function for receiving one byte of data through EEPROM*/
uint8 EEPROM_readByte(uint16 address,uint8*data){

	/* send the start bit*/
	I2C_start();

	/*check if the start bit is sent*/
	if( I2C_getStatus() != I2C_START)  return ERROR;

	/* send the slave address
	 * A8 A9 A10 bits of the required memory address
	 * write request */
	I2C_write((uint8)(0xA0 | ((address & 0x0700)>>7)));

	/*check if master has transmitted slave address and write request and acknowledgment is sent*/
	if(I2C_getStatus() != I2C_MT_SL_ADD_W_ACK ) return ERROR;

	/*send memory address*/
	I2C_write((uint8)address);

	/*check if master has transmitted data and acknowledgment is sent*/
	if(I2C_getStatus() != I2C_MT_DATA_ACK ) return ERROR;

	/*send repeated start bit*/
	I2C_start();

	/*check if repeated start bit*/
	if( I2C_getStatus() != I2C_REPEATED_START)  return ERROR;

	/*send  slave address
	 * A8 A9 A10 bits of the required memory address
	 * read request*/
	I2C_write((uint8)( 0xA0| (((address &0x0700)>>7) | 1)));

	/*check if master has transmitted slave address and read request and acknowledgment is sent*/
	if(I2C_getStatus() != I2C_MT_SL_ADD_R_ACK)  return ERROR;

	/*read byte of memory without the acknowledgment*/
	*data=I2C_readWithNACK();

	/*check if master has received data and the acknowledgment wasn't sent*/
	if(I2C_getStatus() !=I2C_MR_DATA_NACK) return ERROR;

	/*send stop bit*/
	I2C_stop();

	return *data;
}


/*function description: function for sending one byte of data through EEPROM*/
uint8 EEPROM_writeByte(uint16 address,uint8 data){

	/* send the start bit*/
	I2C_start();

	/*check if the start bit is sent*/
	if( I2C_getStatus() != I2C_START)  return ERROR;

	/* send the slave address
	 * A8 A9 A10 bits of the required memory address
	 * write request */
	I2C_write((uint8)(0xA0 | ((address & 0x0700)>>7)));

	/*check if master has transmitted slave address and write request and acknowledgment is sent*/
	if(I2C_getStatus() != I2C_MT_SL_ADD_W_ACK ) return ERROR;

	/*send memory address*/
	I2C_write((uint8)address);

	/*check if master has transmitted data and acknowledgment is sent*/
	if(I2C_getStatus() != I2C_MT_DATA_ACK ) return ERROR;

	/*write one byte o data*/
	I2C_write(data);

	/*check if master transmit the data and acknowledgment is sent*/
	if(I2C_getStatus() != I2C_MT_DATA_ACK)  return ERROR;

	/*send stop bit*/
	I2C_stop();

	return SUCCESS;

}
