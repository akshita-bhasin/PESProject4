/*
 * i2c.h
 *
 *  Created on: Oct 29, 2019
 *      Author: ASUS
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

void I2C_Init(void);
uint8_t i2c_read_byte(uint8_t dev, uint8_t reg);
void I2C_write_byte(uint8_t reg, uint8_t data);
void I2C_write_bytes(uint8_t reg, uint8_t data1, uint8_t data2);
uint8_t i2c_read_bytes(uint8_t dev, uint8_t reg);
void alert_init(void);
//void Init_SysTick(void);
//void SysTick_Handler(void);

#endif /* I2C_H_ */
