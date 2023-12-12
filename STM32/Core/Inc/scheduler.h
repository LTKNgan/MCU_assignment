/*
 * scheduler.h
 *
 *  Created on: Nov 28, 2023
 *      Author: KNgan
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"

void SCH_Init(void);
void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);


#endif /* INC_SCHEDULER_H_ */
