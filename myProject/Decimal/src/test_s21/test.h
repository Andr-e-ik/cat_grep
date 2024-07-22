#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../secondary_functions.h"

#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3
#define TEST_COMPARISONS_ONE 1
#define TEST_COMPARISONS_ZERO 0

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
// void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
// void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int
// code_check); void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
//                     s21_decimal decimal_check, int code_check);
// void test_mod(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
// void test_mod_fail(s21_decimal decimal1, s21_decimal decimal2, int
// code_check);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);

#endif