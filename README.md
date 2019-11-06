# PESProject4

This is a readme file for Project #4 for the Principles of Embedded Software (Fall 2019) class.

Team Members : Akshita Bhasin and Madhukar Arora

Source Files :

1.  i2c. h : Header file contains includes for I2C configuration with the TMP102 Temperature sensor module and function prototypes.
    
2.  i2c.c : Source file contains I2C configuration with the TMP102 Temperature sensor module.
    
3.  led_control.h : Header file contains includes for controlling the RGB LED on the FRDM KL25Z Board and function prototypes
    
4.  led_control.c : Source file contains code for controlling the RGB LED on the FRDM KL25Z Board
    
5.  logger.h : contains function prototypes and includes for logger implementation
    
6.  logger.c : contains logger implementation
    
7.  state_machine.h : contains includes, enum declarations and function prototypes for statemachine implementation
    
8.  state_machine.c : contains statemachine implementation
    
9.  PESProject4.c : Application Entry Point
    

Test Files :

1.  test.c : Unit test case
    
2.  test.h : Contains required function prototypes and header files for executing test.c
    

Guides on Compilation / Execution Notes:

Hardware USED : Freedom Board FRDM KL25Z

IDE USED : MCU Xpresso ([https://mcuxpresso.nxp.com/en/welcome](https://mcuxpresso.nxp.com/en/welcome))

1.  Clean before building any build targets.
    
2.  Build Targets:
    
    Please refer to the following build targets along with their functionality for compilation.
    
    1.  all MODULE = DEBUG_LOG
        
        If selected, the program will run in debug mode with detailed messages logged to the UART.
        
    2.  all MODULE = NORMAL
        
        If selected, the program will run in normal mode with normal messages logged to the UART.
        
    3.  all MODULE = TEST
        
        If selected, the program will run in test mode with detailed test messages logged to the UART.
        
        Note : If there are any elf errors, delete the existing debug folder and create a new one.
        

Observations:

1.  While observing the I2C transactions on the logic analyser, the SCL and the SDA lines constantly read high even though the temperature was being read from the sensor. The issue was resolved by reducing the sampling rate from 100MHz to 50MHz and increasing the logic threshold level to 1.75V
    
2.  There were issues with reading temperature values from the TMP102 via I2C. Initially we were reading only single byte of data which resulted in erroneous temperature values. On reading the TMP102 data sheet, this error was solved by reading two bytes of data.
