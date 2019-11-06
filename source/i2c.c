/*
 *@File Name : i2c.c
 *@Brief: Source file contains I2C configuration with the TMP102 Temperature sensor module
 *Created on: Oct 29, 2019
 *Author: Akshita Bhasin & Madhukar Arora
 */

#include "i2c.h"
uint8_t data[3]; //to store temperature values received from the sensor
extern uint8_t disconnect_flag;

/*
 * function name : I2C_Init
 * parameter : void
 * return type : void
 * @brief : configures the I2C registers on the FRDM KL25Z
 */
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

	PORTA->PCR[5] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x09) | PORT_PCR_PE_MASK;

	GPIOA->PDDR |= 0x01 << 5;
	//NVIC_EnableIRQ(PORTA_IRQHandler());
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

/*
 * function name : I2C_write_byte
 * parameter : uint8_t reg - pointer register value , uint8_t data - value for configuration register
 * return type : void
 * @brief : writes a single byte to the configuration register
 */
void I2C_write_byte(uint8_t reg, uint8_t data)
{
     I2C_TRAN;                    // Transmit
     I2C_M_START;                 // Generate START SIGNAL

     I2C0->D = 0x90;
     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C0->D = reg;              // Device register address(00 for temperature register read only)

     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C0->D = data;            // Send Configuration register byte 1
     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C_M_STOP;				//Send stop bit
}

/*
 * function name : I2C_write_bytes
 * parameter : uint8_t reg - pointer register value , uint8_t data1 - byte1,uint8_t data2 - byte2
 * return type : void
 * @brief : writes two bytes to the configuration register
 */
void I2C_write_bytes(uint8_t reg, uint8_t data1, uint8_t data2)
{
     I2C_TRAN;                    // Transmit
     I2C_M_START;                 // Generate START SIGNAL

     I2C0->D = 0x90;
     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C0->D = reg;              // Device register address

     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C0->D = data1;            // Send Configuration register byte 1
     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C0->D = data2;            // Send Configuration register byte 2
     if(i2c_wait())
     {
    	 disconnect_flag=1;
     }

     I2C_M_STOP;				//Send stop bit
}

/*
 * function name : i2c_read_byte
 * parameter : uint8_t dev, uint8_t reg - pointer register value
 * return type : uint8_t
 * @brief : reads 1 byte of data from the TMP102
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t reg)
{
	uint8_t data;

	I2C_TRAN;
	I2C_M_START;
	I2C0->D = dev;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C0->D = reg;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C_M_RSTART;

	I2C0->D = (dev|0x1);
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C_REC;
	NACK;

	data = I2C0->D;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C_M_STOP;
	data = I2C0->D;

	return data;
}

uint8_t i2c_wait(void)
{
	uint8_t connect = 0;
	volatile uint16_t i;
	while((I2C0->S &I2C_S_IICIF_MASK) == 0)
	{
		i++;
		if(i>50000)
			break;
	}
	if(i>50000)
		connect = 1;
	else
		connect = 0;

	I2C0->S |= I2C_S_IICIF_MASK;

	return connect;
}

/*
 * function name : i2c_read_bytes
 * parameter : uint8_t dev, uint8_t reg - pointer register value
 * return type : int8_t
 * @brief : reads 2 bytes of temperature data from the TMP102 and returns temperature in Celsius
 */
int16_t i2c_read_bytes(uint8_t dev, uint8_t reg)
{
	int16_t temp;

	I2C_TRAN;
	I2C_M_START;
	I2C0->D = dev;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C0->D = reg;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C_M_RSTART;

	I2C0->D = (dev|0x1);
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C_REC;
	ACK;

	data[0] = I2C0->D;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	data[0] = I2C0->D;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	NACK;

	data[1] = I2C0->D;
    if(i2c_wait())
    {
   	 disconnect_flag=1;
    }

	I2C_M_STOP;

	temp = ((data[0] << 4) | (data[1] >> 4));
	return temp;
}

/*
 * function name : alert_init
 * parameter : void
 * return type : void
 * @brief : initializes the TLow and THigh value on the TMP102
 */
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
