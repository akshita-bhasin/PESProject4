/*
 * state_machine.c
 *
 *  Created on: Nov 1, 2019
 *      Author: ASUS
 *
 *      leveraged code : http://web.archive.org/web/20160517005245/http://www.gedan.net/2008/09/08/finite-state-machine-matrix-style-c-implementation
 *
 */

#include "state_machine.h"

state current_state=Temp_Reading;
event current_event;
uint8_t i=0;

uint8_t tempC, tempF, disconnect_status, systick_count=0, timeout_count=1, average=0, flag=0;

void temp_reading(void);
void average_temp(void);
void temp_alert(void);
void disconnect_device(void);
void Init_SysTick(void);
void SysTick_Handler(void);

void state_machine_1(void)
{
	log_string_detail(Status, State_machine_1, "Inside state machine 1");
	while(1)
	{
		//current_event = ReadEvent();
		switch(current_state)
		{
			case Temp_Reading: {
				temp_reading();
				break;
			}
			case Average_Wait: {
				average_temp();
				break;
			}
			case Temp_Alert: {
				temp_alert();
				break;
			}
			case Disconnected: {
				disconnect_device();
				break;
			}
			case End: {
				end();
				break;
			}
		}
	}
}

stateElement stateTab[5] = {
		{Temp_Reading, temp_reading},
		{Average_Wait,average_temp},
		{Temp_Alert,temp_alert},
		{Disconnected,disconnect_device},
		{End, end}
};

void eval_state(void)
{
	stateElement stateEvaluation = stateTab[current_state];
	current_state = stateEvaluation.nextState;
	(*stateEvaluation.actionToDo)();
}


void state_machine_2()
{
	log_string_detail(Status, State_machine_2, "Inside state machine 2");
	current_event = Complete;
	action actionToDo = temp_reading;
	while(1)
	{
		eval_state();
	}
}

void temp_reading(void)
{
	log_string("Inside case Temp_Reading");
	turn_on_led_color('G');
	 //   post_status = i2c_read_bytes(0x90, 0x00);
	 //   printf("Post Status Success(0)/Failed(1): %d", post_status);
	tempC = i2c_read_bytes(0x90, 0x00);
	log_string_detail(Debug, Temp_reading, "Temperature in Celsius is: ");
	log_integer(tempC, 'd');
	log_string("");
	tempF = (tempC * 1.8) + 32;
	log_string_detail(Debug, Temp_reading, "Temperature in Farhenheit is: ");
	log_integer(tempF, 'd');
	log_string("");
    disconnect_status = i2c_read_byte(0x90, 0x01);
    if(disconnect_status == 0) {
    	current_event = Disconnect;
    }
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
		timeout_count=0;
		if(flag==0) {
			current_state = Temp_Reading;
			flag=1;
			state_machine_2();
		}
		else {
			current_state = Temp_Reading;
			flag=0;
			state_machine_1();
		}
	}
	else {
		current_event = Timeout;
	}
	if(current_event == Timeout) {
		if(systick_count == 1) {
			log_string("Inside case Average_Wait");
			systick_count=0;
//					current_event = Timeout;
			turn_on_led_color('G');
			if(timeout_count == 1)
				average = tempC;
			average = (average + tempC)/2;
			log_string("Average Temperature: ");
			log_integer(average, 'd');
			log_string("");
			current_state = Temp_Reading;
			timeout_count++;
		}
	}
	else if(current_event == Disconnect) {
		current_state = Disconnected;
	}
    disconnect_status = i2c_read_byte(0x90, 0x01);
    if(disconnect_status == 0) {
    	current_event = Disconnect;
    }

}

void temp_alert(void)
{
	log_string("Inside case Temp_Alert");
	turn_on_led_color('B');
	PRINTF("\r\nTemperature is below 25 degree Celsius\r\n");
	current_event = Complete;
    disconnect_status = i2c_read_byte(0x90, 0x01);
    if(disconnect_status == 0) {
    	current_event = Disconnect;
    }
	if(current_event == Complete) {
		current_state = Average_Wait;
	}
	else if(current_event == Disconnect) {
		current_state = Disconnected;
	}
}

void disconnect_device(void)
{
	log_string("Inside case Disconnected");
	turn_on_led_color('R');
 //   disconnect_status = i2c_read_byte(0x90, 0x01);
	log_string_detail(Debug, Disconnect_device, "Device disconnected");
	current_state = End;
	return;
}

void end(void)
{
	log_string("Inside case End");
	exit(1);
}

void Init_SysTick(void) {
	SysTick->LOAD = (48000000L/8);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL=0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}


//https://community.nxp.com/thread/418592
void SysTick_Handler(void) {
	systick_count++;
	PRINTF("\r\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Timeout worked\r\n");
}


