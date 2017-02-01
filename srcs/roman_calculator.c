/*
 * roman_calculator.c
 *
 *  Created on: Jan 31, 2017
 *      Author: rahil
 */

#include "roman_calculator.h"

/*
 * Declarations - Local types
 */
typedef struct {
	const char* roman_numeral;
	int	decimal_value;
} roman_decimal_table_type;

/*
 * Declarations - Local functions
 */
int roman_numeral_to_decimal(const char *roman_numeral);
int roman_letter_to_decimal(const char roman_letter);
char decimal_to_roman_letter(int decimal);
void decimal_to_roman_numeral(int decimal, char* output_roman_numeral);

/*
 * Defines
 */

#define RUN_ONLY_THRICE(x)	if(x < 3) 	\
							{			\
								x++;	\
							}			\
							else		\
							{			\
								x=0;	\
								break;	\
							}

/*
 * Global Variables
 */

/*
 * Static Variables
 */

static char *strSum = 0;
static roman_decimal_table_type const roman_decimal_table[] = {
		{"I", 1},
		{"V", 5},
		{"X", 10},
		{"L", 50},
		{"C", 100},
		{"D", 500},
		{"M", 1000},
};
const int table_length = 7;

/* **************************************************************************
 *                         Global Functions
 * **************************************************************************/
/*
 * open_roman_calculator
 *
 * Inputs: 	None
 *
 * Output:	None
 *
 * Notes: It is necessary to call this API to initialize the library
 */
void open_roman_calculator()
{
	strSum = (char*) malloc(MAX_SUM_BUFFER_SIZE);
	if(NULL != strSum)
	{
		/* Initialize the buffer */
		memset(strSum, 0, MAX_SUM_BUFFER_SIZE);
	}
	else
	{
		;
	}
	/* TODO: Add return code for handling less memory issue */
}

/*
 * add_two_roman_numbers
 *
 * Inputs: 	roman_numeral_1 (char*)
 * 			roman_numeral_2 (char*)
 *
 * Output:	The result of addition of roman_numeral_1 and roman_numeral_2
 *
 * Notes:
 * 	1. If any of the inputs are NULL or '/0', the output string is empty
 * 	2. If any of the inputs are invalid numerals like "IIII", then it'll be ignored
 */
char* add_two_roman_numbers(const char* roman_numeral_1, const char* roman_numeral_2)
{
	int decimal_sum = 0;

	/* Populate the sum in decimal */
	decimal_sum = roman_numeral_to_decimal(roman_numeral_1) +
			roman_numeral_to_decimal(roman_numeral_2);

#ifdef _DEBUG_PRINTS
	printf("Roman Numeral 1: %s\t converted to %d\n",
			roman_numeral_1, roman_numeral_to_decimal(roman_numeral_1));
	printf("Roman Numeral 2: %s\t converted to %d\n",
				roman_numeral_2, roman_numeral_to_decimal(roman_numeral_2));
	printf("Sum in decimals: %d\n", decimal_sum);
#endif

	/* Reset the internal buffer */
	memset(strSum, 0, MAX_SUM_BUFFER_SIZE);

	/* Convert the decimal sum in roman numeral */
	if(decimal_sum > 0)
		decimal_to_roman_numeral(decimal_sum, strSum);

	return strSum;
}

/*
 * subtract_two_roman_numbers
 *
 * Inputs: 	roman_numeral_1 (char*)
 * 			roman_numeral_2 (char*)
 *
 * Output:	The result of subtraction of roman_numeral_1 and roman_numeral_2
 *
 * Notes:
 * 	1. If any of the inputs are NULL or '/0', the output string is empty
 * 	2. If any of the inputs are invalid numerals like "IIII", then it'll be ignored
 * 	3. If roman_numeral_2 is bigger than roman_numeral_1, the output string is empty
 */
char* subtract_two_roman_numbers(const char* roman_numeral_1, const char* roman_numeral_2)
{
	int decimal  = 0;
	int operand1 = 0;
	int operand2 = 0;

	operand1 = roman_numeral_to_decimal(roman_numeral_1);
	operand2 = roman_numeral_to_decimal(roman_numeral_2);

	/* Check if operand2 is bigger than operand1 */
	if(operand2 >= operand1)
		decimal = 0;
	else
		decimal = operand1 - operand2;

#ifdef _DEBUG_PRINTS
	printf("Roman Numeral 1: %s\t converted to %d\n",
			roman_numeral_1, roman_numeral_to_decimal(roman_numeral_1));
	printf("Roman Numeral 2: %s\t converted to %d\n",
				roman_numeral_2, roman_numeral_to_decimal(roman_numeral_2));
	printf("Subtraction in decimals: %d\n", decimal);
#endif

	/* Reset the internal buffer */
	memset(strSum, 0, MAX_SUM_BUFFER_SIZE);

	/* Convert the decimal sum in roman numeral */
	if(decimal >0)
		decimal_to_roman_numeral(decimal, strSum);

	return strSum;
}

