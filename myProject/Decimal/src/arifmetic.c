#include "secondary_functions.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result && !(is_it_normal(value))) {
    error = 0;
    *result = value;
    if (INT_GET_BIT(value.bits[3], 31) == 0) {
      result->bits[3] |= (0b10000000000000000000000000000000);
    } else {
      result->bits[3] &= 0x7FFFFFFF;
    }
  }
  return error;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 4;
  if (result && !(is_it_normal(value_1)) && !(is_it_normal(value_2))) {
    error = 0;
    if (INT_GET_BIT(value_2.bits[3], 31) == INT_GET_BIT(value_1.bits[3], 31)) {
      error = normalization(add_and_sub(value_1, value_2, 1), result);
    } else if (INT_GET_BIT(value_1.bits[3], 31) >
               INT_GET_BIT(value_2.bits[3], 31)) {
      s21_negate(value_1, &value_1);
      error = s21_sub(value_2, value_1, result);
    } else {
      s21_negate(value_2, &value_2);
      error = s21_sub(value_1, value_2, result);
    }
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 4;
  if (result && !(is_it_normal(value_1)) && !(is_it_normal(value_2))) {
    error = 0;
    if (INT_GET_BIT(value_2.bits[3], 31) == INT_GET_BIT(value_1.bits[3], 31)) {
      if (s21_is_greater(value_1, value_2)) {
        error = normalization(add_and_sub(value_1, value_2, -1), result);
      } else {
        s21_negate(value_2, &value_2);
        INT_SET_BIT(value_2.bits[3], 31);
        error = normalization(add_and_sub(value_2, value_1, -1), result);
      }
    } else if (INT_GET_BIT(value_1.bits[3], 31) >
               INT_GET_BIT(value_2.bits[3], 31)) {
      s21_negate(value_2, &value_2);
      error = s21_add(value_1, value_2, result);
    } else {
      s21_negate(value_2, &value_2);
      error = s21_add(value_1, value_2, result);
    }
  }
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 4;
  if (result && !(is_it_normal(value_1)) && !(is_it_normal(value_2))) {
    secondary_decimal buff = convert(value_1);
    secondary_decimal res = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    error = 0;
    for (int i = 0; i < 3; i++) {
      for (int ii = 0; ii < 32; ii++) {
        if (INT_GET_BIT(value_2.bits[i], ii)) {
          secondary_decimal term = shift_to_left(buff, (i * 32 + ii));
          res = add_and_sub_calculation(res, term, 1);
          if (res.gigabits[6] != 0) {
            i = 3;
            ii = 32;
          }
        }
      }
    }
    if (res.gigabits[6] == 0) {
      res.modif = modif(value_1) + modif(value_2);
    }
    res.sign =
        (INT_GET_BIT(value_1.bits[3], 31) ^ INT_GET_BIT(value_2.bits[3], 31));
    error = normalization(res, result);
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 4;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    error = 3;
  } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[2] == 0) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;
  } else if (result && !(is_it_normal(value_1)) && !(is_it_normal(value_2))) {
    secondary_decimal v1 = convert(value_1);
    secondary_decimal v2 = convert(value_2);
    while (v2.modif > 0) {
      if (v1.modif) {
        v1.modif--;
      } else {
        multiply_10(&v1);
        v1.modif--;
      }
      v2.modif--;
    }
    secondary_decimal buff_result = {{0, 0, 0, 0, 0, 0, 0}, v1.modif, 0};
    if (first_bit(v1) < first_bit(v2)) {
      error = 2;
    } else {
      error = 0;
      secondary_decimal rem = div_secondary(v1, v2, &buff_result);
      while (v1.modif <= 28) {
        multiply_10(&v1);
        multiply_10(&rem);
      }
    }
    buff_result.sign =
        (INT_GET_BIT(value_1.bits[3], 31) ^ INT_GET_BIT(value_2.bits[3], 31));
    error = normalization(buff_result, result);
  }
  return error;
}
