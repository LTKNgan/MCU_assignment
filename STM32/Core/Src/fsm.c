/*
 * fsm.c
 *
 *  Created on: Dec 3, 2023
 *      Author: TrongAnh & KieuNgan
 */

#include "fsm.h"

// init status
int trafficMode = INIT;
int autoStatus = INIT;
int manualStatus = OFF;
int tuningStatus = OFF;
int pedStatus = OFF;
struct buzzer {
	int status;
	int volume;
	int period;
};

struct buzzer Buzzer = {OFF, 0, 0};

//clock for system - F = 1HZ
int clock_counter_main = 0; // clock of traffic way 1
int clock_counter_side = 0; // clock of traffic way 2

//time of each light in auto mode
int timeRed = 5;
int timeAmber = 2;
int timeGreen = 3;


//AUTO MODE
void fsm_traffic_auto_mode(void){
	switch(autoStatus){
	case OFF:
		// do nothing
		break;
	case INIT:
		autoStatus = RED_GREEN;
		// prepare for red green state
		clock_counter_main = timeRed;
		clock_counter_side = timeGreen;
		clearRoadLed();
		break;
	case RED_GREEN:
		turnOnRed(0);
		turnOnGreen(1);
		if (clock_counter_side == 0){
			autoStatus = RED_AMBER;
//			clock_counter_main = timeRed - timeGreen;
			clock_counter_side = timeAmber;
			clearRoadLed();
		}
		break;
	case RED_AMBER:
		turnOnRed(0);
		turnOnAmber(1);
		if (clock_counter_side == 0){
			autoStatus = GREEN_RED;
			clock_counter_main = timeGreen;
			clock_counter_side = timeRed;
			clearRoadLed();
		}
		break;
	case GREEN_RED:
		turnOnGreen(0);
		turnOnRed(1);
		if (clock_counter_main == 0){
			autoStatus = AMBER_RED;
			clock_counter_main = timeAmber;
//			clock_counter_side = timeRed - timeGreen;
			clearRoadLed();
		}
		break;
	case AMBER_RED:
		turnOnAmber(0);
		turnOnRed(1);
		if (clock_counter_main == 0){
			autoStatus = RED_GREEN;
			clock_counter_main = timeRed;
			clock_counter_side = timeGreen;
			clearRoadLed();
		}
		break;
	default:
		break;
	}
}

//PEDESTRIAN (IN AUTO MODE)
void setBuzzer(void){
	switch (Buzzer.status) {
	case INIT:
		setTimer(Buzzer.period, 3);
		Buzzer.status = ON;
		break;
	case OFF:
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		if (timer_flag[3]) {
			setTimer(100, 3);
			Buzzer.status = ON;
		}
		break;
	case ON:
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, Buzzer.volume);
		if (timer_flag[3]) {
		setTimer(Buzzer.period, 3);
		Buzzer.status = OFF;
		}
		break;
	default:
		break;
	}

}

void fsm_pedestrian(void){
	switch(pedStatus){
	case OFF:
		unsetPedestrianLed(0);
		unsetPedestrianLed(1);
		Buzzer.status = OFF;
		setBuzzer();
		break;
	case INIT:
		if (autoStatus == RED_GREEN || autoStatus == RED_AMBER) pedStatus = GREEN_PED;
		else if (autoStatus == GREEN_RED || autoStatus == AMBER_RED) pedStatus = RED_PED;
		Buzzer.status = INIT;
		break;
	case GREEN_PED:
		setPedestrianLed(1);
		if (clock_counter_main <= 3 && clock_counter_main > 0) {
			Buzzer.period = clock_counter_main*100;
			Buzzer.volume = 12000/clock_counter_main;
			setBuzzer();
		}
		if (clock_counter_main <= 0) {
			pedStatus = RED_PED;
			Buzzer.status = OFF;
			setBuzzer();
		}
		break;
	case RED_PED:
		setPedestrianLed(0);
		if (clock_counter_side <= 0) {
			pedStatus = GREEN_PED;
		}
		break;
	default:
		break;
	}
}

//MANUAL MODE
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

