/*
 * @File Name : state_machine.h
 * @Brief : contains includes, enum declarations and function prototypes for
 *          statemachine implementation
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On: 11/1/2019
 */

#include "i2c.h"
#include "tmp102.h"
#include "led_control.h"
#include "logger.h"

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

//enum of states
typedef enum
{
	Temp_Reading,
	Average_Wait,
	Temp_Alert,
	Disconnected,
	End
} state;

//enum of events
typedef enum
{
	Complete,
	Alert,
	Timeout,
	Disconnect,
	Exit
}event;

//function prototypes
typedef void(*action)(void);

typedef struct
{
	state nextState;
	action actionToDo;
}stateElement;

void temp_reading(void);
void average_temp(void);
void temp_alert(void);
void disconnect_device(void);
void end(void);
void state_machine_1(void);
void Init_SysTick(void);
void SysTick_Handler(void);
void abcd(void);
void eval_state(void);
void state_machine_2();

#endif /* STATE_MACHINE_H_ */
