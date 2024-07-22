#include "secondary_functions.h"

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  int res = 0, done = 0;
  int sign1 = INT_GET_BIT(dec1.bits[3], 31);
  int sign2 = INT_GET_BIT(dec2.bits[3], 31);
  // сравниваем знаки
  if (sign1 > sign2) {
    res = 1;
    done = 1;
  } else if (sign1 < sign2) {
    done = 1;
  }
  if (sign1 == 1 && sign2 == 1) {
    s21_negate(dec1, &dec1);
    s21_negate(dec2, &dec2);
    res = s21_is_less(dec2, dec1);
    done = 1;
  }
  // создаем большие децималы, для дальнейшей работы с ними
  secondary_decimal sdec1 = convert(dec1);
  secondary_decimal sdec2 = convert(dec2);
  // сравниваем коэффиценты масштабирования и выравниваем их
  if (modif(dec1) != modif(dec2) && done == 0) {
    equalization(&sdec1, &sdec2);
  }
  // сравниваем беззнаковые инты каждого большого децимала
  for (int i = 6; done == 0 && i >= 0; i--) {
    if ((unsigned int)sdec1.gigabits[i] < (unsigned int)sdec2.gigabits[i]) {
      res = 1;
      done = 1;

    } else if ((unsigned int)sdec1.gigabits[i] >
               (unsigned int)sdec2.gigabits[i]) {
      res = 0;
      done = 1;
    }
  }

  return res;
}

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int res = 0, done = 0;
  int sign1 = INT_GET_BIT(dec1.bits[3], 31);
  int sign2 = INT_GET_BIT(dec2.bits[3], 31);
  if (sign1 > sign2) {
    done = 1;
  } else if (sign1 < sign2) {
    res = 1;
    done = 1;
  }
  if (sign1 == 1 && sign2 == 1) {
    s21_negate(dec1, &dec1);
    s21_negate(dec2, &dec2);
    res = s21_is_greater(dec2, dec1);
    done = 1;
  }
  // создаем большие децималы, для дальнейшей работы с ними
  secondary_decimal sdec1 = convert(dec1);
  secondary_decimal sdec2 = convert(dec2);
  // сравниваем коэффиценты масштабирования и выравниваем их
  if (modif(dec1) != modif(dec2) && done == 0) {
    equalization(&sdec1, &sdec2);
  }
  // сравниваем беззнаковые инты каждого большого децимала
  for (int i = 6; (done == 0) && (i >= 0); i--) {
    if ((unsigned int)sdec1.gigabits[i] > (unsigned int)sdec2.gigabits[i]) {
      res = 1;
      done = 1;
    } else if ((unsigned int)sdec1.gigabits[i] <
               (unsigned int)sdec2.gigabits[i]) {
      res = 0;
      done = 1;
    }
  }

  return res;
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 1;
  // сравниваем знаки
  if (INT_GET_BIT(dec1.bits[3], 31) != INT_GET_BIT(dec2.bits[3], 31)) {
    res = 0;
  } else {
    res = 1;
  }
  // сравниваем кэффиценты масштабирования
  if (res == 0 && modif(dec1) != modif(dec2)) {
    res = 0;
  }
  // сравниваем беззнаковые инты каждого децимала
  for (int i = 2; res != 0 && i >= 0; i--) {
    if ((unsigned int)dec1.bits[i] != (unsigned int)dec2.bits[i]) {
      res = 0;
    }
  }

  return res;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {
  return !(s21_is_equal(dec1, dec2));
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_less(dec1, dec2));
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2));
}