/*
 * led_control.c
 *
 *  Created on: Nov 4, 2019
 *      Author: ASUS
 */

#include "led_control.h"

void delay_led(uint16_t num)
{
	uint32_t num1 = num*100;
	while(num1!=0)
		num1--;
}

void turn_on_led_color(char color)
{
	LED_RED_INIT(1);
	LED_BLUE_INIT(1);
	LED_GREEN_INIT(1);
	LED_RED_OFF();
	LED_BLUE_OFF();
	LED_GREEN_OFF();

	// for MODULE=FB_DEBUG; blink led, print message via serial terminal
	//	and printing timing cycle delay for the event
	if(color == 'R') {
		LED_BLUE_OFF(); /*!< Turn off target LED_BLUE */
		LED_GREEN_OFF(); /*!< Turn off target LED_GREEN */
		LED_RED_ON(); /*!< Turn on target LED_RED */
		log_string_detail(Debug, Turn_on_LED_color, "LED RED ON");
		delay_led(20000);
	}
	else if(color == 'B') {
    	LED_RED_OFF(); /*!< Turn off target LED_RED */
		LED_GREEN_OFF(); /*!< Turn off target LED_GREEN */
    	LED_BLUE_ON(); /*!< Turn on target LED_BLUE */
		log_string_detail(Debug, Turn_on_LED_color, "LED BLUE ON");
    	delay_led(20000);
	}
	else if(color == 'G') {
		LED_RED_OFF(); /*!< Turn off target LED_RED */
		LED_BLUE_OFF(); /*!< Turn off target LED_BLUE */
		LED_GREEN_ON(); /*!< Turn on target LED_GREEN */
		log_string_detail(Debug, Turn_on_LED_color, "LED GREEN ON");
		delay_led(20000);
	}
}
