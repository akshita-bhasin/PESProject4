/*
 *@File Name : led_control.c
 *@Brief: Source file contains code for controlling the RGB LED
 *        on the FRDM KL25Z Board
 *Created on: Oct 29, 2019
 *Author: Akshita Bhasin & Madhukar Arora
 */

#include "led_control.h"

/*
 * function name : delay_led
 * parameter : uint16_t num - number used to generate a simple delay
 * return type : void
 * @brief : generates a simple delay by decrementing a number
 */
void delay_led(uint16_t num)
{
	uint32_t num1 = num*100;
	while(num1!=0)
		num1--;
}

/*
 * function name : turn_on_led_color
 * parameter : char color - code for which LED to glow
 * return type : void
 * @brief : turns on a single LED depending on the parameter, 'R'- Red 'B'-Blue G - 'Green'
 */
void turn_on_led_color(char color)
{
	LED_RED_INIT(1);
	LED_BLUE_INIT(1);
	LED_GREEN_INIT(1);
	LED_RED_OFF();
	LED_BLUE_OFF();
	LED_GREEN_OFF();

	if(color == 'R') {
		LED_BLUE_OFF(); /*!< Turn off target LED_BLUE */
		LED_GREEN_OFF(); /*!< Turn off target LED_GREEN */
		LED_RED_ON(); /*!< Turn on target LED_RED */
#ifdef NORMAL
		log_string_detail(Status, Turn_on_LED_color, "");
#endif
#ifdef DEBUG_LOG
		log_string_detail(Debug, Turn_on_LED_color, "LED RED ON");
#endif
#ifdef TEST
		log_string_detail(Test, Turn_on_LED_color, "LED RED in Test Mode");
#endif
		delay_led(20000);
	}
	else if(color == 'B') {
    	LED_RED_OFF(); /*!< Turn off target LED_RED */
		LED_GREEN_OFF(); /*!< Turn off target LED_GREEN */
    	LED_BLUE_ON(); /*!< Turn on target LED_BLUE */
#ifdef NORMAL
		log_string_detail(Status, Turn_on_LED_color, "");
#endif
#ifdef DEBUG_LOG
		log_string_detail(Debug, Turn_on_LED_color, "LED BLUE ON");
#endif
#ifdef TEST
		log_string_detail(Test, Turn_on_LED_color, "LED BLUE in Test Mode");
#endif
    	delay_led(20000);
	}
	else if(color == 'G') {
		LED_RED_OFF(); /*!< Turn off target LED_RED */
		LED_BLUE_OFF(); /*!< Turn off target LED_BLUE */
		LED_GREEN_ON(); /*!< Turn on target LED_GREEN */
#ifdef NORMAL
		log_string_detail(Status, Turn_on_LED_color, "");
#endif
#ifdef DEBUG_LOG
		log_string_detail(Debug, Turn_on_LED_color, "LED GREEN ON");
#endif
#ifdef TEST
		log_string_detail(Test, Turn_on_LED_color, "LED GREEN in Test Mode");
#endif
		delay_led(20000);
	}
}
