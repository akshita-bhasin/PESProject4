/* @file test.h
 * @brief Unit test cases headers for PES_Project4
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 10/18/2019
 * @version 1.0
 **/

#ifdef PC_UT
#include "uCUnit/uCUnit.h"
#endif
#include <stdio.h>
#include <stdint.h>

#include "uCUnit.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "logger.h"
#include "i2c.h"
#include "led_control.h"
#include "state_machine.h"



#define LENGTH 16

void unit_test_cases(void);
