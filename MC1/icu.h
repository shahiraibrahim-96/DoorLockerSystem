/*
 * icu.h
 *
 *  Created on: Apr 29, 2019
 *      Author: shahira ibrahim
 */

#ifndef ICU_H_
#define ICU_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/* this enum for selecting clock frequency*/
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CP_8,F_CPU_16,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

/*this enum for selection the ICU edge type detection*/
typedef enum{
	FALLING,RAISING
}Icu_EdgeType;

/*this struct for setting ICU configuration */
typedef struct{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_Config;

/***********************************function prototypes**********************************************/

/*function description:this function is for enabling icu in timer1
 * setting icu edge type detection
 *  setting icu clock
 * initializing timer1
 */
void Icu_init(const Icu_Config *configPtr);

/*function description: function for getting the value of ICR*/
uint16 Icu_getInputCaptureValue (void);

/*function description:function for setting icu edge type detection*/
void Icu_setEgdeType(Icu_EdgeType edgeType);

/*function description:function to set the address of call back function*/
void Icu_setCallBack(void(*a_ptr)(void));

/* function description:function for clearing tcnt1 register in timer1 */
void Icu_clearTimerValue(void);

/* function description:function for canceling all icu and timer1 configuration*/
void Icu_deleteInit(void);

#endif /* ICU_H_ */
