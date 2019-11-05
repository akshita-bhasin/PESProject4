/* @file System.c
 * @brief System dependent functions used by uCUnit.                 *
 *                This file runs with arm-elf-run
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 10/18/2019
 * @version 1.0
 *
 ** Referred to uCUbit from mcuoneclipse for the uCUnit case files

*****************************************************************************
 *                                                                           *
 *  uCUnit - A unit testing framework for microcontrollers                   *
 *                                                                           *
 *  (C) 2007 - 2008 Sven Stefan Krauss                                       *
 *                  https://www.ucunit.org                                   *
                                     *
 *****************************************************************************/

/*
 * This file is part of ucUnit.
 *
 * You can redistribute and/or modify it under the terms of the
 * Common Public License as published by IBM Corporation; either
 * version 1.0 of the License, or (at your option) any later version.
 *
 * uCUnit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with uCUnit.
 *
 * It may also be available at the following URL:
 *       http://www.opensource.org/licenses/cpl1.0.txt
 *
 * If you cannot obtain a copy of the License, please contact the
 * author.
 */
#include <stdio.h>
#include <stdlib.h>
#include "System.h"
#ifdef KL25Z_UT
#include "fsl_debug_console.h"
#endif

void System_exit(int val) {
	for(;;) {
		/* we don't do a shutdown with exit(), as this is will affect debugging.
		 * Instead, we stay here in an endless loop.
		 */
		__asm("nop"); /* burning some CPU cycles here */
	}
	// exit(val);
}

/* Stub: Initialize your hardware here */
void System_Init(void)
{
#ifdef KL25Z_UT
	PRINTF("Init of hardware finished.\n");
#endif
#ifdef PC_UT
	printf("Init of hardware finished.\n");
#endif
}

/* Stub: Shutdown your hardware here */
void System_Shutdown(void)
{
	/* asm("\tSTOP"); */
#ifdef KL25Z_UT
	PRINTF("System shutdown.\n");
#endif
#ifdef PC_UT
	printf("System shutdown.\n");
#endif
	System_exit(0);
}

/* Stub: Recover the system */
void System_Recover(void)
{
	/* Stub: Recover the hardware */
	/* asm("\tRESET"); */
#ifdef KL25Z_UT
	PRINTF("System reset.\n");
#endif
#ifdef PC_UT
	printf("System reset.\n");
#endif
	System_exit(0);
}

/* Stub: Put system in a safe state */
void System_Safestate(void)
{
	/* Disable all port pins */
	/* PORTA = 0x0000; */
	/* PORTB = 0x0000; */
	/* PORTC = 0x0000; */

	/* Disable interrupts */
	/* DIE(); */

	/* Put processor into idle state */
	/* asm("\tIDLE"); */
#ifdef KL25Z_UT
	PRINTF("System safe state.\n");
#endif
#ifdef PC_UT
	printf("System safe state.\n");
#endif
	System_exit(0);
}

/* Stub: Transmit a string to the host/debugger/simulator */
void System_WriteString(char * msg)
{
#ifdef KL25Z_UT
	PRINTF(msg);
#endif
#ifdef PC_UT
	printf(msg);
#endif
}

void System_WriteInt(int n)
{
#ifdef KL25Z_UT
	PRINTF("%d", n);
#endif
#ifdef PC_UT
	printf("%d", n);
#endif
}
