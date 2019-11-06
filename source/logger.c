/*
 * @File Name  : logger.c
 * @Brief : contains logger implementation
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 11/1/2019
 */

#include "logger.h"

/* function name : log_string_detail
 * return type : void
 * parameters :logLevel - variable of enum type log_level, funcName - variable of enum type function_name, char *str - points to string
 * @brief : Uses the log level and the status of the function
 *          and prints the details
 */
void log_string_detail(log_level logLevel, function_name funcName, char * str)
{
	char * log = get_log_level(logLevel);
	PRINTF("\r\n%s",log);
	char * func = get_func_name(funcName);
	PRINTF("%s",func);
	PRINTF("%s\r\n", str);
}

/* function name : log_string
 * return type : void
 * parameters : char *str - pointer to a string
 * @brief : prints a debug message to the terminal
 */
void log_string(char * str)
{
	PRINTF("%s\r\n", str);
}

/* function name : log_char
 * return type : void
 * parameters : char ch
 * @brief : prints a single character to the terminal
 */
void log_char(char ch)
{
	PRINTF("%c\n\r", ch);
}

/* function name : log_integer
 * return type : void
 * parameters : uint8_t num - number, char type - number is decimal or hexadecimal
 * @brief : prints a number to the terminal depending on its type
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

/* function name : get_func_name
 * return type : const char*
 * parameters : function_name func_name - func_name is an variable of enum type function_name
 * @brief : returns a string
 */
const char* get_func_name(function_name func_name)
{
	switch(func_name)
	{
#ifdef DEBUG_LOG
		case i2C_Init: return "I2C Init- to initialize I2C: ";
						break;
		case I2c_read_byte: return "I2C_read_byte- reads a single byte of data: ";
							break;
		case I2c_read_bytes: return "I2C_read_bytes- reads two bytes of data and returns a 16 bit value: ";
							break;
		case I2c_write_byte: return "I2C_write_byte- writes a single byte of data: ";
							break;
		case I2c_write_bytes: return "I2C_read_bytes- writes two bytes of data: ";
							break;
		case Get_TemperatureInC: return "get_Temperature in C- takes a 16 bit value and returns temperature in Celsius: ";
							break;
		case State_machine_1: return "state_machine_1- state driven state machine: ";
							break;
		case State_machine_2: return "state_machine_2- table driven state machine: ";
									break;
		case Temp_reading: return "temp_reading- reads temperature from the sensor and prints in Celsius and Farhenheit: ";
							break;
		case Average_temp: return "average_temp";
							break;
		case Temp_alert: return "temp_alert- alerts when temperature goes below 0 degree C: ";
							break;
		case Disconnect_device: return "disconnect_device- stops the program: ";
							break;
		case END: return "END- exit program: ";
							break;
		case Turn_on_LED_color: return "turn_on_LED_Color- turns on chosen color of LED: ";
							break;
#endif

#ifdef NORMAL
		case i2C_Init: return "I2C Init: ";
						break;
		case I2c_read_byte: return "I2C_read_byte: ";
							break;
		case I2c_read_bytes: return "I2C_read_bytes: ";
							break;
		case I2c_write_byte: return "I2C_write_byte: ";
							break;
		case I2c_write_bytes: return "I2C_write_bytes: ";
							break;
		case Get_TemperatureInC: return "get_Temperature in C: ";
							break;
		case State_machine_1: return "state_machine_1: ";
							break;
		case State_machine_2: return "state_machine_2: ";
									break;
		case Temp_reading: return "temp_reading: ";
							break;
		case Average_temp: return "average_wait: ";
							break;
		case Temp_alert: return "temp_alert: ";
							break;
		case Disconnect_device: return "disconnect_device: ";
							break;
		case END: return "END: ";
							break;
		case Turn_on_LED_color: return "turn_on_LED_Color: ";
							break;
#endif
	}
}

/* function name : get_log_level
 * return type : const char*
 * parameters : log_level logLevel- logLevel is a variable of enum type log_level
 * @brief : returns a string
 */
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



