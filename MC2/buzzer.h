/*
 * buzzer.h
 *
 *  Created on: May 14, 2019
 *      Author: shahira ibrahim
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/*set pin PD4 as an output pin for buzzer*/
#define BUZZER_init DDRA |=(1<<PA1)

/*turn buzzer on*/
#define BUZZER_ON   PORTA |=(1<<PA1)

/*turn buzzer off*/
#define BUZZER_OFF  PORTA &=~(1<<PA1)

#endif /* BUZZER_H_ */
