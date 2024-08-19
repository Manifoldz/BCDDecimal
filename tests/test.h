#ifndef TESTS_H
#define TESTS_H

#define TRUE 1
#define FALSE 0

#include <check.h>
// #include <stdio.h>
#include <stdlib.h>
// #include <time.h> // ATTENTION! USE ONLY FOR LEAK TESTING!

#include "../s21_decimal.h"

// 9999999999999999
#define MAX_BCD_UINT 11068046444225730969ULL

Suite *suite_bits_manipulation(void);
Suite *suite_aux(void);
Suite *suite_core(void);
Suite *suite_compares(void);
Suite *suite_arithmetics(void);
Suite *suite_rounds(void);
Suite *suite_convert(void);

// Free str-memory and makes NULL-ptr
void s21_free_str(char **str_in);

#endif
