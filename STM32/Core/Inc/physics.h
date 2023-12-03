/*
 * physics.h
 *
 *  Created on: Dec 2, 2023
 *      Author: TrongAnh
 */

#ifndef INC_PHYSICS_H_
#define INC_PHYSICS_H_

void turnOffAllLED(void);

void turnOnAllLED(void);

void clearRoadLed(void);

//AUTO MODE:
//turn on the led with index:	0: way 1
//								1: way 2
void autoRed(int index);
void autoAmber(int index);
void AutoGreen(int index);

//TUNING MODE:
//Blink the suitable led
void blinkyRed(void);
void blinkyAmber(void);
void blinkyGreen(void);

/*
 * @brief: set the pedestrian led
 *
 * @param:	0	-	RED
 * 			1	-	AMBER
 * 			2	-	GREEN
 * @retval: None
 */
void setPerdestrianLed(int index);
#endif /* INC_PHYSICS_H_ */
