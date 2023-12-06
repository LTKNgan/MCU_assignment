/*
 * fsm.h
 *
 *  Created on: Dec 3, 2023
 *      Author: TrongAnh
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "global.h"
#include <stdio.h>

void fsm_switch_mode(void);
void fsm_traffic(void);
void clock_counter_traffic_update(void);

#endif /* INC_FSM_H_ */
