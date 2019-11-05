/*
 *@File Name : led_control.h
 *@Brief: Header file contains includes for controlling the RGB LED
 *        on the FRDM KL25Z Board and function prototypes
 *Created on: Oct 29, 2019
 *Author: Akshita Bhasin & Madhukar Arora
 */

#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "logger.h"

//function prototypes
void turn_on_led_color(char color);
void delay_led(uint16_t num);


#endif /* LED_CONTROL_H_ */
