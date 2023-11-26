/*
 * button.h
 *
 *  Created on: Nov 1, 2023
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define PRESSED 0
#define RELEASE 1
#define KEY_PRESS_TIME 1000

void getButtonValue();

int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();

#endif /* INC_BUTTON_H_ */
