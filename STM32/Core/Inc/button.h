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

GPIO_TypeDef * BUTTON_GPIO[NUM_BUTTON];
uint16_t BUTTON_PIN[NUM_BUTTON];

void getButtonValue(void);
int isButtonPress(int index);
#endif /* INC_BUTTON_H_ */
