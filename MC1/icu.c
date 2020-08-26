#include "icu.h"

static volatile void(*g_callBackPtr)(void) = NULL_PTR;

/*********************************functions implementation****************************************/

/*
 * function description:ISR calling back the function that should be executed when an edge is captured
 */
ISR(TIMER1_CAPT_vect){

	if(g_callBackPtr != NULL_PTR){
		(*g_callBackPtr)();
	}
}

/*function description:this function is for enabling icu in timer1
 * setting icu edge type detection
 *  setting icu clock
 * initializing timer1 register
 */
void Icu_init(const Icu_Config * configPtr){

	 /*set ICP1/PD6 as an input pin */
	CLEAR_BIT(DDRD,PD6);

	 /*these tow pins should be set in non_pwm_mode*/
	TCCR1A = (1<<FOC1A)|(1<<FOC1B);

	 /*setting the edge detection type*/
	TCCR1B =(TCCR1B & 0XBF) | ((configPtr->edge)<<6);

	/*setting the required clock*/
	TCCR1B =(TCCR1B & 0XF8) |(configPtr->clock);

	/*clearing counting register in timer1*/
	TCNT1=0;

	/*clearing input capture register in timer1*/
	ICR1=0;

	  /*enable interrupt in timer1*/
	TIMSK |=(1<<TICIE1);
}


/*function description:function for setting icu edge type detection*/
void Icu_setEgdeType(const Icu_EdgeType edgeType){
	TCCR1B =(TCCR1B & 0XBF) | (edgeType<<6);
}

/*function description:function to set the address of call back function*/
void Icu_setCallBack(void(*a_ptr)(void)){

	g_callBackPtr=a_ptr;
}


/* function description:function for clearing tcnt1 register in timer1 */
Icu_clearTimerValue(void){
	TCNT1=0;
}


/* function description:function for canceling all icu and timer1 configuration*/
void Icu_deleteInit(void){
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;
	CLEAR_BIT(TIMSK,TICIE1);
}


/*function description: function for getting the value of ICR*/
uint16 Icu_getInputCaptureValue (void){
	return ICR1;
}
