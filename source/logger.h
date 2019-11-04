/*
 * @file logger.h
 * @brief contains function prototypes and header files for logger.c
 * @author Akshita Bhasin and Madhukar Arora
 * @date 10/15/2019
 * @version 1.0
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
	I2C_Init,
	i2c_read_byte,
	i2c_read_bytes,
	Init_SysTick,
	state_machine_1,
	temp_reading,
	average_temp,
	temp_alert,
	disconnect_device
}function_name;

const char* get_func_name(function_name func_name);

const char* get_log_level(log_level logLevel);

void log_string_detail(log_level logLevel, function_name funcName, char * str);

// Log_integer – display an integer
void log_integer(uint32_t * dispInt, size_t length);

// Log_char - display a character
void log_char(char ch);

void log_string(char * str);


#endif /* LOGGER_H_ */
