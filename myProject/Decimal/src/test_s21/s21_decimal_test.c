#include "test.h"
// s21_add

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(code, check);
}

START_TEST(test_add_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  ck_assert_int_ne(s21_add(decimal1, decimal2, NULL), TEST_ARITHMETIC_OK);
}

START_TEST(test_add_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  ck_assert_int_ne(s21_add(decimal1, decimal2, &result), TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // 79228162514264337543839948913
  s21_decimal check = {{0x6D692071, 0xFFFFFFF4, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add11) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add12) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  test_add_fail(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add13) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add14) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_add15) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}
END_TEST

// s21_sub

void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, check);
}

START_TEST(test_sub_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_sub(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(test_sub_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub1) {
  // 7.922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 3.9614081257132168796771975172
  s21_decimal check = {{0x4, 0x0, 0x80000000, 0x1C0000}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub8) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  test_sub_fail(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub9) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_sub10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  test_sub_fail(decimal1, decimal2, check);
}
END_TEST

// s21_mul

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, code_check);
}

void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_mul_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_mul(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(test_mul_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST
// 6277101735 3866807638 3578942304 9210091073 8267692769 46612225
START_TEST(test_mul_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_manual1) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.8228162514264337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x1C0000}};
  // 61.978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x1B0000}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual2) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.8228162514264337593543950335
  s21_decimal decimal2 = {{0x4F63FFFF, 0xBB0D25CF, 0x1A962D2F, 0x801C0000}};
  // -6.5190219687391279469416894926
  s21_decimal check = {{0x23B23CAE, 0xEC60363A, 0xD2A415FA, 0x801C0000}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual3) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.00000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800E0000}};
  // 0.0000000000003500000000000012
  s21_decimal check = {{0x40B6C00C, 0xC6F3B, 0x0, 0x1C0000}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual4) {
  // -7922816251426.4337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  // 78228162514264.337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xF0000}};
  // -619787357287241642624224547.27
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80020000}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual5) {
  // -79228162514264.337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  // 782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
  // -61978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80000000}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual6) {
  // 79228162514264.1
  s21_decimal decimal1 = {{0x70D42571, 0x2D093, 0x0, 0x10000}};
  // 78228162514264.5
  s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
  // 6197873572872410706900970254.4
  s21_decimal check = {{0x7F6C2E90, 0x3FD777DD, 0xC8439BCC, 0x10000}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual7) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.00000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x50000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_mul_manual8) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_mul_fail1(decimal1, decimal2, code_check);
}
END_TEST

START_TEST(test_mul_manual9) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  test_mul_fail1(decimal1, decimal2, code_check);
}
END_TEST

START_TEST(test_mul_manual10) {
  // -0.0000000000000025
  s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // too small
  // 0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = TEST_ARITHMETIC_SMALL;

  test_mul_fail2(decimal1, decimal2, decimal_check, code_check);
}
END_TEST

START_TEST(test_mul1) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_mul2) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_mul3) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_mul4) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991720
  s21_decimal decimal_check = {
      {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_mul5) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387504754779197847983442
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}
END_TEST

void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, code_check);
}

