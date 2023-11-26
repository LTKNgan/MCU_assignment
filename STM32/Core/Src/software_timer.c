/*
 * software_timer.c
 *
 *  Created on: Nov 1, 2023
 *      Author: DELL
 */


#include "software_timer.h"

// set timer flag and timer counter
int timer1_flag = 0;
int timer1_counter = 0;

int timer2_flag = 0;
int timer2_counter = 0;

// set timer function
void setTimer1(int duration) {
	timer1_counter = duration/TIME_CYCLE;
	timer1_flag = 0;
}

void setTimer2(int duration) {
	timer2_counter = duration/TIME_CYCLE;
	timer2_flag = 0;
}

// timer run function
void timer1Run() {
	if (timer1_counter > 0)
	{
		timer1_counter--;
		if (timer1_counter <= 0)
		{
			timer1_flag = 1;
		}
	}
}

void timer2Run() {
	if (timer2_counter > 0)
	{
		timer2_counter--;
		if (timer2_counter <= 0)
		{
			timer2_flag = 1;
		}
	}
}

/////////////////////
void timerRun() {
	timer1Run();
	timer2Run();
}
