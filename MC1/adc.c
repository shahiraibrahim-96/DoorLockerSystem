/*
 * adc.c
 *
 *  Created on: Apr 24, 2019
 *      Author: shahira ibrahim
 */
#include "adc.h"

/******************************global variable prototype*****************************************/
volatile uint16 g_conversionResult=0;
/**************************************************************************************************/





/*********************************preprocessing functions**************************************/

     uint16 ADC_readChannel(uint8 channel_num);

/************************************************************************************************/





/*******************************************functions implementations****************************************/



/*function description:this function for 1.enabling  ADC module
* 2.choosing the voltage reference
* 3.choosing prescaler
* 
*/
void ADC_init(const ADC_Config*configPtr)
{
	/*making ADLAR=0 */
	ADMUX=0;

	/*setting the voltage reference*/
	ADMUX=(ADMUX & 0x3F) |((configPtr->reference)<<6);

	/*enabling the ADC*/
	ADCSRA |= (1<<ADEN) ;

	/*setting the required prescaler*/
	ADCSRA =(ADCSRA & 0XF8) | ((configPtr->prescaler) & 0X07);


}






/*function description:this function is for 1.starting conversion from analog signals to digital
 * 2.choosing ADC channel from 1->7
 * 3.returning ADC conversion value
 */
uint16 ADC_readChannel(uint8 channel_num)
{
	/*setting the required ADC channel*/
	ADMUX = (ADMUX & 0XE0)|(channel_num & 0x07);

	/*starting conversion from analog signals to digital*/
	SET_BIT(ADCSRA,ADSC);

	/*waiting until conversion is done*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	/*clearing ADC interrupt flag by setting ADIF pin*/
	SET_BIT(ADCSRA,ADIF);

	/* return the digital output*/
	return ADC;

}









