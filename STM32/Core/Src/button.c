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

struct keyget listButton[NUM_BUTTON] = {{RELEASE, RELEASE, RELEASE, RELEASE, 0, 0}};
GPIO_TypeDef * BUTTON_GPIO[NUM_BUTTON] = {BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port, BUTTON_PERD_GPIO_Port};
uint16_t BUTTON_PIN[NUM_BUTTON] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin, BUTTON_PERD_Pin};

/*
 * @brief:	get all the button value
 *
 * @param:	NONE
 * @retval:	NONE
 */

void getButtonValue(void) {
	for (int i = 0; i < NUM_BUTTON; i++){
		listButton[i].keyget1 = listButton[i].keyget2;
		listButton[i].keyget2 = listButton[i].keyget3;
		listButton[i].keyget3 = HAL_GPIO_ReadPin(BUTTON_GPIO[i], BUTTON_PIN[i]);
		if((listButton[i].keyget1 == listButton[i].keyget2) && (listButton[i].keyget2 == listButton[i].keyget3)){
			if (listButton[i].oldState != listButton[i].keyget3){
				listButton[i].oldState = listButton[i].keyget3;
				if (listButton[i].keyget3 == PRESSED){
					listButton[i].flag = 1;
					listButton[i].timePress = KEY_PRESS_TIME / TIME_CYCLE;
				}
			}
			else if (listButton[i].keyget3 == PRESSED){
				listButton[i].timePress--;
				if (listButton[i].timePress == 0){
					listButton[i].oldState = RELEASE;
				}
			}
		}
	}
}


/*
 * @brief:	check if the button is pressed or not
 *
 * @param:	index of button [0...3]
 * @retval:	1	-	button is pressed
 * 			0	-	button is not pressed
 */

int isButtonPress(int index){
	if (listButton[index].flag == 1){
		listButton[index].flag = 0;
		return 1;
	}
	return 0;
}
