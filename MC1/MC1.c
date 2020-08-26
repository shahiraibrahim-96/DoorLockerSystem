/*
 * MC1.c
 *
 *  Created on: May 13, 2019
 *      Author: shahira ibrahim
 */
#include "lcd.h"
#include "keypad.h"
#include "timers.h"
#include "uart.h"
#include "hmi.h"

uint8 password[PASSWORD_LENGTH];

int main(void){
	uint8 key=0;
	bool passswoordCorrect;
    bool exist;
	LCD_init();
	UART_init();
	SREG  |= (1<<7);

	while(UART_receiveByte() != M2_READY);
	exist=UART_receiveByte();
	if(!exist){
		PASSWORD_config(g_inputPassword,g_newPassWord,PASSWORD_LENGTH);
		UART_sendByte(M2_READY);
		PASSWORD_sending(g_inputPassword,PASSWORD_LENGTH);
		g_storageFlag= UART_receiveByte();
		LCD_clearScreen();
		if(g_storageFlag){
			LCD_sendString("pass Is Saved");
		   _delay_ms(1000);
		}
		else{
			LCD_sendString("storing Failed");
			 _delay_ms(1000);
		}
	}

	else
	{

	}
	while(1){
		while(UART_receiveByte() != M2_READY){}
		PASSWORD_receiving(passwordReceived,PASSWORD_LENGTH);
		do{
			g_countingWrongAttempts=0;
			LCD_clearScreen();
			LCD_sendString("+ set New Pass");
			LCD_display_In_Location("- open Door",1,0);
			UART_sendByte(M2_READY);
			key=Keypad_getKeyPressed();
			UART_sendByte(key);
			_delay_ms(500);
			for(g_countingWrongAttempts=0;g_countingWrongAttempts<3;g_countingWrongAttempts++)
			{
				LCD_clearScreen();
				LCD_sendString("Enter Old Pass");
				LCD_goTo_Location(1,0);
				PASSWORD_insertion(password,PASSWORD_LENGTH);
				_delay_ms(500);
				passswoordCorrect=PASSWORD_checkValidity(password,passwordReceived,PASSWORD_LENGTH);
				if(passswoordCorrect)
				{
					LCD_clearScreen();
					LCD_sendString("PasswordsMatched");
					_delay_ms(1000);
					break;
				}
				else
				{
					LCD_clearScreen();
					LCD_sendString("wrong Password");
					_delay_ms(1000);
				}

			}

			UART_sendByte(M2_READY);
			UART_sendByte(g_countingWrongAttempts);
			if(g_countingWrongAttempts==3){
			TIMER1_CTCMode(FCPU_256,31250);
            _delay_ms(1000);
			LCD_clearScreen();

			 LCD_display_In_Location("wait for 60",0,0);
			 LCD_display_In_Location("seconds",1,0);
			while((g_MC1>0) && (g_MC1<=60) ){}

			TIMER1_OFF();
			LCD_clearScreen();
			g_MC1=0;
           }


		}while(g_countingWrongAttempts==3);

		if(key=='+'){
				LCD_clearScreen();
				LCD_sendString("Setting New Pass");
				_delay_ms(1000);
				LCD_clearScreen();
				PASSWORD_config(g_inputPassword,g_newPassWord,PASSWORD_LENGTH);
				UART_sendByte(M2_READY);
				PASSWORD_sending(g_newPassWord,PASSWORD_LENGTH);
				while(UART_receiveByte() != M2_READY){}
				g_storageFlag= UART_receiveByte();
				LCD_clearScreen();
				if(g_storageFlag)
				{
					LCD_sendString("NEW Pass Saved");
				     _delay_ms(1000);
				}
				else
				{
					LCD_sendString("storing Failed");
					 _delay_ms(1000);
				}

			}
			else if(key=='-'){
			LCD_clearScreen();
			TIMER1_CTCMode(FCPU_256,31250);
			_delay_ms(1000);

			LCD_sendString("Opening The Door");
			while(g_MC1 >0 && g_MC1<=15 ){}
			LCD_clearScreen();
			LCD_sendString("Closing The Door");
			while(g_MC1>15 && g_MC1<=30 ){}
			TIMER1_OFF();
			LCD_clearScreen();
			g_MC1=0;

		}
	}
}
