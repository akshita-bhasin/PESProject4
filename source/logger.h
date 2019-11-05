/*
 * @File  : logger.h
 * @Brief : contains function prototypes and includes for logger implementation
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 11/1/2019
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "fsl_debug_console.h"

typedef enum
{
	Test,
	Debug,
	Status
}log_level;

typedef enum
{
	i2C_Init,
	I2c_read_byte,
	I2c_read_bytes,
	init_SysTick,
	State_machine_1,
	State_machine_2,
	Temp_reading,
	Average_temp,
	Temp_alert,
	Disconnect_device,
	END,
	Turn_on_LED_color
}function_name;

const char* get_func_name(function_name func_name);

const char* get_log_level(log_level logLevel);

void log_string_detail(log_level logLevel, function_name func_name, char * str);

// Log_integer – display an integer
void log_integer(uint8_t num, char type);

// Log_char - display a character
void log_char(char ch);

void log_string(char * str);


#endif /* LOGGER_H_ */
