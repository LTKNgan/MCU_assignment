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

#define TIME_CYCLE 10

extern int timeRed;
extern int timeAmber;
extern int timeGreen;

extern int traffic_status;
extern int blinky_status;

enum {INIT};			// common initial state
enum {RED1_GREEN2=1, RED1_AMBER2, GREEN1_RED2, AMBER1_RED2};
enum {RED=1, AMBER, GREEN};

extern char str[];

extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart2;

extern int segment_buffer[];

#endif /* INC_GLOBAL_H_ */