void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_div_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_div(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(test_div_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_manual1) {
  // 1.2640938749860586450804312205
  s21_decimal decimal1 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 0.6320469374930293225402156102
  s21_decimal check = {{0x8C444446, 0x5F128130, 0x146C2B73, 0x1C0000}};

  test_div(decimal1, decimal2, check);
}
END_TEST
/*
START_TEST(test_div_manual2) {
  // 2
  s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x0}};
  // 1.2640938749860586450804312205
  s21_decimal decimal2 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 1.5821609767882606564463392905
  s21_decimal check = {{0x8B80B889, 0x20B8279E, 0x331F5430, 0x1C0000}};

  test_div(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_div_manual3) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 12.640938749860586450805
  s21_decimal decimal2 = {{0x2EB3EF75, 0x4444026F, 0x2AD, 0x150000}};
  // 113255494.17884722765619814067
  s21_decimal check = {{0x6D7C5EB3, 0x2C521AF0, 0x24984660, 0x140000}};

  test_div(decimal1, decimal2, check);
}
END_TEST

// 00000000000111000000000000000000 00000000000100001000101100101010
// 00101100001010000000001010010000 10010100000000000000000000000000
START_TEST(test_div_manual4) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 500
  s21_decimal decimal2 = {{0x1F4, 0x0, 0x0, 0x0}};
  // 0.002
  s21_decimal check = {{0x2, 0x0, 0x0, 0x30000}};

  test_div(decimal1, decimal2, check);
}
END_TEST
*/

START_TEST(test_div_manual5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 10000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

  test_div(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_div_manual6) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};

  test_div(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_div_manual7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  int code_check = TEST_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST

START_TEST(test_div_manual8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST

START_TEST(test_div_manual9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST
/*

START_TEST(test_div_manual10) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  int code_check = TEST_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}
END_TEST

START_TEST(test_div_manual11) {
  // 0.0000000074505801528346182749
  s21_decimal decimal1 = {{0xCAD4845D, 0x9F9C7BD, 0x4, 0x1C0000}};
  // 1152921504606846976
  s21_decimal decimal2 = {{0x0, 0x10000000, 0x0, 0x0}};
  // 0.0000000000000000000000000065
  s21_decimal decimal_check = {{0x41, 0x0, 0x0, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_div_manual12) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = TEST_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}
END_TEST

START_TEST(test_div_manual13) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST
START_TEST(test_div_manual14) {
  // -79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST

START_TEST(test_div_manual15) {
  // 79228162514264337593543950319
  s21_decimal decimal1 = {{0xFFFFFFEF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST
*/

START_TEST(test_div1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_div2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_div3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_div4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST
/*
START_TEST(test_div5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 1.9999999999999999998915797827
  s21_decimal decimal_check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_div6) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // 20000000000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST
*/

START_TEST(test_div7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST

START_TEST(test_div8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 79149013500763574019524425909
  s21_decimal decimal_check = {{0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST

START_TEST(test_div9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = TEST_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}
END_TEST

/*
START_TEST(test_div10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // 1320469375237738959892399172.1
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}
END_TEST
*/

////// Comparision

START_TEST(test_comp_is_greater_1) {
  s21_decimal decimal1 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_greater_2) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_greater_3) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_greater_or_equal_1) {
  s21_decimal decimal1 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2),
                   TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_greater_or_equal_2) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2),
                   TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_greater_or_equal_3) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2),
                   TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_less_1) {
  s21_decimal decimal1 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_less_2) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_less_3) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_less_or_equal_1) {
  s21_decimal decimal1 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2),
                   TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_less_or_equal_2) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2),
                   TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_less_or_equal_3) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less_or_equal(decimal1, decimal2),
                   TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_equal_1) {
  s21_decimal decimal1 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_equal_2) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_equal_3) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_not_equal_1) {
  s21_decimal decimal1 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), TEST_COMPARISONS_ONE);
}
END_TEST

START_TEST(test_comp_is_not_equal_2) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), TEST_COMPARISONS_ZERO);
}
END_TEST

START_TEST(test_comp_is_not_equal_3) {
  s21_decimal decimal1 = {{1, 4, 4, 0b00000000000000000000000000000000}};
  s21_decimal decimal2 = {{2, 4, 4, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), TEST_COMPARISONS_ONE);
}
END_TEST

// truncate

