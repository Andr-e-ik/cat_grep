#include "secondary_functions.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = OK_rounders;
  if (!result) {  // if NULL
    code = calculation_error_rounders;
  } else if (is_it_normal(value)) {  // неправильные decimal
    code = calculation_error_rounders;
  } else {
    secondary_decimal res = convert(value);
    while (res.modif > 0) {
      division_10(&res);
    }
    code = normalization(res, result);
  }
  return code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = OK_rounders;
  if (!result) {  // if NULL
    code = calculation_error_rounders;
  } else if (is_it_normal(value)) {  // неправильные decimal
    code = calculation_error_rounders;
  } else {
    secondary_decimal res = convert(value);
    int residual = 0;
    while (res.modif > 0) {
      residual = division_10(&res);
    }
    code = normalization(res, result);

    s21_decimal one = {{0b1, 0x0, 0x0, 0x0}};  // 1

    if ((residual == 5 && !(((*result).bits[0] & 1) != 1)) ||
        (residual > 5)) {  // если дробная часть равна 0.5 и целая часть
                           // нечетная или дробная часть больше 0.5
      if (!res.sign) {                  // положительное число
        s21_add(*result, one, result);  // добавляем единичку
      } else {
        s21_sub(*result, one, result);  // вычитаем единичку
      }
    }
  }
  return code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = OK_rounders;
  if (!result) {  // if NULL
    code = calculation_error_rounders;
  } else if (is_it_normal(value)) {  // неправильные decimal
    code = calculation_error_rounders;
  } else {
    secondary_decimal res = convert(value);
    int residual = 0;
    while (res.modif > 0) {
      residual = division_10(&res);
    }
    code = normalization(res, result);

    if ((INT_GET_BIT((*result).bits[3], 31) == 1) &&
        (residual > 0)) {  // если число отрицательное и есть дробная часть
      s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
      s21_sub(*result, one, result);  // вычитаем единичку
    }
  }
  return code;
}