/*
 * close_roman_calculator
 *
 * Inputs: 	None
 *
 * Output:	None
 *
 * Notes: It is necessary to call this API to avoid memory leaks
 */
void close_roman_calculator(void)
{
	if(NULL != strSum)
	{
		free(strSum);
	}
}

/* **************************************************************************
 *                         Local Functions
 * **************************************************************************/

int roman_numeral_to_decimal(const char* roman_numeral)
{
	int decimal_value   = 0;
	int current_value   = 0;
	int previous_value  = 0;
	int counter         = 0;

	while('\0' != roman_numeral[counter])
	{
		current_value = roman_letter_to_decimal(roman_numeral[counter]);
		if(current_value >= previous_value)
		{
			decimal_value += current_value;
		}
		else
		{
			if(roman_numeral[counter+1] != '\0')
				decimal_value -= current_value;
			else
				decimal_value += current_value;
		}
		previous_value = current_value;
		counter++;
	}

	return decimal_value;
}

int roman_letter_to_decimal(const char roman_letter)
{
	int counter=0;
	int decimal_value=0;

	for(counter=0; counter<table_length; counter++)
	{
		if(*(roman_decimal_table[counter].roman_numeral) == roman_letter)
		{
			decimal_value = roman_decimal_table[counter].decimal_value;
			break;
		}
	}

	return decimal_value;
}

char decimal_to_roman_letter(int decimal)
{
	int counter=0;
	char roman_letter ='\0';

	for(counter=0; counter<table_length; counter++)
	{
		if(roman_decimal_table[counter].decimal_value == decimal)
		{
			roman_letter = *(roman_decimal_table[counter].roman_numeral);
			break;
		}
	}

	return roman_letter;
}

void decimal_to_roman_numeral(int decimal, char* output_roman_numeral)
{
	int indent = 0;
	int counter = 0;

	while(decimal >= 1000)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(1000);
		indent++;
		decimal -= 1000;
	}

	/* Middle cases */
	if(decimal == 900)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(100);
		indent++;
		output_roman_numeral[indent] = decimal_to_roman_letter(1000);
		indent++;
		decimal -= 900;
	}

	/* If the numeral is V, L or D you can't have more than one */
	if(decimal >= 500)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(500);
		indent++;
		decimal -= 500;
	}

	/* Middle cases */
	if(decimal == 400)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(100);
		indent++;
		output_roman_numeral[indent] = decimal_to_roman_letter(500);
		indent++;
		decimal -= 400;
	}

	/* If the numeral is I, X or C you can't have more than three */
	while(decimal >= 100)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(100);
		indent++;
		decimal -= 100;
		RUN_ONLY_THRICE(counter);
	}

	/* Middle cases */
	if(decimal == 90)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(10);
		indent++;
		output_roman_numeral[indent] = decimal_to_roman_letter(100);
		indent++;
		decimal -= 90;
	}

	/* If the numeral is V, L or D you can't have more than one */
	if(decimal >= 50)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(50);
		indent++;
		decimal -= 50;
	}
	/* Middle cases */
	if(decimal == 40)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(10);
		indent++;
		output_roman_numeral[indent] = decimal_to_roman_letter(50);
		indent++;
		decimal -= 40;
	}

	/* If the numeral is I, X or C you can't have more than three */
	while(decimal >= 10)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(10);
		indent++;
		decimal -= 10;
		RUN_ONLY_THRICE(counter);
	}

	/* Middle cases */
	if(decimal == 9)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(1);
		indent++;
		output_roman_numeral[indent] = decimal_to_roman_letter(10);
		indent++;
		decimal -= 9;
	}

	/* If the numeral is V, L or D you can't have more than one */
	if(decimal >= 5)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(5);
		indent++;
		decimal -= 5;
	}

	/* Middle cases */
	if(decimal == 4)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(1);
		indent++;
		output_roman_numeral[indent] = decimal_to_roman_letter(5);
		indent++;
		decimal -= 4;
	}

	/* If the numeral is I, X or C you can't have more than three */
	while(decimal >= 1)
	{
		output_roman_numeral[indent] = decimal_to_roman_letter(1);
		indent++;
		decimal -= 1;
		RUN_ONLY_THRICE(counter);
	}

	strSum[indent] = '\0';
}
