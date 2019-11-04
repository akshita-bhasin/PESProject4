/*
 * statemachine2.h
 *
 *  Created on: Nov 4, 2019
 *      Author: madhu
 */

#ifndef STATEMACHINE2_H_
#define STATEMACHINE2_H_

#include "i2c.h"

typedef enum {
	Temp_Reading,
	Average_Wait,
	Temp_Alert,
	Disconnected
//	End
}state;


typedef enum{
	Complete,
	Alert,
	Timeout,
	Disconnect
}event;

typedef void(*action)(void);

void temp_reading(void);
void average_temp(void);
void temp_alert(void);
void disconnect_device(void);
void Init_SysTick(void);
void SysTick_Handler(void);
void eval_state(void);
void statemachine2();

typedef struct
{
	state nextState;
	action actionToDo;
}stateElement;
/*
stateElement stateTab[4] = {
		{Temp_Reading, temp_reading},
		{Average_Wait,average_temp},
		{Temp_Alert,temp_alert},
		{Disconnected,disconnect_device}
};
*/


#endif /* STATEMACHINE2_H_ */
