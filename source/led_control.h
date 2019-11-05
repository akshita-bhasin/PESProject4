/*
 * led_control.h
 *
 *  Created on: Nov 4, 2019
 *      Author: ASUS
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

void turn_on_led_color(char color);

void delay_led(uint16_t num);


#endif /* LED_CONTROL_H_ */
