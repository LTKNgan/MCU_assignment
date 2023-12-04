/*
 * fsm.c
 *
 *  Created on: Dec 3, 2023
 *      Author: TrongAnh
 */

#include "fsm.h"

// init status
int trafficMode = INIT;
int autoStatus = INIT;
int manualStatus = OFF;
int tuningStatus = OFF;
int perdStatus = OFF;

//clock for system - F = 1HZ
int clock_counter = 0; // clock of traffic way 1
int clock_counter_1 = 0; // clock of traffic way 2
//
int timeRed = 5;
int timeAmber = 2;
int timeGreen = 3;

void fsm_traffic(void){
	switch(trafficMode){
	case INIT:
		trafficMode = AUTO_MODE;
		if (timeRed != (timeAmber + timeGreen)){
			trafficMode = ERROR_MODE;
		}
		// prepare for auto mode
		autoStatus = INIT;
		manualStatus = OFF;
		tuningStatus = OFF;
		break;
	case AUTO_MODE:
		fsm_traffic_auto_mode();
		if (isButtonLongPress(0)){
			trafficMode = MANUAL_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO MANUAL MODE#\r\n"),500);
			// TODO: prepare for next mode
			manualStatus = INIT;
			autoStatus= OFF;
			tuningStatus = OFF;
		}
		else if (isButtonLongPress(1)){
			trafficMode = TUNING_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO TUNING MODE#\r\n"),500);
			// TODO: prepare for next mode
			tuningStatus = INIT;
			autoStatus = OFF;
			manualStatus = OFF;
		}
		break;
	case MANUAL_MODE:
		fsm_traffic_manual_mode();
		if (isButtonLongPress(0)){
			trafficMode = AUTO_MODE;
			// TODO: prepare for next mode
			autoStatus = INIT;
			manualStatus = OFF;
			tuningStatus = OFF;
		}
		else if (isButtonLongPress(1)){
			trafficMode = TUNING_MODE;
			//TODO: prepare for next mode
			tuningStatus = INIT;
			autoStatus = OFF;
			manualStatus = OFF;
		}
		break;
	case TUNING_MODE:
		fsm_traffic_tunning_mode();
		if (isButtonLongPress(0)){
			trafficMode = MANUAL_MODE;
			//TODO: prepare for next mode
			manualStatus = INIT;
			autoStatus = OFF;
			tuningStatus = OFF;
		}
		else if (isButtonLongPress(1)){
			trafficMode = AUTO_MODE;
			//TODO: prepare for next mode
			autoStatus = INIT;
			manualStatus = OFF;
			tuningStatus = OFF;
		}
		break;
	default:
		break;
	}
}

