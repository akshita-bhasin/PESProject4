/*
 * statemachine2.c
 *
 *  Created on: Nov 4, 2019
 *      Author: madhu
 *      leveraged code : http://web.archive.org/web/20160517005245/http://www.gedan.net/2008/09/08/finite-state-machine-matrix-style-c-implementation
 */
#include"statemachine2.h"

extern uint8_t delay;
extern uint8_t delay_end;

state current_state = Temp_Reading;
event current_event;
uint8_t tempC, tempF, timeout_count=1, average=0;


stateElement stateTab[4] = {
		{Temp_Reading, temp_reading},
		{Average_Wait,average_temp},
		{Temp_Alert,temp_alert},
		{Disconnected,disconnect_device}
};

void eval_state(void)
{
	stateElement stateEvaluation = stateTab[current_state];
	current_state = stateEvaluation.nextState;
	(*stateEvaluation.actionToDo)();
}


void statemachine2()
{
	current_event = Complete;
	action actionToDo = temp_reading;
	while(1)
	{
		eval_state();
	}
}

void temp_reading(void)
{
	 //   post_status = i2c_read_bytes(0x90, 0x00);
	 //   printf("Post Status Success(0)/Failed(1): %d", post_status);
	tempC = i2c_read_bytes(0x90, 0x00);
	PRINTF("\r\nTemperature in Celsius is: \r\n");
	PRINTF("%dC",tempC);
	PRINTF("\r\nTemperature in Farhenheit is: \r\n");
	tempF = (tempC * 1.8) + 32;
	PRINTF("%dF",tempF);
	if(tempC < 27)
		current_event = Alert;
	else
		current_event = Complete;
	if(current_event == Complete) {
		current_state = Average_Wait;
	}
	else if(current_event == Disconnect)
		current_state = Disconnected;
	else if(current_event == Alert) {
		current_state = Temp_Alert;
	}
}


void average_temp(void)
{
	if(timeout_count>=4){
		//state_machine_1();
		exit(1);
	}
	else
		current_event = Timeout;
	if(timeout_count == 1)
		average = tempC;
	average = (average + tempC)/2;
	PRINTF("\r\nAverage Temperature: \r\n");
	PRINTF("%d",average);
	if(current_event == Timeout) {
		Init_SysTick();
		SysTick_Handler();
//					current_event = Timeout;
		current_state = Temp_Reading;
		timeout_count++;
	}
	else if(current_event == Disconnect) {
		current_state = Disconnected;
	}
}

void temp_alert(void)
{
	PRINTF("\r\nTemperature is below 25 degree Celsius\r\n");
	current_event = Complete;
	if(current_event == Complete) {
		current_state = Average_Wait;
	}
	else if(current_event == Disconnect) {
		current_state = Disconnected;
	}
}

void disconnect_device(void)
{
	PRINTF("Device disconnected\r\n");
	exit(1);
}

void Init_SysTick(void) {
	SysTick->LOAD = (48000000L/16);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL=0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}


//https://community.nxp.com/thread/418592
void SysTick_Handler(void) {
	if(delay) {
		delay--;
		if(delay==0)
			delay_end = 1;
	}
}




