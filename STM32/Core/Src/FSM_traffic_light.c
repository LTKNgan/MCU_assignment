/*
 * FMS_traffic_light.c
 *
 *  Created on: Nov 2, 2023
 *      Author: DELL
 */

#include "FSM_traffic_light.h"

int counter;

void allLEDoff() {
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|GREEN_LED1_Pin|AMBER_LED1_Pin
							|RED_LED2_Pin|GREEN_LED2_Pin|AMBER_LED2_Pin, 1);
}

void trafficLightRun() {
    switch (traffic_status) {
        case INIT:
        	allLEDoff();
            traffic_status = RED1_GREEN2;
            counter = timeGreen;
            setTimer1(1000);
            break;
        case RED1_GREEN2:
        	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | GREEN_LED2_Pin, 0);
            segment_buffer[0] = (counter + timeAmber)/10;
            segment_buffer[1] = (counter + timeAmber)%10;
            segment_buffer[2] = counter/10;
            segment_buffer[3] = counter%10;
            if (timer1_flag) {
                setTimer1(1000);
                counter--;
                if (counter <= 0) {
                    traffic_status = RED1_AMBER2;
                    counter = timeAmber;
                    allLEDoff();
                }
            }
            break;
        case RED1_AMBER2:
        	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | AMBER_LED2_Pin, 0);

        	segment_buffer[0] = counter/10;
        	segment_buffer[1] = counter%10;
        	segment_buffer[2] = counter/10;
        	segment_buffer[3] = counter%10;

            if (timer1_flag) {
                setTimer1(1000);
                counter--;
                if (counter <= 0) {
                    traffic_status = GREEN1_RED2;
                    counter = timeGreen;
                    allLEDoff();

                }
            }
            break;
        case GREEN1_RED2:
        	HAL_GPIO_WritePin(GPIOA, GREEN_LED1_Pin | RED_LED2_Pin, 0);
            segment_buffer[0] = counter/10;
            segment_buffer[1] = counter%10;
            segment_buffer[2] = (counter + timeAmber)/10;
            segment_buffer[3] = (counter + timeAmber)%10;
            if (timer1_flag) {
                setTimer1(1000);
                counter--;
                if (counter <= 0) {
                    traffic_status = AMBER1_RED2;
                    counter = timeAmber;
                    allLEDoff();
                }
            }
            break;
        case AMBER1_RED2:
        	HAL_GPIO_WritePin(GPIOA, AMBER_LED1_Pin | RED_LED2_Pin, 0);
			segment_buffer[0] = counter/10;
			segment_buffer[1] = counter%10;
			segment_buffer[2] = counter/10;
			segment_buffer[3] = counter%10;
			if (timer1_flag) {
				setTimer1(1000);
				counter--;
				if (counter <= 0) {
					traffic_status = RED1_GREEN2;
					counter = timeGreen;
					allLEDoff();
				}
			}
			break;
        default:
            break;
    }
}

void led_blinky(int led) {
	switch (blinky_status) {
	case INIT:
		allLEDoff();
		if (led == RED) blinky_status = RED;
		else if (led == GREEN) blinky_status = GREEN;
		else if (led == AMBER) blinky_status = AMBER;
		setTimer1(250);
		break;
	case RED:
		if (timer1_flag) {
			setTimer1(250);
			HAL_GPIO_TogglePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin);
		}
		break;
	case GREEN:
		if (timer1_flag) {
			setTimer1(250);
			HAL_GPIO_TogglePin(GPIOA, GREEN_LED1_Pin | GREEN_LED2_Pin);
		}
		break;
	case AMBER:
		if (timer1_flag) {
			setTimer1(250);
			HAL_GPIO_TogglePin(GPIOA, AMBER_LED1_Pin | AMBER_LED2_Pin);
		}
		break;
	default:
		break;
	}
}
