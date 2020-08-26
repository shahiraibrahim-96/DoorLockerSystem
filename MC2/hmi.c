/*
 * password.c
 *
 *  Created on: May 13, 2019
 *      Author: shahira ibrahim
 */
#include "hmi.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "eeprom.h"


uint8 g_inputPassword [PASSWORD_LENGTH];
uint8 g_newPassWord[PASSWORD_LENGTH];
uint8 passwordReceived[PASSWORD_LENGTH];
uint8 g_countingWrongAttempts=0;
bool g_passWordCorrect;
bool g_storageFlag;
bool g_alreadyThere;
uint8 g_storedPass[PASSWORD_LENGTH];

void PASSWORD_insertion( uint8 *inputPass,uint8 passwordSize){
	uint8 i=0;
	for(i=0;((Keypad_getKeyPressed() != 13) && (i<passwordSize));i++){
		inputPass[i]=Keypad_getKeyPressed();
		_delay_ms(300);
		if(inputPass[i]>=0 && inputPass[i] <=9 )
			LCD_interToString(inputPass[i]);
		else
			LCD_sendCharacter(inputPass[i]);
	}
}

bool PASSWORD_checkValidity(uint8 *inputPass,uint8 *savedPass,uint8 passwordSize){
	uint8 i;
	for(i=0;i<passwordSize;i++){
		if(inputPass[i] != savedPass[i]){
			 g_passWordCorrect=FALSE;
			return g_passWordCorrect;
		}
	}
	g_passWordCorrect=TRUE;
	return g_passWordCorrect;
}
void PASSWORD_config(uint8 *inputPass,uint8*savedPass,uint8 passwordSize){

		LCD_sendString("Enter password:");
		LCD_goTo_Location(1,0);
		PASSWORD_insertion(inputPass,passwordSize);
		do{
		LCD_clearScreen();
		LCD_sendString("Re_EnterPassword");
		LCD_goTo_Location(1,0);
		PASSWORD_insertion(savedPass,passwordSize);
		_delay_ms(500);
	}while(!(PASSWORD_checkValidity(inputPass,savedPass,passwordSize)));

}
void PASSWORD_sending(uint8 *savedPass,uint8 passwordSize){
	uint8 i=0;
	for(i=0;i<passwordSize;i++){
	while(UART_receiveByte() != M2_READY){}
	UART_sendByte(savedPass[i]);

	}
}
void PASSWORD_receiving(uint8 *receivedPass,uint8 passwordSize){
 uint8 i=0;
  for(i=0;i<passwordSize;i++){
	 UART_sendByte(M2_READY); // MC2 is ready
	 receivedPass[i]=UART_receiveByte(); // receive the string
  }
}
uint8 PASSWORD_storing(uint8 *receivedPass,uint8 passwordSize){
	uint8 i,errorCheck=0;
	for(i=0;i<passwordSize;i++){
		errorCheck=EEPROM_writeByte(0x0311+i,receivedPass[i]);
		_delay_ms(10);
	}
	return errorCheck;
}

void PASSWORD_restored(uint8 *savedPass,uint8 passwordSize){
	uint8 i,data=0;
	for(i=0;i<passwordSize;i++){
		savedPass[i]=EEPROM_readByte(0x0311+i,&data);
	}

}

bool PASSWORD_isExist(uint8 *restoredPass,uint8 passwordSize){
	uint8 i,data=0,countToFive=0;
	for(i=0;i<passwordSize;i++){
		restoredPass[i]=EEPROM_readByte(0x0311+i,&data);
		if(restoredPass[i] == 255) countToFive++;
	}
   if(countToFive == 5)
   {
	   g_alreadyThere =FALSE;
	   return  g_alreadyThere;
   }
   else
   {
	   g_alreadyThere =TRUE;
	   return  g_alreadyThere;
   }
}
