/*
 * motor.h
 *
 *  Created on: May 2, 2019
 *      Author: shahira ibrahim
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"


/*function description: function for setting the output pins for motor*/
void motor_init(void);

/*function description:function for unlocking the door by spinning the motor in clock wise direction*/
void motor_UnLockingDoor(void);


/*function description:function for locking the door by spinning the motor in anti clock wise direction*/
void motor_LockingDoor(void);


void motor_stop(void);
#endif /* MOTOR_H_ */
