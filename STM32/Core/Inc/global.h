/*
 * global.h
 *
 *  Created on: Nov 3, 2023
 *      Author: DELL
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "FSM_traffic_light.h"
#include "scheduler.h"
#include "task.h"
#include <stdio.h>

#define TIME_CYCLE	10
#define NUM_TIMER	4

#define	INIT	10
#define OFF		0

//STATE for AUTO / MANUAL SETTING
#define	RED_GREEN	1
#define	RED_AMBER	2
#define	GREEN_RED	3
#define	AMBER_RED	4

//STATE for TUNING SETTING
#define	RED_ADJ		1
#define AMBER_ADJ	2
#define GREEN_ADJ	3

extern int timeRed;
extern int timeAmber;
extern int timeGreen;

extern int traffic_status;
extern int blinky_status;


//String use for UART
extern char str[];

//Interrupt use for PWM control
extern TIM_HandleTypeDef htim3;


extern UART_HandleTypeDef huart2;


//Variable use for FSM
extern int autoStatus;
extern int manualStatus;
extern int tuningStatus;
extern int perdStatus;

#endif /* INC_GLOBAL_H_ */
