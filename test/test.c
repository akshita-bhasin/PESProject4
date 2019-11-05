/* @file test.c
 * @brief Unit test cases for PES_Project3
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 10/18/2019
 * @version 1.0
 */

#include "test.h"

uint8_t i;
const int8_t seed = 8;
uint8_t status;
uint32_t * address = NULL;
uint32_t verify_arr[16];

/*
 Function Name: unit_test_cases
 Function arguments: void
 Function return type: void
 Brief: performs unit tests on various memory functions
*/
void unit_test_cases(void)
{
	//Test case for allocate bytes
	UCUNIT_TestcaseBegin("Allocate bytes test pass");
	uint32_t * allocate_test_1 = allocate_words(LENGTH);
	UCUNIT_CheckIsNotNull(allocate_test_1);
	UCUNIT_TestcaseEnd();
	free_words(allocate_test_1); // freeing allocated memory after every test case

	//Test for boundary conditions in allocate
	UCUNIT_TestcaseBegin("Allocate bytes test fail");
	uint32_t * allocate_test_2 = allocate_words(5000);
	UCUNIT_CheckIsNull(allocate_test_2);
#ifdef KL25Z_UT
	LED_RED_ON();
	LED_GREEN_OFF();
	LED_BLUE_OFF();
#endif
	UCUNIT_TestcaseEnd();
	free_words(allocate_test_2);

	//Write pattern test if status is 0
	UCUNIT_TestcaseBegin("Write pattern pass test");
	uint32_t * write_pattern_alloc = allocate_words(LENGTH);
	status = write_pattern(write_pattern_alloc, LENGTH, seed);
	UCUNIT_CheckIsEqual(status,0);
	UCUNIT_TestcaseEnd();
	free_words(write_pattern_alloc);

	//Display memory test to check if any memory displayed
	UCUNIT_TestcaseBegin("Display memory test");
	uint32_t * disp_mem_alloc = allocate_words(LENGTH);
	uint8_t * disp_mem = display_memory(disp_mem_alloc, LENGTH);
	UCUNIT_CheckIsNotNull(disp_mem);
	UCUNIT_TestcaseEnd();
	free_words(disp_mem_alloc);

	/* Write memory test for storing AA in memory, checking if 8 bit,
	 * if written successfully, and if actually written in memory
	 * by reading it
	 */
	UCUNIT_TestcaseBegin("Write memory test pass");
	uint32_t * write_mem_alloc = allocate_words(LENGTH);
	for(i=0;i<LENGTH/4;i++) {
		status = write_memory(get_address(write_mem_alloc, i), 0xAA);
		UCUNIT_CheckIs8Bit(0xAA);
		UCUNIT_CheckIsEqual(status,0);
	}
	for(i=0; i<LENGTH/16; i++) {
		uint8_t mem_value = *((uint8_t*)(write_mem_alloc+i));
		UCUNIT_CheckIsEqual(mem_value, 0xAA);
	}
	UCUNIT_TestcaseEnd();
	free_words(write_mem_alloc);

	/* Write memory test for storing AA in memory, checking if
	 * written successfully, and if actually written in memory
	 * by reading it
	 */
	UCUNIT_TestcaseBegin("Write memory test fail");
	uint32_t * write_mem_fail_alloc = allocate_words(LENGTH);
	for(i=0;i<LENGTH/4;i++) {
		status = write_memory(get_address(write_mem_fail_alloc, i*200), 0xAA);
		UCUNIT_CheckIsEqual(status,0);
	}
	for(i=0; i<LENGTH/16; i++) {
		uint8_t mem_fail_value = *((uint8_t*)(write_mem_fail_alloc+i));
		UCUNIT_CheckIsEqual(mem_fail_value, 0xAA);
	}
	UCUNIT_TestcaseEnd();
	free_words(write_mem_fail_alloc);

	/* Invert block in memory test, checking if inverted
	 * successfully, and if actually written in memory by reading it
	 */
	UCUNIT_TestcaseBegin("Invert memory block test pass");
	uint32_t * invert_block_alloc = allocate_words(LENGTH);
	for(i=0;i<LENGTH/4;i++) {
		*(invert_block_alloc+i) = i;
		status = invert_block(get_address(invert_block_alloc, i), 4);
		UCUNIT_CheckIsEqual(status,0);
	}
	for(i=0; i<LENGTH/8; i++) {
		uint8_t invert_value = *((uint8_t*)(invert_block_alloc+i));
		UCUNIT_CheckIsEqual(invert_value, i^0xFF);
	}
	UCUNIT_TestcaseEnd();
	free_words(invert_block_alloc);

	/* Invert block in memory test, checking if inverted
	 * successfully, and if actually written in memory by reading it
	 */
	UCUNIT_TestcaseBegin("Invert memory block test fail");
	uint32_t * invert_block_fail_alloc = allocate_words(LENGTH);
	for(i=0;i<LENGTH/4;i++) {
		*(invert_block_alloc+i) = i;
		status = invert_block(get_address(invert_block_fail_alloc, i), 4);
		UCUNIT_CheckIsEqual(status,0);
	}
	for(i=0; i<LENGTH/4; i++) {
		uint8_t invert_fail_value = *((uint8_t*)(invert_block_fail_alloc+i));
		UCUNIT_CheckIsEqual(invert_fail_value, i);
	}
	UCUNIT_TestcaseEnd();
	free_words(invert_block_fail_alloc);

	// Get adddress with offset from memory, checking if written
	UCUNIT_TestcaseBegin("Get address test");
	uint32_t * get_addr_alloc = allocate_words(LENGTH);
	uint32_t * get_addr = NULL;
	for(i=0;i<LENGTH/16;i++) {
		get_addr = get_address(get_addr_alloc, i);
		UCUNIT_CheckIsEqual(get_addr, (get_addr_alloc+i));
	}
	UCUNIT_TestcaseEnd();
	free_words(get_addr_alloc);

	/* Verify memory test, by writing a pattern,
	 * and verifying if new pattern is same as earlier pattern
	 */
	UCUNIT_TestcaseBegin("Verify memory test ");
	uint32_t * verify_mem_alloc = allocate_words(LENGTH);
	status = write_pattern(verify_mem_alloc, LENGTH, seed);
	UCUNIT_CheckIsEqual(status,0);
	address = verify_pattern(verify_mem_alloc, LENGTH, seed);
	UCUNIT_CheckIsEqual(address[0], 0);
	UCUNIT_TestcaseEnd();
	free_words(verify_mem_alloc);

	/* Verify memory test, by writing a pattern,
	 * and verifying if new pattern is different from earlier pattern
	 */
	UCUNIT_TestcaseBegin("Verify memory test with failed address");
	uint32_t * verify_mem_alloc_fail = allocate_words(LENGTH);
	status = write_pattern(verify_mem_alloc_fail, LENGTH, seed);
	UCUNIT_CheckIsEqual(status,0);
	write_memory(get_address(verify_mem_alloc_fail, 1), 0x11);
	write_memory(get_address(verify_mem_alloc_fail, 2), 0x22);
	address = verify_pattern(verify_mem_alloc_fail, LENGTH, seed);
	UCUNIT_CheckIsNotNull(address);
	UCUNIT_TestcaseEnd();
	free_words(verify_mem_alloc_fail);

	//Free words unit test to check for a fail case
	UCUNIT_TestcaseBegin("Free words test");
	uint32_t * free_words_alloc = allocate_words(LENGTH);
	free_words(free_words_alloc);
	UCUNIT_CheckIsNull(free_words_alloc);
	UCUNIT_TestcaseEnd();
}

int main(void) {
	//Initializing board pins
#ifdef KL25Z_UT
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();
#endif
	//Calling function to run memory tests
	unit_test_cases();
	return 0;
}
