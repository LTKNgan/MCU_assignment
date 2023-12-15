/*
 * software_timer.c
 *
 *  Created on: Dec 7, 2023
 *      Author: DELL
 */


#include "software_timer.h"

//	Array of timer variable
//	timer_counter[0]:	counter for auto mode with F = 1HZ
//	timer_counter[1]:	counter for blink with F = 4HZ
//	timer_counter[2]:	for pedestrian count down, = 4*timeRed
//	timer_counter[3]:	counter for buzzer

int timer_counter[NUM_TIMER] = {0};
int timer_flag[NUM_TIMER] = {0};
int timer_duration[NUM_TIMER] = {1000, 250, 0, 0};

// set timer flag and timer counter
void setTimer(int duration, int index){
	timer_counter[index] = duration / TIME_CYCLE;
	timer_flag[index] = 0;
}

void timerRun(){
	for (int i = 0; i < NUM_TIMER; i++){
		if (timer_counter[i] > 0){
			timer_counter[i]--;
			if (timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}
