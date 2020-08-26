/*
 * spi.c
 *
 *  Created on: Apr 30, 2019
 *      Author: shahira ibrahim
 */
#include "spi.h"
/*************************************function definition**************************************************/




/*function description :this function is used for setting SPI as a master
 * SPIE=0,disabling SPI interrupts
 * CPHA=0,CPOL=0 leading edge'rising edge' and sampling at the leading edge
 * DORD=0 sending out the MSB first
 * SPI2X=0 USING THe normal speed of SPI
 * using F_CPU/4 prescaler
 */
void SPI_initMaster(void){

	/*setting SS,MOSI,SCK  as output pins*/
	DDRB |=(1<<PB4)|(1<<PB5)|(1<<PB7);

	/*setting MISO as an input pin*/
	DDRB &=~(1<<PB6);

	/*set SPI as a master device and enabling the SPI*/
	SPCR |=(1<<MSTR)|(1<<SPE);
}


/*function description :this function is used to set SPI as a slave */
void SPI_initSlave(void){

	/*set MISO AS AN OUTPUT PIN*/
	DDRB |=0X40;

	/*setting SS,MOSI,SCK  as input pins*/
	DDRB &=~(0XB0);

	/*enabling SPI*/
	SPCR |=(1<<SPE);
}


/*this function is for sending a byte of data through SPI */
void SPI_sendByte(uint8 data){

	/*transmitting data to SPDR REgister*/
	SPDR=data;

	/*wait until SPSR is set and when it happens means the transfer is complete*/
	while(BIT_IS_CLEAR(SPSR,SPIF));

}


/*this function is for sending a string of data byte by byte through SPI */
void SPI_sendString(const uint8 *str){
	uint8 i=0;
	while(str[i] != '\0'){
		SPI_sendByte(str[i]);
		i++;
	}

}



/*this function is for receiving a byte of data through SPI */
uint8 SPI_receiveByte(void){

	/*wait until SPSR is set and when it happens means the transfer is complete*/
	while(BIT_IS_CLEAR(SPSR,SPIF));

	/*return the received byte from SPI data register*/
	  return SPDR;
}



/*this function is for receiving a string of data byte by byte through SPI */
void SPI_receiveString(uint8 *str){
	uint8 i=0;
	str[i]=SPI_receiveByte();

	/*using # character as my own null terminator so spi could know when to stop receiving data*/
	while(str[i] != '#'){
		i++;
		str[i]=SPI_receiveByte();

	}
	str[i]='\0';

}
