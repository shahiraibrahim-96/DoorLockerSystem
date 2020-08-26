/*
 * motor.c

 *
 *  Created on: May 2, 2019
 *      Author: shahira ibrahim
 */
#include "motor.h"

/*function description: function for setting the output pins for motor*/
void motor_init(void){

	/*set PB4 PB5 as output pins*/
	DDRB |=(1<<PB4);
	DDRB |=(1<<PB5);

	/*initiating motor at zero speed at first*/
	PORTB &=~(1<<PB4);
	PORTB &=~(1<<PB5);

}

/*function description:function for unlocking the door by spinning the motor in clock wise direction*/
void motor_UnLockingDoor(void){

	PORTB |=(1<<PB4);
	PORTB &=~(1<<PB5);
}

/*function description:function for locking the door by spinning the motor in anti clock wise direction*/
void motor_LockingDoor(void){

	PORTB &=~(1<<PB4);
	PORTB |=(1<<PB5);
}

void motor_stop(void){

	PORTB &=~(1<<PB4);
    PORTB &=~(1<<PB5);
}
