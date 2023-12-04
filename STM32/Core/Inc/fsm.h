/*
 * fsm.h
 *
 *  Created on: Dec 3, 2023
 *      Author: TrongAnh
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "global.h"
#include "button.h"
#include "software_timer.h"
#include "physics.h"
#include <stdio.h>





void fsm_traffic(void);
void clock_counter_update(void);
void fsm_traffic_auto_mode(void);
void fsm_traffic_manual_mode(void);
void fsm_traffic_tunning_mode(void);
void logClock();
void logTime();
#endif /* INC_FSM_H_ */
