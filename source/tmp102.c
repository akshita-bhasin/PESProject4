/*
 *@File Name : i2c.c
 *@Brief: Source file contains I2C configuration with the TMP102 Temperature sensor module
 *Created on: Oct 29, 2019
 *Author: Akshita Bhasin & Madhukar Arora
 */

#include "tmp102.h"

#define RESOLUTION 	0.0625

/*
 * function name : get_TemperatureInC
 * parameter : int16_t temp
 * return type : int8_t
 * @brief : returns the temperature value in Celsius
 */
int8_t get_TemperatureInC(int16_t temp)
{
	int8_t tempC;
	if(temp> 0x7FFF)
		temp |= 0xF000; // negative for 12-bit temperature register
	tempC = temp * RESOLUTION;

	return tempC;
}
