/*
 * physics.c
 *
 *  Created on: Dec 2, 2023
 *      Author: TrongAnh
 */

#include "physics.h"
#include "main.h"
#include "global.h"

void turnOffAllLED(void){
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |AMBER_LED1_Pin
			| AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin | RED_PERD_Pin | GREEN_PERD_Pin, 1);
}

void turnOnAllLED(void){
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |AMBER_LED1_Pin
				| AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin | RED_PERD_Pin | GREEN_PERD_Pin, 0);
}

//AUTO MODE:
//turn on the led with index:	0: way 1
//								1: way 2
void autoRed(int index){
	if (index == 0){
		HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, AMBER_LED1_Pin | GREEN_LED1_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, AMBER_LED2_Pin | GREEN_LED2_Pin, 1);
	}
}
void autoAmber(int index){
	if (index == 0){
		HAL_GPIO_WritePin(GPIOA, AMBER_LED1_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | GREEN_LED1_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, AMBER_LED2_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin| GREEN_LED2_Pin, 1);
	}
}

void AutoGreen(int index){
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
 * 			1	-	AMBER
 * 			2	-	GREEN
 * @retval: None
 */
void setPedestrianLed(int index){
	if(index == 0){
		HAL_GPIO_WritePin(GPIOA, RED_PERD_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, GREEN_PERD_Pin, 1);
	}
	else if (index == 1){
		HAL_GPIO_WritePin(GPIOA, RED_PERD_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, GREEN_PERD_Pin, 0);
	}
	else if (index == 2){
		HAL_GPIO_WritePin(GPIOA, RED_PERD_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, GREEN_PERD_Pin, 0);
	}
}