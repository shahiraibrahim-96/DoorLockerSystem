/*
 * adc.h
 *
 *  Created on: Apr 24, 2019
 *      Author: shahira ibrahim
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*********************in case of using ADC with interrupts**************************************/

extern volatile uint16 g_conversionResult;
/************************************************************************************************/


/*this enum for selecting ADC frequency clock prescaler division factor*/
typedef enum{
	DIVISION_2_0,DIVISION_2_1,DIVISION_4,DIVISION_8,DIVISION_16,DIVISION_32,DIVISION_64,DIVISION_128
}ADC_Prescaler;


/*this enum for selecting ADC reference voltage*/
typedef enum{
	AREF_REFERENCE,AVCC_REFERENCE,INTERNAL_REFERENCE=3
}reference_voltage;


/*this struct for setting ADC configuration*/
typedef struct{
	ADC_Prescaler prescaler;
	reference_voltage reference;
}ADC_Config;

/**********************************function prototypes*****************************************/


/*function description:this function for 1.enabling  ADC module
 * 2.choosing the voltage reference
 * 3.choosing prescaler
 * 4.in case of using interrupts it will set ADIE pin
 */
void ADC_init(const ADC_Config*configPtr);


/*function description:this function is for 1.starting conversion from analog signals to digital
 * 2.choosing ADC channel from 1->7
 * 3.returning ADC conversion value
 */
uint16 ADC_readChannel(uint8 channel_num);




#endif /* ADC_H_ */
