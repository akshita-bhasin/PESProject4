/*
 * i2c.c
 *
 *  Created on: Oct 29, 2019
 *      Author: ASUS
 */

#include "i2c.h"
uint8_t data[3];

void I2C_Init(void)
{
	/* Enable clock for I2C0 module */
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	/* Enable clock for Port C */
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	/* Port C MUX configuration */
	PORTC->PCR[8] |=  PORT_PCR_MUX(2);
	PORTC->PCR[9] |=  PORT_PCR_MUX(2);

	/* Configure Divider Register */
	I2C0->F |= I2C_F_MULT(0) | I2C_F_ICR(0X11);

	/* Enable I2C module and interrupt */
	I2C0->C1 |= I2C_C1_IICEN_MASK;// | I2C_C1_IICIE_MASK;

	/* Select high drive mode */
	I2C0->C2 |= I2C_C2_HDRS_MASK;

	I2C0->SLTH |= I2C_SLTH_SSLT(0x01);
}

#define I2C_M_START  I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP   I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN     I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC     I2C0->C1 &= ~I2C_C1_TX_MASK

#define I2C_WAIT    while((I2C0->S &I2C_S_IICIF_MASK) == 0) {}\
						I2C0->S |= I2C_S_IICIF_MASK;

#define NACK        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK         I2C0->C1 &= ~I2C_C1_TXAK_MASK

//extern uint8_t delay;
//extern uint8_t delay_end;


void I2C_write_byte(uint8_t reg, uint8_t data)
{
     I2C_TRAN;                    // Transmit
     I2C_M_START;                 // Generate START SIGNAL

     I2C0->D = 0x90;
     I2C_WAIT;

     I2C0->D = reg;              // Device register address
     /* Pointer register byte 000000+(00) for temperature register read only  */
     //changed to configuration register
     I2C_WAIT;

     I2C0->D = data;            // Send Configuration register byte 1
     I2C_WAIT;

     I2C_M_STOP;
     //Send stop bit
}

void I2C_write_bytes(uint8_t reg, uint8_t data1, uint8_t data2)
{
     I2C_TRAN;                    // Transmit
     I2C_M_START;                 // Generate START SIGNAL

     I2C0->D = 0x90;
     I2C_WAIT;

     I2C0->D = reg;              // Device register address
     /* Pointer register byte 000000+(00) for temperature register read only  */
     //changed to configuration register
     I2C_WAIT;

     I2C0->D = data1;            // Send Configuration register byte 1
     I2C_WAIT;

     I2C0->D = data2;            // Send Configuration register byte 2
     I2C_WAIT;

     I2C_M_STOP;
     //Send stop bit
}

uint8_t i2c_read_byte(uint8_t dev, uint8_t reg)
{
	uint8_t data;

	I2C_TRAN;
	I2C_M_START;
	I2C0->D = dev;
	I2C_WAIT;

	I2C0->D = reg;
	I2C_WAIT;

	I2C_M_RSTART;

	I2C0->D = (dev|0x1);
	I2C_WAIT;

	I2C_REC;
	NACK;

	data = I2C0->D;
	I2C_WAIT;

	I2C_M_STOP;
	data = I2C0->D;

	return data;
}

uint8_t i2c_read_bytes(uint8_t dev, uint8_t reg)
{
	uint16_t temp;
	uint8_t tempC;

	I2C_TRAN;
	I2C_M_START;
	I2C0->D = dev;
	I2C_WAIT;

	I2C0->D = reg;
	I2C_WAIT;

	I2C_M_RSTART;

	I2C0->D = (dev|0x1);
	I2C_WAIT;

	I2C_REC;
	ACK;

	data[0] = I2C0->D;
	I2C_WAIT;

	data[0] = I2C0->D;
	I2C_WAIT;

	NACK;

	data[1] = I2C0->D;
	I2C_WAIT;

	I2C_M_STOP;

	temp = ((data[0] << 4) | (data[1] >> 4));
	tempC = temp * 0.0625;
	return tempC;
}

void alert_init(void)
{
	uint8_t tl0a=  0x1d;
	uint8_t tl0b= 0x00;

	uint8_t th0a = 0x1d;
	uint8_t th0b = 0x00;

	I2C_write_bytes(0x02, tl0a, tl0b);
	delay_loop(10000);
	I2C_write_bytes(0x03, th0a, th0b);
}
