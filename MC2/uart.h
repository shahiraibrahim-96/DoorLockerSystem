/*
 * uart.h
 *
 *  Created on: Apr 30, 2019
 *      Author: shahira ibrahim
 */

#ifndef UART_H_
#define UART_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/***********************************PREPROCESSOR MACROS********************************************/
#define F_CPU_BAUD_RATE 9600
#define F_CPU_CLOCK     (1000000UL)
#define UBRR_VALUE    (((F_CPU_CLOCK/(8UL *F_CPU_BAUD_RATE)))-1)
/************************************************************************************************/



/**********************************functions prototype*******************************************/


/*function description:this function is used to setup the required uart frame
 * disabling frame error ,data over run error and parity error bits by clearing (FE,DOR,PE)bits
 * using one stop bit by clearing USBS bit
 * using asynchronous operation by clearing UMSEL bit
 */
void UART_init(void);

/*function description :this function is used for transmitting one byte of data through uart*/
void UART_sendByte(const uint8 data);

/*function description :this function is used for receiving one byte of data through uart*/
uint8 UART_receiveByte(void);

/*function description :this function is used for transmitting string through uart*/
void UART_sendString(const uint8*data);

/*function description :this function is used for receiving string through uart*/
void UART_receiveString(uint8 *str);

#endif /* UART_H_ */
