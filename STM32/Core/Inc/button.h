/*
 * button.h
 *
 *  Created on: Nov 1, 2023
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"
#define NUM_BUTTON	4

#define PRESSED 0
#define RELEASE 1
#define KEY_PRESS_TIME 1000


void getButtonValue(void);
int isButtonShortPress(int index);
int isButtonLongPress(int index);
#endif /* INC_BUTTON_H_ */
