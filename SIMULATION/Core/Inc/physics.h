/*
 * physics.h
 *
 *  Created on: Dec 7, 2023
 *      Author: DELL
 */

#ifndef INC_PHYSICS_H_
#define INC_PHYSICS_H_

#include "global.h"

void turnOffAllLED(void);

void turnOnAllLED(void);

void clearRoadLed(void);

//AUTO / MANUAL MODE:
//turn on the led with index:	0: way 1
//								1: way 2
void turnOnRed(int index);
void turnOnAmber(int index);
void turnOnGreen(int index);

//TUNING MODE:
//Blink the suitable led
void blinkyRed(void);
void blinkyAmber(void);
void blinkyGreen(void);

/*
 * @brief: set the pedestrian led
 *
 * @param:	0	-	RED
 * 			1	-	GREEN
 * @retval: None
 */
void setPedestrianLed(int index);
void unsetPedestrianLed(int index);
#endif /* INC_PHYSICS_H_ */
