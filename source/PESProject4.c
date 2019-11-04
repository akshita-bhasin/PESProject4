/**
 * @file    PESProject4.c
 * @brief   Application entry point.
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
#include <stdint.h>
/*
 * @brief   Application entry point.
 */

uint8_t post_status, post_flag, delay_end, delay;

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
    if(post_status == 96) {
    	PRINTF("POST tests successful\r\n");
    	post_flag = 1;
    }
    else {
    	PRINTF("POST tests failed\r\n");
    	post_flag=0;
    }
    PRINTF("\r\nPost data read is: %d\r\n", post_status);
 //   I2C_write_byte(0x01, 0x60, 0xA0);
    delay=15;
/*    	PRINTF("\r\nTemperature in Celsius is: \r\n");
    	tempC = i2c_read_bytes(0x90, 0x00);
    	PRINTF("%d",tempC);
    	PRINTF("\r\nTemperature in Farhenheit is: \r\n");
    	tempF = (tempC * 1.8) + 32;
    	PRINTF("%d",tempF);
    	Init_SysTick();
    	SysTick_Handler(); */

    state_machine_1();
    if(delay_end)
    	delay_end=0;

   return 0 ;
}
