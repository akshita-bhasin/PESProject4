/*
 * state_machine.h
 *
 *  Created on: Nov 1, 2019
 *      Author: ASUS
 */

#include "i2c.h"

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum
{
	Temp_Reading,
	Average_Wait,
	Temp_Alert,
	Disconnected,
	End
} state;

/*typedef enum
{
	Temp_Reading,
	Average_Wait,
	Temp_Alert,
	Disconnected,
	End,
	last_state
} state_table;
*/
typedef enum
{
	Complete,
	Alert,
	Timeout,
	Disconnect
}event;
/*
typedef enum
{
	Complete,
	Alert,
	Timeout,
	Disconnect,
	last_event
} event_table;

typedef state_table(*const arrEventHandler[last_state][last_event])(void);

typedef state_table(*poinEventHandler)(void); */

void temp_reading(void);
void average_temp(void);
void temp_alert(void);
void disconnect_device(void);
void state_machine_1(void);
void Init_SysTick(void);
void SysTick_Handler(void);
void abcd(void);

#endif /* STATE_MACHINE_H_ */