//TUNING MODE
void logNewTime(){
	if (tuningStatus == RED_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER RED :%d#\r\n",timeRed),500);
	if (tuningStatus == AMBER_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER AMBER :%d#\r\n",timeAmber),500);
	if (tuningStatus == GREEN_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER GREEN :%d#\r\n",timeGreen),500);
}

void fsm_traffic_tunning_mode(void){
	switch(tuningStatus){
	case OFF:
		// do nothing
	case INIT:
		tuningStatus = RED_ADJ;
		clearRoadLed();
		logNewTime();
		setTimer(timer_duration[1], 1);
		break;
	case RED_ADJ:
		blinkyRed();
		if (isButtonShortPress(2)){
			timeRed++;
			if (timeRed > 99) timeRed = 0;
			logNewTime();
		}
		else if (isButtonLongPress(2)){
			timeRed--;
			if (timeRed < 0) timeRed = 99;
			logNewTime();
		}
		else if (isButtonShortPress(1)){
			tuningStatus = GREEN_ADJ;
			clearRoadLed();
			logNewTime();
		}
		break;
	case GREEN_ADJ:
		blinkyGreen();
		if(isButtonShortPress(2)){
			timeGreen++;
			if (timeGreen > 99) timeGreen = 0;
			logNewTime();
		}
		else if(isButtonLongPress(2)){
			timeGreen--;
			if (timeGreen < 0) timeGreen = 99;
			logNewTime();
		}
		else if(isButtonShortPress(1)){
			tuningStatus = AMBER_ADJ;
			clearRoadLed();
			logNewTime();
		}
		break;
	case AMBER_ADJ:
		blinkyAmber();
		if (isButtonShortPress(2)){
			timeAmber++;
			if (timeAmber > 99) timeAmber = 0;
			logNewTime();
		}
		else if(isButtonLongPress(2)){
			timeAmber--;
			if (timeAmber < 0) timeAmber = 99;
			logNewTime();
		}
		else if (isButtonShortPress(1)){
			tuningStatus = RED_ADJ;
			clearRoadLed();
			logNewTime();
		}
		break;

	default:
		break;
	}
}

void fsm_switch_mode(void){
	if (isButtonLongPress(0)){
		if (trafficMode != MANUAL_MODE) {
			trafficMode = MANUAL_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO MANUAL MODE#\r\n"),500);
			// TODO: prepare for manual mode
			manualStatus = INIT;
			autoStatus= OFF;
			tuningStatus = OFF;
			pedStatus = OFF;
			fsm_pedestrian();
		}
		else {
			trafficMode = INIT;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO AUTO MODE#\r\n"),500);

		}
	}
	else if (isButtonLongPress(1)){
		if (trafficMode != TUNING_MODE) {
			trafficMode = TUNING_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO TUNING MODE#\r\n"),500);
			// TODO: prepare for next mode
			tuningStatus = INIT;
			autoStatus = OFF;
			manualStatus = OFF;
			pedStatus = OFF;
			fsm_pedestrian();
		}
		else {
			trafficMode = INIT;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO AUTO MODE#\r\n"),500);
		}
	}
}

void fsm_traffic(void){
	switch(trafficMode){
	case INIT:
		if (timeRed != (timeAmber + timeGreen)){
			trafficMode = ERROR_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER ERROR#\r\n"),500);
			autoStatus = OFF;
			manualStatus = OFF;
			tuningStatus = OFF;
			pedStatus = OFF;
		}
		else {
			trafficMode = AUTO_MODE;
			autoStatus = INIT;
			manualStatus = OFF;
			tuningStatus = OFF;
			pedStatus = OFF;
			setTimer(timer_duration[0], 0);
		}
		turnOffAllLED();
		break;
	case AUTO_MODE:
		if (isButtonShortPress(3)) {
			if (pedStatus == OFF) {
				pedStatus = INIT;
				setTimer(4*1000*timeRed, 2);
			}
			else pedStatus = OFF;
		}
		if (timer_flag[2] == 1) pedStatus = OFF;
		fsm_pedestrian();
		fsm_traffic_auto_mode();
		break;
	case MANUAL_MODE:
		fsm_traffic_manual_mode();
		break;
	case TUNING_MODE:
		fsm_traffic_tunning_mode();
		break;
	default:
		break;
	}
}

void clock_counter_traffic_update(void){
	if((timer_flag[0] == 1) && (trafficMode == AUTO_MODE)){
		clock_counter_main--;
		clock_counter_side--;
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\n!7SEG WAY1:%d#\r\n",clock_counter_main),500);
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!7SEG WAY2:%d#\r\n",clock_counter_side),500);
		if (pedStatus != OFF) {
			if (pedStatus == GREEN_PED)
				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!PEDESTRIAN: %d#\r\n", clock_counter_main),500);
			else if (pedStatus == RED_PED)
				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!PEDESTRIAN: %d#\r\n", clock_counter_side),500);
		}
		setTimer(timer_duration[0], 0);
	}
}
