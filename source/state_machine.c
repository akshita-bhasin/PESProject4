/*
 * @File Name  : state_machine.c
 * @Brief : contains statemachine implementation
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 11/1/2019
 * Leveraged Code : http://web.archive.org/web/20160517005245/http://www.gedan.net/2008/09/08/finite-state-machine-matrix-style-c-implementation
 */

#include "state_machine.h"

state current_state=Temp_Reading;
event current_event;
uint8_t i;

int16_t temp;
int8_t tempC, tempF;
uint8_t timeout_status=0, timeout_count=1, average=0, flag=0, disconnect_flag;
uint16_t systick_count=0;

/* function name : state_machine_1
 * return type : void
 * parameters :  void
 * @brief : contains implementation of State Oriented state machine
 *          switches between different states of the state machine and
 *          does the appropriate function.
 */
void state_machine_1(void)
{
#ifdef NORMAL
	log_string_detail(Status, State_machine_1, "Inside state machine 1");
#endif
#ifdef DEBUG_LOG
	log_string_detail(Debug, State_machine_1, "Inside state machine 1 - state driven state machine");
#endif
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

/* function name : eval_state
 * return type : void
 * parameters :  void
 * @brief : used to find the next state and the action/function to be executed
 */
void eval_state(void)
{
	stateElement stateEvaluation = stateTab[current_state];
	current_state = stateEvaluation.nextState;
	(*stateEvaluation.actionToDo)();
}

/* function name : state_machine_2
 * return type : void
 * parameters :  void
 * @brief : contains implementation of Table Driven state machine
 */
void state_machine_2()
{
#ifdef NORMAL
	log_string_detail(Status, State_machine_2, "Inside state machine 2");
#endif
#ifdef DEBUG_LOG
	log_string_detail(Debug, State_machine_2, "Inside state machine 2 - table driven state machine");
#endif
	current_event = Complete;
	action actionToDo = temp_reading;
	while(1)
	{
		eval_state();
	}
}

/* function name : temp_reading
 * return type : void
 * parameters :  void
 * @brief : executed if current state is temperature reading
 *          reads the temperature from the TMP102 and determines the next state
 *          based on the events
 */
void temp_reading(void)
{
	log_string("Inside case Temp_Reading");
	turn_on_led_color('G');
	temp = i2c_read_bytes(0x90, 0x00);
	tempC = get_TemperatureInC(temp);
	tempF = (tempC * 1.8) + 32;
 //   disconnect_status = i2c_read_byte(0x90, 0x01);
	if(tempC < 0)
		current_event = Alert;
	else
		current_event = Complete;
	if(disconnect_flag == 1) {
		current_event = Disconnect;
	}
	if(current_event == Complete) {
		current_state = Average_Wait;
	}
	else if(current_event == Disconnect)
		current_state = Disconnected;
	else if(current_event == Alert) {
		current_state = Temp_Alert;
	}
}

/* function name : average_temp
 * return type : void
 * parameters :  void
 * @brief : executed if current state is average/wait
 *          shows the last read temperature from the TMP102
 *          and displays the average value
 *          determines the next state based on the events
 */
void average_temp(void)
{
	if(timeout_status==0) {
#ifdef NORMAL
		log_string_detail(Status, Average_temp, "Waiting for Timeout");
#endif
#ifdef DEBUG_LOG
		log_string_detail(Debug, Average_temp, "Waiting for Timeout for 15 seconds using SysTick Timer");
#endif
		current_event = Timeout;
		timeout_status=1;
	}
//	}
		 //   disconnect_status = i2c_read_byte(0x90, 0x01);
		 //   if(disconnect_status == 0) {
	if(disconnect_flag == 1) {
		current_event = Disconnect;
	}

	if(current_event == Timeout) {
		if(systick_count == 1500) {
			log_string("Inside case Average_Wait");

#ifdef NORMAL
			log_string_detail(Status, Temp_reading, "Temperature in Celsius is: ");
#endif
#ifdef DEBUG_LOG
			log_string_detail(Debug, Temp_reading, "Temperature in Celsius from temperature register is: ");
#endif
			log_integer(tempC, 'd');
			log_string("C");
#ifdef NORMAL
			log_string_detail(Status, Temp_reading, "Temperature in Farhenheit is: ");
#endif
#ifdef DEBUG_LOG
			log_string_detail(Debug, Temp_reading, "Temperature in Farhenheit from temperature register is: ");
#endif
			log_integer(tempF, 'd');
			log_string("F");
			systick_count=0;
			turn_on_led_color('G');
			if(timeout_count == 1)
				average = tempC;
			average = (average + tempC)/2;
			log_string("Average Temperature: ");
			log_integer(average, 'd');
			log_string("C");
			current_state = Temp_Reading;
			timeout_status=0;
			timeout_count++;

			if(timeout_count>4){
				timeout_count=1;
				if(flag==0) {
					current_state = Temp_Reading;
					flag=1;
					average=0;
					state_machine_2();
				}
				else {
					current_state = Temp_Reading;
					flag=0;
					average=0;
					state_machine_1();
				}
			}
		}
	}
	else if(current_event == Disconnect) {
		current_state = Disconnected;
	}
}

/* function name : temp_alert
 * return type : void
 * parameters :  void
 * @brief : executed if current state is Temp Alert
 *          determines the next state of the statemachine
 *          based on the current event
 */
void temp_alert(void)
{
	log_string("Inside case Temp_Alert");
	turn_on_led_color('B');
	log_string("");
#ifdef NORMAL
		log_string_detail(Status, Temp_Alert, "Temperature below 0 degree Celsius");
#endif
#ifdef DEBUG_LOG
		log_string_detail(Debug, Temp_Alert, "Temperature is below 0 degree Celsius");
#endif
	current_event = Complete;
 //   disconnect_status = i2c_read_byte(0x90, 0x01);
 //   if(disconnect_status == 0) {
    if(disconnect_flag == 1) {
    	current_event = Disconnect;
    }
	if(current_event == Complete) {
		current_state = Average_Wait;
	}
	else if(current_event == Disconnect) {
		current_state = Disconnected;
	}
}

/* function name : disconnect_device
 * return type : void
 * parameters :  void
 * @brief : executed if current state is Disconnected
 *          and changes the state to End
 */
void disconnect_device(void)
{
	log_string("Inside case Disconnected");
	turn_on_led_color('R');
 //   disconnect_status = i2c_read_byte(0x90, 0x01);
#ifdef NORMAL
		log_string_detail(Status, Disconnect_device, "Device disconnected");
#endif
#ifdef DEBUG_LOG
		log_string_detail(Debug, Disconnect_device, "Device disconnected due to either a loose connection\r\nor being stuck in wait");
#endif
	current_state = End;
	return;
}

/* function name : end
 * return type : void
 * parameters :  void
 * @brief : executed if current state is End
 *          and causes exit from state machine 1 / state machine 2
 */
void end(void)
{
	log_string("Inside case End");
	exit(0);
}

/* function name : SysTick_Handler
 * return type : void
 * parameters :  void
 * @brief : generates required time delay
 * leverage : //https://community.nxp.com/thread/418592
 */
void SysTick_Handler(void) {
	systick_count++;
//	PRINTF("\r\nSysTick: %d\r\n", systick_count);
}


