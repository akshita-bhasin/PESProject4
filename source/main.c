/*
 * @File Name   : main.c
 * @Brief  : Application Entry Point
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 10/25/2019
 * leveraged code : http://web.archive.org/web/20160517005245/http://www.gedan.net/2008/09/08/finite-state-machine-matrix-style-c-implementation
 */

#include "main.h"

uint8_t post_status, post_flag, alert_status_tl0, alert_status_th0;
int8_t tempinC;

void delay_loop(uint16_t num)
{
	for(uint8_t i=num; i>0; i--);
}

int main(void)
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    I2C_Init();
    post_status = i2c_read_byte(0x90, 0x01);
    if(post_status == 96 || post_status == 98) {
	#ifdef NORMAL
    	log_string_detail(Status, I2c_read_byte, "POST tests successful");
	#endif
	#ifdef DEBUG_LOG
    	log_string_detail(Debug, I2c_read_byte, "POST tests successful with i2c_read for config register");
	#endif

    	post_flag = 1;
    }
    else {
	#ifdef NORMAL
    	log_string_detail(Status, I2c_read_byte, "POST tests failed");
	#endif
	#ifdef DEBUG_LOG
	log_string_detail(Debug, I2c_read_byte, "POST tests failed with i2c_read for config register");
	#endif
    	post_flag=0;
    	turn_on_led_color('R');
    }
    if(post_flag==0)
    	while(1);
    I2C_write_byte(0x01, 0x60);
    delay_loop(10000);
    uint8_t data = i2c_read_byte(0x90, 0x01);
#ifdef DEBUG_LOG
    log_string_detail(Debug, I2c_read_byte, "Written data into config register: ");
#endif
#ifdef NORMAL
    log_string_detail(Status, I2c_read_byte, "Written data: ");
#endif
    log_integer(data, 'H');
    log_string("Post data read is: ");
    log_integer(post_status, 'd');
    I2C_write_bytes(0x01, 0x60, 0xA0);
#ifdef DEBUG_LOG
    log_string_detail(Debug, I2c_write_bytes, "0x60 and 0xA0 written into config register");
#endif
#ifdef NORMAL
    log_string_detail(Status, I2c_write_bytes, "0x60 and 0xA0 written");
#endif
    delay_loop(20000);
    uint8_t data1 = i2c_read_byte(0x90, 0x01);
#ifdef DEBUG_LOG
    log_string_detail(Debug, I2c_read_byte, "First byte of data written in config register");
#endif
#ifdef NORMAL
    log_string_detail(Status, I2c_read_byte, "First byte of data");
#endif
    log_integer(data1, 'H');
    SysTick_Config(48000000L/100L);
	uint8_t init_tl0 = i2c_read_byte(0x90, 0x02);
	PRINTF("\r\nTL0: %d\r\n", init_tl0);

	delay_loop(10000);

	uint8_t init_th0 = i2c_read_byte(0x90, 0x03);
	PRINTF("\r\nTH0: %d\r\n", init_th0);

	delay_loop(10000);

	alert_init();

	delay_loop(10000);
	alert_status_tl0 = i2c_read_byte(0x90, 0x02);
	PRINTF("Alert: %d\r\n", alert_status_tl0);
	delay_loop(10000);
	alert_status_th0 = i2c_read_byte(0x90, 0x03);
	PRINTF("Alert: %d\r\n", alert_status_th0);
	if(post_flag==1)
		state_machine_1();
   return 0 ;
}
