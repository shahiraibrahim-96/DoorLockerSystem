/*
 * MC2.c
 *
 *  Created on: May 16, 2019
 *      Author: shahira ibrahim
 */
#include "uart.h"
#include "eeprom.h"
#include "motor.h"
#include "hmi.h"
#include "buzzer.h"
#include "timers.h"
#include "lcd.h"

int main(void)
{
	LCD_init();
	uint8 key=0,i=0;
	bool state;
	BUZZER_init;
	UART_init();
	EEPROM_init();
	motor_init();

	SREG  |= (1<<7);
	state= PASSWORD_isExist(g_storedPass,PASSWORD_LENGTH);
	UART_sendByte(M2_READY);
	UART_sendByte(state);
	if(!state){
	while(UART_receiveByte() != M2_READY){}
	PASSWORD_receiving(passwordReceived,PASSWORD_LENGTH);
	UART_sendByte(PASSWORD_storing(passwordReceived,PASSWORD_LENGTH));
	}
	else
	{

	}

	while(1){
		PASSWORD_restored(g_storedPass,PASSWORD_LENGTH);
		UART_sendByte(M2_READY);
		PASSWORD_sending(g_storedPass,PASSWORD_LENGTH);
		while(UART_receiveByte() != M2_READY){}
		key=UART_receiveByte();
		_delay_ms(500);
		while(UART_receiveByte() != M2_READY){}
		g_countingWrongAttempts=UART_receiveByte();
		if(g_countingWrongAttempts==3){
			TIMER1_CTCMode(FCPU_256,31250);
			     _delay_ms(1000);
			     BUZZER_ON;
			 	while((g_MC2>0) && (g_MC2<=60) ){}
			 	TIMER1_OFF();
			 	BUZZER_OFF;
			 	g_MC2=0;

		}
		else
		{


		if(key=='+'){
			  while(UART_receiveByte() != M2_READY){}
			  PASSWORD_receiving(passwordReceived,PASSWORD_LENGTH);
			  UART_sendByte(M2_READY);
			  state=PASSWORD_storing(passwordReceived,PASSWORD_LENGTH);
				UART_sendByte(state);
				PASSWORD_restored(g_storedPass,PASSWORD_LENGTH);
				for(i=0;i<5;i++){
					LCD_interToString(g_storedPass[i]);
				}



	}
		else if(key=='-'){
			TIMER1_CTCMode(FCPU_256,31250);
				_delay_ms(1000);
				motor_UnLockingDoor();
				while((g_MC2>0) && (g_MC2<=15) ){}
				motor_LockingDoor();
				while((g_MC2>15) && (g_MC2<=30) ){}
				TIMER1_OFF();
				motor_stop();
				g_MC2=0;
		}}
}
}
