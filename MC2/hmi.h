/*
 * password.h
 *
 *  Created on: May 13, 2019
 *      Author: shahira ibrahim
 */

#ifndef HMI_H_
#define HMI_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

#define PASSWORD_LENGTH 5
#define M2_READY 0x10

extern uint8 g_inputPassword [PASSWORD_LENGTH];
extern uint8 g_newPassWord[PASSWORD_LENGTH];
extern uint8 g_countingWrongAttempts;
extern bool g_passWordCorrect;
extern bool g_storageFlag;
extern bool g_alreadyThere;
extern uint8 passwordReceived[PASSWORD_LENGTH];
extern uint8 g_storedPass[PASSWORD_LENGTH];

void PASSWORD_insertion( uint8 *inputPass,uint8 passwordSize);
bool PASSWORD_checkValidity(uint8 *inputPass,uint8 *savedPass,uint8 passwordSize);
void PASSWORD_sending(uint8 *savedPass,uint8 passwordSize);
void PASSWORD_receiving(uint8 *receivedPass,uint8 passwordSize);
void PASSWORD_config(uint8 *inputPass,uint8*savedPass,uint8 passwordSize);
void PASSWORD_restored(uint8 *savedPass,uint8 passwordSize);
uint8 PASSWORD_storing(uint8 *receivedPass,uint8 passwordSize);
bool PASSWORD_isExist(uint8 *restoredPass,uint8 passwordSize);
#endif /* HMI_H_ */
