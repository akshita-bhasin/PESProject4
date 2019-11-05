/*
 * @file  : logger.c
 * @brief : contains logger implementation
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 10/15/2019
 * @version 1.0
 */

#include "logger.h"
const char* get_func_name(function_name func_name);
const char* get_log_level(log_level logLevel);

void log_string_detail(log_level logLevel, function_name funcName, char * str)
{
	char * log = get_log_level(logLevel);
	PRINTF("\r\n%s",log);
	char * func = get_func_name(funcName);
	PRINTF("%s",func);
	PRINTF("%s\r\n", str);
}


void log_string(char * str)
{
	PRINTF("\r\n%s\r\n", str);
}
/* function name : log_data
 * return type : void
 * parameters : uint8_t* seqAddr (address), size_t length(number of bytes)
 * @brief : logs the data at a memory location
 */
/*void log_data(uint8_t * seqAddr, size_t length)
{
	if(logger_status==1){
	#ifdef KL25Z_LOG
		PRINTF("Contents at memory location 0X%x: \n\r",seqAddr);
	#endif
	#ifdef PC_LOG
		printf("Contents at memory location 0X%x: \n\r",seqAddr);
	#endif
		for(uint8_t i=0;i<length;i++){
		#ifdef KL25Z_LOG
			PRINTF("0x%x ",*(seqAddr+i));
		#endif
		#ifdef PC_LOG
			printf("0x%x ",*(seqAddr+i));
		#endif
		}
	#ifdef KL25Z_LOG
		PRINTF("\n\r");
	#endif
	#ifdef PC_LOG
		printf("\n\r");
	#endif
	}
} */

/* function name : log_char
 * return type : void
 * parameters : char *dispStr
 * @brief : if logger enabled, logger logs a string
 */
void log_char(char ch)
{
	PRINTF("%c\n\r", ch);
}

/* function name : log_integer
 * return type : void
 * parameters : uint32_t * dispInt(address), size_t length(number of bytes)
 * @brief : if logger enabled, logger logs the values at an address
 */
void log_integer(uint8_t num, char type)
{
	if(type == 'd')
		PRINTF("%d", num);
	else if((type == 'h') | (type=='H'))
		PRINTF("0x%X", num);
	else
		PRINTF("%d", num);
}

const char* get_func_name(function_name func_name)
{
	switch(func_name)
	{
		case i2C_Init: return "I2C Init- to initialize I2C: ";
						break;
		case I2c_read_byte: return "I2C_read_byte- reads a single byte of data: ";
							break;
		case I2c_read_bytes: return "I2C_read_bytes- reads two bytes of data and gives out temperature in Celsius: ";
							break;
		case init_SysTick: return "Init_SysTick- Initialize SysTick Timer to run for 1 second: ";
							break;
		case State_machine_1: return "state_machine_1- state driven state machine: ";
							break;
		case State_machine_2: return "state_machine_2- table driven state machine: ";
									break;
		case Temp_reading: return "temp_reading- reads temperature from the sensor and prints in Celsius and Farhenheit: ";
							break;
		case Average_temp: return "I2C Init";
							break;
		case Temp_alert: return "temp_alert- alerts when temperature goes below Tlow or goes above Thigh: ";
							break;
		case Disconnect_device: return "disconnect_device- stops the program: ";
							break;
		case END: return "END- exit program: ";
							break;
		case Turn_on_LED_color: return "turn_on_LED_Color- turns on chosen color of LED: ";
							break;
	}
}

const char* get_log_level(log_level logLevel)
{
	switch(logLevel)
	{
		case Test: return "Test: ";
					break;
		case Status: return "Status: ";
					break;
		case Debug: return "Debug: ";
					break;
	}
}



