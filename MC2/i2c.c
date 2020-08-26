/*
 * i2c.c
 *
 *  Created on: May 7, 2019
 *      Author: shahira ibrahim
 */
#include "i2c.h"


/*function description: choosing prescaler
 * choosing baud rate
 * assigning device address in case of slave state
 * activating the module
 */
void I2C_init(void){

   /*NO Prescaler is used*/
   TWSR=0;

   /*using 400000 kbps baud rate and after substituting in SCL frequency=(CPU Clock frequency)/(16 + 2(TWBR) ⋅ 4^TWPS)*/
   TWBR=0X02;

   /*MC address is used in case if of being slave device*/
   TWAR = 0b00000010;

   /*enabling I2C module*/
   TWCR =(1<<TWEN);

}


/*function description:function for sending start bit*/
void I2C_start(void){

	/* clearing flag at first ,enabling the module and sending start bit*/
	TWCR= (1<<TWINT)| (1<<TWEN) |(1<<TWSTA);

	 /*wait until is the start bit is sent*/
	 while(BIT_IS_CLEAR(TWCR,TWINT));

}

/*function description:function for sending stop bit*/
void I2C_stop(void){

	/* clearing flag at first ,enabling the module and sending stop bit*/
	TWCR= (1<<TWINT)| (1<<TWEN) |(1<<TWSTO);


}

/*function description:function for sending one byte of data through i2c module*/
void I2C_write(uint8 data){

    /*Writing data to TWDR register*/
	TWDR= data;

	/* clearing flag at first ,enabling the module*/
	TWCR= (1<<TWINT)| (1<<TWEN) ;

	/*wait until all data is written*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

}

/*function description:function for receiving one byte of data USING ACK BIT through i2c module*/
uint8 I2C_readWithACK(void){

	/* clearing flag at first ,enabling the module and enabling the ack bit*/
	TWCR= (1<<TWINT)| (1<<TWEN)|(1<<TWEA) ;

	/*wait until all data is ready*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/*read data*/
	return TWDR;
}

/*function description:function for receiving one byte of data without USING ACK BIT through i2c module*/
uint8 I2C_readWithNACK(void){

	/* clearing flag at first ,enabling the module and disabling the ack bit*/
	TWCR= (1<<TWINT)| (1<<TWEN) ;

	/*wait until all data is ready*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/*read data*/
	return TWDR;

}

/*function description: function for getting the status of i2c module*/
uint8 I2C_getStatus(void){

    uint8 status=TWSR &(0XF8);

    /*read status*/
	return status;
}

