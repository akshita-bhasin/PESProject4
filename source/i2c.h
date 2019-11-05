/*
 *@File Name : i2c.h
 *@Brief: Header file contains includes for I2C configuration with the TMP102 Temperature
 *        sensor module and function prototypes
 *Created on: Oct 29, 2019
 *Author: Akshita Bhasin & Madhukar Arora
 */
#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

//function prototypes
void I2C_Init(void);
uint8_t i2c_read_byte(uint8_t dev, uint8_t reg);
void I2C_write_byte(uint8_t reg, uint8_t data);
void I2C_write_bytes(uint8_t reg, uint8_t data1, uint8_t data2);
uint8_t i2c_read_bytes(uint8_t dev, uint8_t reg);
void alert_init(void);

#endif /* I2C_H_ */
