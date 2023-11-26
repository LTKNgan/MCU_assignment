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

int segment_buffer[] = {0, 0, 0, 0};