void test_truncate(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_truncate(decimal, &result);
  int sign_check = INT_GET_BIT(decimal_check.bits[3], 31);
  int sign_result = INT_GET_BIT(decimal.bits[3], 31);
  ck_assert_int_eq(code, OK_rounders);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(test_truncate_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_truncate(decimal, NULL);

  ck_assert_int_eq(code, calculation_error_rounders);
}

START_TEST(test_truncate_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_truncate_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033
  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  test_truncate(decimal, decimal_check);
}

START_TEST(test_truncate_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  test_truncate(decimal, decimal_check);
}

// round

void test_round(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_round(decimal, &result);
  int sign_check = INT_GET_BIT(decimal_check.bits[3], 31);
  int sign_result = INT_GET_BIT(result.bits[3], 31);
  ck_assert_int_eq(code, OK_rounders);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(test_round_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_round(decimal, NULL);

  ck_assert_int_eq(code, calculation_error_rounders);
}

START_TEST(test_round_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_round_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_round(decimal, decimal_check);
}

START_TEST(test_round_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_round(decimal, decimal_check);
}

START_TEST(test_round_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_round(decimal, decimal_check);
}

START_TEST(test_round_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_round(decimal, decimal_check);
}

START_TEST(test_round_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  test_round(decimal, decimal_check);
}

// negate

void test_negate(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_negate(decimal, &result);
  int sign_check = INT_GET_BIT(decimal_check.bits[3], 31);
  int sign_result = INT_GET_BIT(result.bits[3], 31);
  ck_assert_int_eq(code, OK_rounders);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(test_negate_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_negate(decimal, NULL);

  ck_assert_int_eq(code, calculation_error_rounders);
}

START_TEST(test_negate_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_negate_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // -792281625142643375935439503.35
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

  test_negate(decimal, decimal_check);
}

// floor

void test_floor(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_floor(decimal, &result);
  int sign_check = INT_GET_BIT(decimal_check.bits[3], 31);
  int sign_result = INT_GET_BIT(result.bits[3], 31);
  ck_assert_int_eq(code, OK_rounders);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(test_floor_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, calculation_error_rounders);
}

START_TEST(test_floor_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, calculation_error_rounders);
}
END_TEST

START_TEST(test_floor_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  test_floor(decimal, decimal_check);
}

// convert

START_TEST(test_from_int_to_decimal1) {
  int src = 1027557455;
  s21_decimal dst = {{0x00011B7E, 0x00014CC3, 0x0000BDF8, 0x00009B31}};
  int error = s21_from_int_to_decimal(src, &dst);
  s21_decimal res = {{0x3D3F484F, 0x00000000, 0x00000000, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(dst.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_from_int_to_decimal2) {
  int inp = -1963415980;
  s21_decimal out = {{0x00011B7E, 0x00014CC3, 0x0000BDF8, 0x00009B31}};
  int error = s21_from_int_to_decimal(inp, &out);
  s21_decimal res = {{0x750759AC, 0x00000000, 0x00000000, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_from_int_to_decimal3) {
  int inp = -1963415980;
  int error = s21_from_int_to_decimal(inp, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_test1) {
  int true_res = 0;
  s21_decimal val1 = {{0x7E85626B, 0xCE0FBFB4, 0xFF7975A6, 0x80160000}};
  int result = -7906551;
  int output = 0;
  int s21_res = s21_from_decimal_to_int(val1, &output);
  ck_assert_int_eq(result, output);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_from_decimal_to_int_test2) {
  int true_res = 1;
  s21_decimal val1 = {{0xDBA2C5D3, 0xFF7CA645, 0x7B54257E, 0x00080000}};
  int result = 0;
  int output = 0;
  int s21_res = s21_from_decimal_to_int(val1, &output);
  ck_assert_int_eq(result, output);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_from_decimal_to_int_test3) {
  int true_res = 0;
  s21_decimal val1 = {{0x24D39F84, 0x3E98A64B, 0x86EF7DD5, 0x00160000}};
  int result = 4176051;
  int output = 0;
  int s21_res = s21_from_decimal_to_int(val1, &output);
  ck_assert_int_eq(result, output);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_from_decimal_to_int_test4) {
  int true_res = 0;
  s21_decimal val1 = {{0x0EA2437F, 0x76E20EFD, 0xF05B03D5, 0x80150000}};
  int result = -74386432;
  int output = 0;
  int s21_res = s21_from_decimal_to_int(val1, &output);
  ck_assert_int_eq(result, output);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_from_decimal_to_int_test5) {
  int true_res = 1;
  s21_decimal val1 = {{0x0EA2437F, 0x76E20EFD, 0xF05B03D5, 0x80150000}};
  int result = 1;
  int s21_res = s21_from_decimal_to_int(val1, NULL);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_from_decimal_to_float_test1) {
  s21_decimal val_1 = {{0x154338CA, 0x75E94EA2, 0xDD7ECF07, 0x00000000}};
  float *result = NULL;
  int error = s21_from_decimal_to_float(val_1, result);
  ck_assert_ptr_eq(result, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_test2) {
  s21_decimal val_1 = {{0x154338CA, 0x75E94EA2, 0xDD7ECF07, 0x00000000}};
  float result;
  float expected;
  unsigned char b[] = {207, 126, 93, 111};
  memcpy(&expected, &b, 4);
  int error = s21_from_decimal_to_float(val_1, &result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_from_decimal_to_float_test3) {
  s21_decimal val_1 = {{0x9987CE65, 0x14B2E8A1, 0x1B36CEE8, 0x00110000}};
  float result;
  float expected;
  unsigned char b[] = {234, 224, 156, 81};
  memcpy(&expected, &b, 4);
  int error = s21_from_decimal_to_float(val_1, &result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_from_decimal_to_float_test4) {
  s21_decimal val_1 = {{0x79566370, 0x54EA07AB, 0xB8DCA7AA, 0x800C0000}};
  float result;
  float expected;
  unsigned char b[] = {2, 66, 75, 219};
  memcpy(&expected, &b, 4);
  int error = s21_from_decimal_to_float(val_1, &result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_test1) {
  float val = 2;
  s21_decimal *result = NULL;
  int ret = s21_from_float_to_decimal(val, result);
  ck_assert_ptr_eq(result, NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_test2) {
  float val1 = 1.7891289;
  float val2 = 0.0;
  int ret1 = 0;
  int ret2 = 0;
  s21_decimal dec = {0};
  ret2 = s21_from_float_to_decimal(val1, &dec);
  s21_from_decimal_to_float(dec, &val2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_float_eq_tol(val1, val2, 1e-6);
}
END_TEST

START_TEST(test_from_float_to_decimal_test3) {
  float val_1 = 0.9;
  float val_2 = 0.0;
  int ret1 = 0;
  int ret2 = 0;
  s21_decimal val1 = {{0}};
  ret2 = s21_from_float_to_decimal(val_1, &val1);
  s21_from_decimal_to_float(val1, &val_2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_from_float_to_decimal_test4) {
  s21_decimal val1 = {0};
  s21_from_float_to_decimal(-333.22, &val1);
  float result = 0;
  s21_from_decimal_to_float(val1, &result);

  ck_assert_float_eq_tol(result, -333.22, 1e-06);
}
END_TEST

START_TEST(test_from_float_to_decimal_test5) {
  float val_1 = .00000000000000000000000000000000193929383838292;
  s21_decimal result = {{32131, 1231435, 2311, 3121441}};
  int ret1 = s21_from_float_to_decimal(val_1, &result);
  ck_assert_int_eq(ret1, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_test6) {
  float val_1 = powl(2.0, 96);
  s21_decimal result = {{32131, 1231435, 2311, 3121441}};
  int ret1 = s21_from_float_to_decimal(val_1, &result);
  ck_assert_int_eq(ret1, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_test7) {
  float val_1 = -1 * powl(2.0, 96);
  s21_decimal result = {{32131, 1231435, 2311, 3121441}};
  int ret1 = s21_from_float_to_decimal(val_1, &result);
  ck_assert_int_eq(ret1, 1);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("s21_decimal_utils");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_add_fail_manual1);
  tcase_add_test(tc_core, test_add_fail_manual2);
  tcase_add_test(tc_core, test_add_fail_manual3);
  tcase_add_test(tc_core, test_add_fail_manual4);
  tcase_add_test(tc_core, test_add_fail_manual5);
  tcase_add_test(tc_core, test_add_fail_manual6);
  tcase_add_test(tc_core, test_add_fail_manual7);
  tcase_add_test(tc_core, test_add_fail_manual8);
  tcase_add_test(tc_core, test_add_fail_manual9);
  tcase_add_test(tc_core, test_add_fail_manual10);
  tcase_add_test(tc_core, test_add_fail_manual11);
  tcase_add_test(tc_core, test_add_fail_manual12);
  tcase_add_test(tc_core, test_add_fail_manual13);
  tcase_add_test(tc_core, test_add_fail_manual14);
  tcase_add_test(tc_core, test_add_fail_manual15);
  tcase_add_test(tc_core, test_add_fail_manual16);
  tcase_add_test(tc_core, test_add_fail_manual17);

  tcase_add_test(tc_core, test_add1);
  tcase_add_test(tc_core, test_add2);
  tcase_add_test(tc_core, test_add3);
  tcase_add_test(tc_core, test_add4);
  tcase_add_test(tc_core, test_add5);
  tcase_add_test(tc_core, test_add6);
  tcase_add_test(tc_core, test_add7);
  tcase_add_test(tc_core, test_add8);
  tcase_add_test(tc_core, test_add9);
  tcase_add_test(tc_core, test_add10);
  tcase_add_test(tc_core, test_add11);
  tcase_add_test(tc_core, test_add12);
  tcase_add_test(tc_core, test_add13);
  tcase_add_test(tc_core, test_add14);
  tcase_add_test(tc_core, test_add15);

  tcase_add_test(tc_core, test_mul_fail_manual1);
  tcase_add_test(tc_core, test_mul_fail_manual2);
  tcase_add_test(tc_core, test_mul_fail_manual3);
  tcase_add_test(tc_core, test_mul_fail_manual4);
  tcase_add_test(tc_core, test_mul_fail_manual5);
  tcase_add_test(tc_core, test_mul_fail_manual6);
  tcase_add_test(tc_core, test_mul_fail_manual7);
  tcase_add_test(tc_core, test_mul_fail_manual8);
  tcase_add_test(tc_core, test_mul_fail_manual9);
  tcase_add_test(tc_core, test_mul_fail_manual10);
  tcase_add_test(tc_core, test_mul_fail_manual11);
  tcase_add_test(tc_core, test_mul_fail_manual12);
  tcase_add_test(tc_core, test_mul_fail_manual13);
  tcase_add_test(tc_core, test_mul_fail_manual14);
  tcase_add_test(tc_core, test_mul_fail_manual15);
  tcase_add_test(tc_core, test_mul_fail_manual16);
  tcase_add_test(tc_core, test_mul_fail_manual17);

  tcase_add_test(tc_core, test_mul_manual1);
  tcase_add_test(tc_core, test_mul_manual2);
  tcase_add_test(tc_core, test_mul_manual3);
  tcase_add_test(tc_core, test_mul_manual4);
  tcase_add_test(tc_core, test_mul_manual5);
  tcase_add_test(tc_core, test_mul_manual6);
  tcase_add_test(tc_core, test_mul_manual7);
  tcase_add_test(tc_core, test_mul_manual8);
  tcase_add_test(tc_core, test_mul_manual9);
  tcase_add_test(tc_core, test_mul_manual10);

  tcase_add_test(tc_core, test_mul1);
  tcase_add_test(tc_core, test_mul2);
  tcase_add_test(tc_core, test_mul3);
  tcase_add_test(tc_core, test_mul4);
  tcase_add_test(tc_core, test_mul5);

  tcase_add_test(tc_core, test_sub_fail_manual1);
  tcase_add_test(tc_core, test_sub_fail_manual2);
  tcase_add_test(tc_core, test_sub_fail_manual3);
  tcase_add_test(tc_core, test_sub_fail_manual4);
  tcase_add_test(tc_core, test_sub_fail_manual5);
  tcase_add_test(tc_core, test_sub_fail_manual6);
  tcase_add_test(tc_core, test_sub_fail_manual7);
  tcase_add_test(tc_core, test_sub_fail_manual8);
  tcase_add_test(tc_core, test_sub_fail_manual9);
  tcase_add_test(tc_core, test_sub_fail_manual10);
  tcase_add_test(tc_core, test_sub_fail_manual11);
  tcase_add_test(tc_core, test_sub_fail_manual12);
  tcase_add_test(tc_core, test_sub_fail_manual13);
  tcase_add_test(tc_core, test_sub_fail_manual14);
  tcase_add_test(tc_core, test_sub_fail_manual15);
  tcase_add_test(tc_core, test_sub_fail_manual16);
  tcase_add_test(tc_core, test_sub_fail_manual17);

  tcase_add_test(tc_core, test_sub1);
  tcase_add_test(tc_core, test_sub2);
  tcase_add_test(tc_core, test_sub3);
  tcase_add_test(tc_core, test_sub4);
  tcase_add_test(tc_core, test_sub5);
  tcase_add_test(tc_core, test_sub6);
  tcase_add_test(tc_core, test_sub7);
  tcase_add_test(tc_core, test_sub8);
  tcase_add_test(tc_core, test_sub9);
  tcase_add_test(tc_core, test_sub10);

  tcase_add_test(tc_core, test_div_fail_manual1);
  tcase_add_test(tc_core, test_div_fail_manual2);
  tcase_add_test(tc_core, test_div_fail_manual3);
  tcase_add_test(tc_core, test_div_fail_manual4);
  tcase_add_test(tc_core, test_div_fail_manual5);
  tcase_add_test(tc_core, test_div_fail_manual6);
  tcase_add_test(tc_core, test_div_fail_manual7);
  tcase_add_test(tc_core, test_div_fail_manual8);
  tcase_add_test(tc_core, test_div_fail_manual9);
  tcase_add_test(tc_core, test_div_fail_manual10);
  tcase_add_test(tc_core, test_div_fail_manual11);
  tcase_add_test(tc_core, test_div_fail_manual12);
  tcase_add_test(tc_core, test_div_fail_manual13);
  tcase_add_test(tc_core, test_div_fail_manual14);
  tcase_add_test(tc_core, test_div_fail_manual15);
  tcase_add_test(tc_core, test_div_fail_manual16);
  tcase_add_test(tc_core, test_div_fail_manual17);

  tcase_add_test(tc_core, test_div_manual1);
  // tcase_add_test(tc_core, test_div_manual2);
  // tcase_add_test(tc_core, test_div_manual3);
  // tcase_add_test(tc_core, test_div_manual4);
  tcase_add_test(tc_core, test_div_manual5);
  tcase_add_test(tc_core, test_div_manual6);
  tcase_add_test(tc_core, test_div_manual7);
  tcase_add_test(tc_core, test_div_manual8);
  tcase_add_test(tc_core, test_div_manual9);
  // tcase_add_test(tc_core, test_div_manual10);
  // tcase_add_test(tc_core, test_div_manual11);
  // tcase_add_test(tc_core, test_div_manual12);
  // tcase_add_test(tc_core, test_div_manual13);
  // tcase_add_test(tc_core, test_div_manual14);
  // tcase_add_test(tc_core, test_div_manual15);

  tcase_add_test(tc_core, test_div1);
  tcase_add_test(tc_core, test_div2);
  tcase_add_test(tc_core, test_div3);
  tcase_add_test(tc_core, test_div4);
  // tcase_add_test(tc_core, test_div5);
  // tcase_add_test(tc_core, test_div6);
  tcase_add_test(tc_core, test_div7);
  tcase_add_test(tc_core, test_div8);
  tcase_add_test(tc_core, test_div9);
  // tcase_add_test(tc_core, test_div10);

  tcase_add_test(tc_core, test_comp_is_greater_1);
  tcase_add_test(tc_core, test_comp_is_greater_2);
  tcase_add_test(tc_core, test_comp_is_greater_3);
  tcase_add_test(tc_core, test_comp_is_greater_or_equal_1);
  tcase_add_test(tc_core, test_comp_is_greater_or_equal_2);
  tcase_add_test(tc_core, test_comp_is_greater_or_equal_3);
  tcase_add_test(tc_core, test_comp_is_less_1);
  tcase_add_test(tc_core, test_comp_is_less_2);
  tcase_add_test(tc_core, test_comp_is_less_3);
  tcase_add_test(tc_core, test_comp_is_less_or_equal_1);
  tcase_add_test(tc_core, test_comp_is_less_or_equal_2);
  tcase_add_test(tc_core, test_comp_is_less_or_equal_3);
  tcase_add_test(tc_core, test_comp_is_equal_1);
  tcase_add_test(tc_core, test_comp_is_equal_2);
  tcase_add_test(tc_core, test_comp_is_equal_3);
  tcase_add_test(tc_core, test_comp_is_not_equal_1);
  tcase_add_test(tc_core, test_comp_is_not_equal_2);
  tcase_add_test(tc_core, test_comp_is_not_equal_3);

  tcase_add_test(tc_core, test_truncate_fail1);
  tcase_add_test(tc_core, test_truncate_fail2);
  tcase_add_test(tc_core, test_truncate_fail3);
  tcase_add_test(tc_core, test_truncate_fail4);
  tcase_add_test(tc_core, test_truncate_fail5);
  tcase_add_test(tc_core, test_truncate_fail6);
  tcase_add_test(tc_core, test_truncate_fail7);
  tcase_add_test(tc_core, test_truncate_fail8);
  tcase_add_test(tc_core, test_truncate_fail9);
  tcase_add_test(tc_core, test_truncate_ok1);
  tcase_add_test(tc_core, test_truncate_ok2);
  tcase_add_test(tc_core, test_truncate_ok3);
  tcase_add_test(tc_core, test_truncate_ok4);
  tcase_add_test(tc_core, test_truncate_ok5);

  tcase_add_test(tc_core, test_round_fail1);
  tcase_add_test(tc_core, test_round_fail2);
  tcase_add_test(tc_core, test_round_fail3);
  tcase_add_test(tc_core, test_round_fail4);
  tcase_add_test(tc_core, test_round_fail5);
  tcase_add_test(tc_core, test_round_fail6);
  tcase_add_test(tc_core, test_round_fail7);
  tcase_add_test(tc_core, test_round_fail8);
  tcase_add_test(tc_core, test_round_fail9);
  tcase_add_test(tc_core, test_round_ok1);
  tcase_add_test(tc_core, test_round_ok2);
  tcase_add_test(tc_core, test_round_ok3);
  tcase_add_test(tc_core, test_round_ok4);
  tcase_add_test(tc_core, test_round_ok5);

  tcase_add_test(tc_core, test_negate_fail1);
  tcase_add_test(tc_core, test_negate_fail2);
  tcase_add_test(tc_core, test_negate_fail3);
  tcase_add_test(tc_core, test_negate_fail4);
  tcase_add_test(tc_core, test_negate_fail5);
  tcase_add_test(tc_core, test_negate_fail6);
  tcase_add_test(tc_core, test_negate_fail7);
  tcase_add_test(tc_core, test_negate_fail8);
  tcase_add_test(tc_core, test_negate_fail9);
  tcase_add_test(tc_core, test_negate_ok1);
  tcase_add_test(tc_core, test_negate_ok2);
  tcase_add_test(tc_core, test_negate_ok3);
  tcase_add_test(tc_core, test_negate_ok4);
  tcase_add_test(tc_core, test_negate_ok5);

  tcase_add_test(tc_core, test_floor_fail1);
  tcase_add_test(tc_core, test_floor_fail2);
  tcase_add_test(tc_core, test_floor_fail3);
  tcase_add_test(tc_core, test_floor_fail4);
  tcase_add_test(tc_core, test_floor_fail5);
  tcase_add_test(tc_core, test_floor_fail6);
  tcase_add_test(tc_core, test_floor_fail7);
  tcase_add_test(tc_core, test_floor_fail8);
  tcase_add_test(tc_core, test_floor_fail9);
  tcase_add_test(tc_core, test_floor_ok1);
  tcase_add_test(tc_core, test_floor_ok2);
  tcase_add_test(tc_core, test_floor_ok3);
  tcase_add_test(tc_core, test_floor_ok4);
  tcase_add_test(tc_core, test_floor_ok5);

  tcase_add_test(tc_core, test_from_int_to_decimal1);
  tcase_add_test(tc_core, test_from_int_to_decimal2);
  tcase_add_test(tc_core, test_from_int_to_decimal3);
  tcase_add_test(tc_core, test_from_decimal_to_int_test1);
  tcase_add_test(tc_core, test_from_decimal_to_int_test2);
  tcase_add_test(tc_core, test_from_decimal_to_int_test3);
  tcase_add_test(tc_core, test_from_decimal_to_int_test4);
  tcase_add_test(tc_core, test_from_decimal_to_int_test5);
  tcase_add_test(tc_core, test_from_decimal_to_float_test1);
  tcase_add_test(tc_core, test_from_decimal_to_float_test2);
  tcase_add_test(tc_core, test_from_decimal_to_float_test3);
  tcase_add_test(tc_core, test_from_decimal_to_float_test4);
  tcase_add_test(tc_core, test_from_float_to_decimal_test1);
  tcase_add_test(tc_core, test_from_float_to_decimal_test2);
  tcase_add_test(tc_core, test_from_float_to_decimal_test3);
  tcase_add_test(tc_core, test_from_float_to_decimal_test4);
  tcase_add_test(tc_core, test_from_float_to_decimal_test5);
  tcase_add_test(tc_core, test_from_float_to_decimal_test6);
  tcase_add_test(tc_core, test_from_float_to_decimal_test7);

  suite_add_tcase(suite, tc_core);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_VERBOSE);

  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failures == 0) ? 0 : 1;
}