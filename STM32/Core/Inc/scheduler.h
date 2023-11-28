/*
 * scheduler.h
 *
 *  Created on: Nov 28, 2023
 *      Author: DELL
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#define SCH_MAX_TASK	10
#define NO_TASK_ID 		0

#include "global.h"

void SCH_Init(void);
void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint32_t taskID);


#endif /* INC_SCHEDULER_H_ */
