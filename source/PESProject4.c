/*
 * @File Name   : PesProject4.c
 * @Brief  : Application Entry Point
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 10/25/2019
 * leveraged code : http://web.archive.org/web/20160517005245/http://www.gedan.net/2008/09/08/finite-state-machine-matrix-style-c-implementation
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "i2c.h"
#include "state_machine.h"
#include "logger.h"
#include <stdint.h>
/*
 * @brief   Application entry point.
 */

uint8_t post_status, post_flag, tempinC, alert_status_tl0, alert_status_th0;

void delay_loop(uint16_t num)
{
	for(uint8_t i=num; i>0; i--);
}

int main(void)
{

//	uint8_t tempC, tempF;
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    I2C_Init();
    post_status = i2c_read_byte(0x90, 0x01);
    if(post_status == 96 || post_status == 98) {
    	log_string_detail(Status, I2c_read_byte, "POST tests successful");
 //   	PRINTF("POST tests successful\r\n");
    	post_flag = 1;
    }
    else {
    	log_string_detail(Status, I2c_read_byte, "POST tests failed");
  //  	PRINTF("POST tests failed\r\n");
    	post_flag=0;
    }

    I2C_write_byte(0x01, 0x60);
    delay_loop(10000);
    uint8_t data = i2c_read_byte(0x90, 0x01);
    log_string_detail(Debug, I2c_read_byte, "Written data: ");
    log_integer(data, 'H');
    log_string("Post data read is: ");
    log_integer(post_status, 'd');
//    PRINTF("\r\nPost data read is: %d\r\n", post_status);
    I2C_write_bytes(0x01, 0x60, 0xA0);
    delay_loop(20000);
    uint8_t data1 = i2c_read_byte(0x90, 0x01);
    log_string_detail(Debug, I2c_read_byte, "First byte of data");
    log_integer(data1, 'H');
	Init_SysTick();

	tempinC = i2c_read_bytes(0x90, 0x00);
	PRINTF("\r\nTemperagture in Celsius: %d\r\n", tempinC);
	uint8_t init_tl0 = i2c_read_byte(0x90, 0x02);
	PRINTF("TL0: %d\r\n", init_tl0);

	delay_loop(10000);

	uint8_t init_th0 = i2c_read_byte(0x90, 0x03);
	PRINTF("TH0: %d\r\n", init_th0);

	delay_loop(10000);

	alert_init();

	delay_loop(10000);
	alert_status_tl0 = i2c_read_byte(0x90, 0x02);
	PRINTF("Alert: %d\r\n", alert_status_tl0);
	delay_loop(10000);
	alert_status_th0 = i2c_read_byte(0x90, 0x03);
	PRINTF("Alert: %d\r\n", alert_status_th0);
    state_machine_1();
   return 0 ;
}
