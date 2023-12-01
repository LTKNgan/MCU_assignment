/*
 * global.c
 *
 *  Created on: Nov 3, 2023
 *      Author: DELL
 */

#include "global.h"

// time for traffic light
int timeRed;
int timeAmber;
int timeGreen;

// status of traffic light
int traffic_status = INIT;
int blinky_status = INIT;

char str[50];

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

int segment_buffer[4] = {0,0,0,0};
