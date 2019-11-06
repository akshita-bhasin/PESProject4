/*
 * @File  : main.h
 * @Brief : contains function prototypes and includes for main file implementation
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 11/1/2019
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "state_machine.h"
#include "led_control.h"
#include "logger.h"
#include <stdint.h>
#include <stdlib.h>
#include "i2c.h"

void delay_loop(uint16_t num);

#endif /* MAIN_H_ */