void fsm_traffic_auto_mode(void){
	switch(autoStatus){
	case OFF:
		// do nothing
		break;
	case INIT:
		autoStatus = RED_GREEN;
		// prepare for red green state
		clock_counter = timeRed;
		clock_counter_1 = timeGreen;
		clearRoadLed();
		break;
	case RED_GREEN:
		turnOnRed(0);
		turnOnGreen(1);
		if (clock_counter_1 == 0){
			autoStatus = RED_AMBER;
			clock_counter = timeRed - timeGreen;
			clock_counter_1 = timeAmber;
			clearRoadLed();
		}
		break;
	case RED_AMBER:
		turnOnRed(0);
		turnOnAmber(1);
		if (clock_counter_1 == 0){
			autoStatus = GREEN_RED;
			clock_counter = timeGreen;
			clock_counter_1 = timeRed;
			clearRoadLed();
		}
		break;
	case GREEN_RED:
		turnOnGreen(0);
		turnOnRed(1);
		if (clock_counter == 0){
			autoStatus = AMBER_RED;
			clock_counter = timeAmber;
			clock_counter_1 = timeRed - timeGreen;
			clearRoadLed();
		}
		break;
	case AMBER_RED:
		turnOnAmber(0);
		turnOnRed(1);
		if (clock_counter == 0){
			autoStatus = RED_GREEN;
			clock_counter = timeRed;
			clock_counter_1 = timeGreen;
		}
		break;
	default:
		break;
	}
}
void fsm_traffic_manual_mode(void){
	switch(manualStatus){
	case OFF:
		// do nothing
		break;
	case INIT:
		manualStatus = RED_GREEN;
		clearRoadLed();
		break;
	case RED_GREEN:
		turnOnRed(0);
		turnOnGreen(1);
		if (isButtonShortPress(0)){
			manualStatus = RED_AMBER;
			clearRoadLed();
		}
		break;
	case RED_AMBER:
		turnOnRed(0);
		turnOnAmber(1);
		if(isButtonShortPress(0)){
			manualStatus = GREEN_RED;
			clearRoadLed();
		}
		break;
	case GREEN_RED:
		turnOnGreen(0);
		turnOnRed(1);
		if(isButtonShortPress(0)){
			manualStatus = AMBER_RED;
			clearRoadLed();
		}
		break;
	case AMBER_RED:
		turnOnAmber(0);
		turnOnRed(1);
		if(isButtonShortPress(0)){
			manualStatus = RED_GREEN;
			clearRoadLed();
		}
		break;
	default:
		break;
	}
}
void fsm_traffic_tunning_mode(void){
	switch(tuningStatus){
	case OFF:
		// donothing
	case INIT:
		tuningStatus = RED_ADJ;
		clearRoadLed();
		break;
	case RED_ADJ:
		blinkyRed();
		if (isButtonShortPress(2)){
			timeRed++;
			if (timeRed > 99) timeRed = 99;
		}
		else if (isButtonLongPress(2)){
			timeRed--;
			if (timeRed < 0) timeRed = 0;
		}
		else if (isButtonShortPress(1)){
			tuningStatus = AMBER_ADJ;
			clearRoadLed();
		}
		break;
	case AMBER_ADJ:
		blinkyAmber();
		if (isButtonShortPress(2)){
			timeAmber++;
			if (timeAmber > 99) timeAmber = 99;
		}
		else if(isButtonLongPress(2)){
			timeAmber--;
			if (timeAmber < 0) timeAmber = 0;
		}
		else if (isButtonShortPress(1)){
			tuningStatus = GREEN_ADJ;
			clearRoadLed();
		}
		break;
	case GREEN_ADJ:
		blinkyGreen();
		if(isButtonShortPress(2)){
			timeGreen++;
			if (timeGreen >99) timeGreen = 99;
		}
		else if(isButtonLongPress(2)){
			timeGreen--;
			if (timeGreen < 0) timeGreen = 0;
		}
		else if(isButtonShortPress(1)){
			tuningStatus = RED_ADJ;
			clearRoadLed();
		}
		break;
	default:
		break;
	}
}

void fsm_pedestrian(void){
	switch(perdStatus){
	case INIT:

		break;

	default:
		break;
	}
}
void clock_counter_update(void){
	if((timer_flag[0] == 1) && (trafficMode == AUTO_MODE)){
		clock_counter--;
		clock_counter_1--;
		setTimer(timer_duration[0], 0);
	}
}

void logClock(){
	 if (timer_flag[3] == 1 && trafficMode == AUTO_MODE){
			  HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!7SEG WAY1:%d#\r\n",clock_counter),500);
			  HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!7SEG WAY2:%d#\r\n",clock_counter_1),500);
			  setTimer(timer_duration[3], 3);
		  }
}

void logTime(){
	if (timer_flag[3] == 1 && trafficMode == TUNING_MODE){
		if (tuningStatus == RED_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER RED :%d#\r\n",timeRed),500);
		if (tuningStatus == AMBER_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER AMBER :%d#\r\n",timeAmber),500);
		if (tuningStatus == GREEN_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER GREEN :%d#\r\n",timeGreen),500);
		setTimer(timer_duration[3], 3);
	}
}
