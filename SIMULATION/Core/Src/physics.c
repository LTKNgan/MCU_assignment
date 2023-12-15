/*
 * physics.c
 *
 *  Created on: Dec 7, 2023
 *      Author: DELL
 */


#include "physics.h"

void turnOffAllLED(void){
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |AMBER_LED1_Pin
			| AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin | RED_PERD_Pin | GREEN_PERD_Pin, 1);
}

void turnOnAllLED(void){
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |AMBER_LED1_Pin
				| AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin | RED_PERD_Pin | GREEN_PERD_Pin, 0);
}

//AUTO / MANUAL MODE:
//turn on the led with index:	0: way 1
//								1: way 2
void turnOnRed(int index){
	if (index == 0){
		HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, AMBER_LED1_Pin | GREEN_LED1_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, AMBER_LED2_Pin | GREEN_LED2_Pin, 1);
	}
}
//turn on the led with index:	0: way 1
//								1: way 2
void turnOnAmber(int index){
	if (index == 0){
		HAL_GPIO_WritePin(GPIOA, AMBER_LED1_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | GREEN_LED1_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, AMBER_LED2_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin| GREEN_LED2_Pin, 1);
	}
}

//turn on the led with index:	0: way 1
//								1: way 2
void turnOnGreen(int index){
	if (index == 0){
		HAL_GPIO_WritePin(GPIOA, GREEN_LED1_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | AMBER_LED1_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, GREEN_LED2_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin| AMBER_LED2_Pin, 1);
	}
}

//TUNING MODE:
//Blink the suitable led
void blinkyRed(void){
	if(timer_flag[1] == 1){
		HAL_GPIO_TogglePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin);
		setTimer(timer_duration[1], 1);
	}
}

void blinkyAmber(void){
	if(timer_flag[1] == 1){
		HAL_GPIO_TogglePin(GPIOA, AMBER_LED1_Pin | AMBER_LED2_Pin);
		setTimer(timer_duration[1], 1);
	}
}

void blinkyGreen(void){
	if (timer_flag[1] == 1){
		HAL_GPIO_TogglePin(GPIOA, GREEN_LED1_Pin | GREEN_LED2_Pin);
		setTimer(timer_duration[1], 1);
	}
}

void clearRoadLed(void){
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |
			AMBER_LED1_Pin | AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin, 1);
}

/*
 * @brief: set the pedestrian led
 *
 * @param:	0	-	RED
 * 			1	-	GREEN
 * @retval: None
 */
void setPedestrianLed(int index){
	if(index == 0){
		HAL_GPIO_WritePin(GPIOA, RED_PERD_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, GREEN_PERD_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, RED_PERD_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, GREEN_PERD_Pin, 0);
	}
}

void unsetPedestrianLed(int index) {
	if (index == 0)
		HAL_GPIO_WritePin(GPIOA, RED_PERD_Pin, 1);
	else if (index == 1)
		HAL_GPIO_WritePin(GPIOA, GREEN_PERD_Pin, 1);
}
