/*
 * uart.c
 *
 *  Created on: Apr 30, 2019
 *      Author: shahira ibrahim
 */
#include "uart.h"

/*****************************************functions definition************************************/

/*function description:this function is used to setup the required uart frame
 * disabling frame error ,data over run error and parity error bits by clearing (FE,DOR,PE)bits
 * using one stop bit by clearing USBS bit
 * using asynchronous operation by clearing UMSEL bit
 */
void UART_init(void){

	/*u2x for double transmission speed*/
	UCSRA =(1<<U2X);

	/*enabling receiving and transmitting pins*/
	UCSRB =(1<<RXEN)|(1<<TXEN);

	/*setting URSEL SO I CAN write in UCSRC and also using 8 data bits*/
	UCSRC =(1<<URSEL) |(1<<UCSZ1)|(1<<UCSZ0);

	/*clearing URSEL bit so i can write in UBRRH register and putting the  first 8 bits of UBRR value in UBRRL and last four bits in UBRRH*/
	UBRRH=UBRR_VALUE>>8;
	UBRRL=UBRR_VALUE;

}


/*function description :this function is used for transmitting one byte of data through uart*/
void UART_sendByte(const uint8 data){

    /*wait until the UDRE is set and then write to UDR register*/
	while(BIT_IS_CLEAR(UCSRA,UDRE));

	/*writing data to UDR Register*/
	UDR=data;
}




/*function description :this function is used for receiving one byte of data through uart*/
uint8 UART_receiveByte(void){

	/*wait until the RXC flag is set and then read the data from UDR Register*/
	while(BIT_IS_CLEAR(UCSRA,RXC));

	/*reading the data from udr register*/
	return UDR;
}


/*function description :this function is used for transmitting string through uart*/
void UART_sendString(const uint8*data){

	/*counter variable*/
	uint8 i=0;

	/*loop through the string and send it byte by byte until it reaches the null terminator*/
	while(data[i] != '\0'){
		UART_sendByte(data[i]);
		i++;
	}
}


/*function description :this function is used for receiving string through uart*/
void UART_receiveString(uint8 *str){

	/*counter variable*/
	uint8 i=0;

	str[i]=UART_receiveByte();
	/*loop through the string and send it byte by byte until it reaches special character '*'which i set it as a null terminator so the function know when to stop */
	while(str[i] != 13){
		i++;
		str[i]=UART_receiveByte();


	}

	/*putting a null terminator at the end of the string*/
	str[i]='\0';

}
