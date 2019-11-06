/*
 *@File Name : i2c.h
 *@Brief: Header file contains includes for I2C configuration with the TMP102 Temperature
 *        sensor module and function prototypes
 *Created on: Oct 29, 2019
 *Author: Akshita Bhasin & Madhukar Arora
 *
 */

#ifndef TMP102_H_
#define TMP102_H_

#include <stdint.h>

//function prototypes
int8_t get_TemperatureInC(int16_t temp);

#endif /* TMP102_H_ */
