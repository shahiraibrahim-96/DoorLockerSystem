/*
 * i2c.h
 *
 *  Created on: May 7, 2019
 *      Author: shahira ibrahim
 */

#ifndef I2C_H_
#define I2C_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"


/****************************************preprocessor macros*****************************************/
/* I2C Status Bits in the TWSR Register */
#define I2C_START               0x08   /*start bit has been sent*/
#define I2C_REPEATED_START      0x10   /*repeated start bit has been sent*/
#define I2C_MT_SL_ADD_W_ACK     0x18   /*master has transmitted slave address and write request and acknowledgment is sent*/
#define I2C_MT_SL_ADD_R_ACK     0x40   /*master has transmitted slave address and read request and acknowledgment is sent*/
#define I2C_MT_DATA_ACK         0x28  /* master has transmitted data and acknowledgment is sent*/
#define I2C_MR_DATA_ACK         0x50  /*master has received data and acknowledgment is sent*/
#define I2C_MR_DATA_NACK        0x58  /*master has received data and doesn't send an acknowledgment which means it doesn't want to receive more data*/
/*************************************************************************************************************************************************************/






/************************************************functions prototype**********************************/


/*function description: choosing prescaler
 * choosing baud rate
 * assigning device address in case of slave state
 * activating the module
 */
void I2C_init(void);

/*function description:function for sending start bit*/
void I2C_start(void);

/*function description:function for sending stop bit*/
void I2C_stop(void);

/*function description:function for sending one byte of data through i2c module*/
void I2C_write(uint8 data);

/*function description:function for receiving one byte of data USING ACK BIT through i2c module*/
uint8 I2C_readWithACK(void);

/*function description:function for receiving one byte of data without USING ACK BIT through i2c module*/
uint8 I2C_readWithNACK(void);

/*function description: function for getting the status of i2c module*/
uint8 I2C_getStatus(void);


#endif /* I2C_H_ */
