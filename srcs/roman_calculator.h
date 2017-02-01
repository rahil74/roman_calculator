/*
 * roman_calculator.h
 *
 *  Created on: Jan 31, 2017
 *      Author: rahil
 */

#ifndef ROMAN_CALCULATOR_H_
#define ROMAN_CALCULATOR_H_


#include <stdlib.h>
#include <string.h>
#ifdef _DEBUG_PRINTS
#include <stdio.h>
#endif

/*
 * Maximum size of the buffer to store sum
 *
 * Can be optimized for smaller calculations
 *
 */
#define MAX_SUM_BUFFER_SIZE 64

/* Initializes the roman calculator library */
void open_roman_calculator(void);
/* Adds and returns the sum of roman_numeral_1 and roman_numeral_2 */
char* add_two_roman_numbers(const char* roman_numeral_1, const char* roman_numeral_2);
/* Subtracts two roman numbers */
char* subtract_two_roman_numbers(const char* roman_numeral_1, const char* roman_numeral_2);
/* Closes the roman calculator library */
void close_roman_calculator(void);

#endif /* ROMAN_CALCULATOR_H_ */
