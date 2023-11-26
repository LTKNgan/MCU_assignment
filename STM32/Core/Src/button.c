/*
 * button.c
 *
 *  Created on: Nov 1, 2023
 *      Author: DELL
 */
#include "button.h"

struct keyget {
	int keyget1;
	int keyget2;
	int keyget3;
	int oldState;
	int flag;
	int timePress;
};

struct keyget button1 = {RELEASE, RELEASE, RELEASE, RELEASE, 0, 0};
struct keyget button2 = {RELEASE, RELEASE, RELEASE, RELEASE, 0, 0};
struct keyget button3 = {RELEASE, RELEASE, RELEASE, RELEASE, 0, 0};

// get button value
void getKey1() {
	button1.keyget1 = button1.keyget2;
	button1.keyget2 = button1.keyget3;
	button1.keyget3 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
	if (button1.keyget1 == button1.keyget2 && button1.keyget2 == button1.keyget3) {
		if (button1.oldState != button1.keyget3) {
			button1.oldState = button1.keyget3;
			if (button1.keyget3 == PRESSED) {
				button1.flag = 1;
				button1.timePress = KEY_PRESS_TIME/TIME_CYCLE;
			}
		}
		else if (button1.keyget3 == PRESSED){
			button1.timePress--;
			if (button1.timePress == 0) {
				button1.oldState = RELEASE;
			}
		}
	}
}

void getKey2() {
	button2.keyget1 = button2.keyget2;
	button2.keyget2 = button2.keyget3;
	button2.keyget3 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
	if (button2.keyget1 == button2.keyget2 && button2.keyget2 == button2.keyget3) {
		if (button2.oldState != button2.keyget3) {
			button2.oldState = button2.keyget3;
			if (button2.keyget3 == PRESSED) {
				button2.flag = 1;
				button2.timePress = KEY_PRESS_TIME/TIME_CYCLE;
			}
		}
		else if (button2.keyget3 == PRESSED){
			button2.timePress--;
			if (button2.timePress == 0) {
				button2.oldState = RELEASE;
			}
		}
	}
}

void getKey3() {
	button3.keyget1 = button3.keyget2;
	button3.keyget2 = button3.keyget3;
	button3.keyget3 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
	if (button3.keyget1 == button3.keyget2 && button3.keyget2 == button3.keyget3) {
		if (button3.oldState != button3.keyget3) {
			button3.oldState = button3.keyget3;
			if (button3.keyget3 == PRESSED) {
				button3.flag = 1;
				button3.timePress = KEY_PRESS_TIME/TIME_CYCLE;
			}
		}
		else if (button3.keyget3 == PRESSED){
			button3.timePress--;
			if (button3.timePress == 0) {
				button3.oldState = RELEASE;
			}
		}
	}
}

void getButtonValue() {
	getKey1();
	getKey2();
	getKey3();
}

// check if button is pressed
int isButton1Pressed()
{
	if (button1.flag == 1) {
		button1.flag = 0;
		return 1;
	}
	return 0;
}

int isButton2Pressed()
{
	if (button2.flag == 1) {
		button2.flag = 0;
		return 1;
	}
	return 0;
}

int isButton3Pressed()
{
	if (button3.flag == 1) {
		button3.flag = 0;
		return 1;
	}
	return 0;
}
