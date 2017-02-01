/*
 * tests.c
 *
 *  Created on: Jan 31, 2017
 *      Author: rahil
 */

#include <check.h>
#include "roman_calculator.h"

START_TEST(TestAdditionOfTwoRomanNumbers)
{
	open_roman_calculator();
	ck_assert_str_eq(add_two_roman_numbers("I", "I"), "II");
	ck_assert_str_eq(add_two_roman_numbers("XX", "II"), "XXII");
	ck_assert_str_eq(add_two_roman_numbers("XIV", "LX"), "LXXIV");
	ck_assert_str_eq(add_two_roman_numbers("II", "II"), "IV");
	ck_assert_str_eq(add_two_roman_numbers("D", "D"), "M");
	close_roman_calculator();
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, TestAdditionOfTwoRomanNumbers);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
