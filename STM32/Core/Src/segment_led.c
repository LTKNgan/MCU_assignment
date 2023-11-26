/*
 * segment_led.c
 *
 *  Created on: Nov 2, 2023
 *      Author: DELL
 */

#include "segment_led.h"

enum {SEG0=1, SEG1, SEG2, SEG3};
int segment_status = INIT;
int time_segment = 10;

void displayNum(int num) {
	switch (num)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_c_Pin|SM_d_Pin
		                        |SM_e_Pin|SM_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SM_g_GPIO_Port, SM_g_Pin, GPIO_PIN_SET);
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_d_Pin
		                        |SM_e_Pin|SM_f_Pin|SM_g_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SM_b_Pin|SM_c_Pin, GPIO_PIN_RESET);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_d_Pin
		                        |SM_e_Pin|SM_g_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_c_Pin|SM_f_Pin, GPIO_PIN_SET);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_c_Pin
								|SM_d_Pin|SM_g_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_e_Pin|SM_f_Pin, GPIO_PIN_SET);
		break;

	case 4:
		HAL_GPIO_WritePin(GPIOB, SM_b_Pin|SM_c_Pin
		                        |SM_f_Pin|SM_g_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_d_Pin|SM_e_Pin, GPIO_PIN_SET);
		break;

	case 5:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_c_Pin|SM_d_Pin
		                        |SM_f_Pin|SM_g_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_b_Pin|SM_e_Pin, GPIO_PIN_SET);
		break;

	case 6:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_c_Pin|SM_d_Pin
		                        |SM_e_Pin|SM_f_Pin|SM_g_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_b_Pin, GPIO_PIN_SET);
		break;

	case 7:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_d_Pin|SM_e_Pin|SM_f_Pin|SM_g_Pin, GPIO_PIN_SET);
		break;

	case 8:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_c_Pin|SM_d_Pin
		                        |SM_e_Pin|SM_f_Pin|SM_g_Pin, GPIO_PIN_RESET);
		break;

	case 9:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_c_Pin
								|SM_d_Pin|SM_f_Pin|SM_g_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SM_e_Pin, GPIO_PIN_SET);
		break;

	default:
		HAL_GPIO_WritePin(GPIOB, SM_a_Pin|SM_b_Pin|SM_c_Pin|SM_d_Pin
		                        |SM_e_Pin|SM_f_Pin|SM_g_Pin, GPIO_PIN_SET);
		break;
	}
}

void displaySegment() {
	switch (segment_status) {
	case INIT:
		segment_status = SEG0;
		setTimer2(time_segment);
		break;
	case SEG0:
		// enable led 0 and disable led 1, 2, 3
		HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, 0);
		displayNum(segment_buffer[0]);
		if (timer2_flag) {
			setTimer2(time_segment);
			segment_status = SEG1;
		}
		break;
	case SEG1:
		// enable led 1 and disable led 0, 2, 3
		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0);
		displayNum(segment_buffer[1]);
		if (timer2_flag) {
			setTimer2(time_segment);
			segment_status = SEG2;
		}
		break;
	case SEG2:
		// enable led 2 and disable led 0, 1, 3
		HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN0_Pin | EN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0);
		displayNum(segment_buffer[2]);
		if (timer2_flag) {
			setTimer2(time_segment);
			segment_status = SEG3;
		}
		break;
	case SEG3:
		// enable led 3 and disable led 0, 1, 2
		HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN0_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, 0);
		displayNum(segment_buffer[3]);
		if (timer2_flag) {
			setTimer2(time_segment);
			segment_status = SEG0;
		}
		break;
	default:
		break;
	}
}
