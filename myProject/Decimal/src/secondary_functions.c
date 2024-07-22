#include "secondary_functions.h"

unsigned char modif(s21_decimal value) {
  int result = value.bits[3] << 8;
  return (result >> 24);
}

int equalization(secondary_decimal *v1, secondary_decimal *v2) {
  int pow_10 = 0;
  secondary_decimal *g;
  if (v1->modif > v2->modif) {
    g = v2;
  } else if (v1->modif < v2->modif) {
    g = v1;
  }
  while (v2->modif != v1->modif) {
    pow_10 += multiply_10(g);
  }
  return pow_10;
}

int division_10(secondary_decimal *result) {
  secondary_decimal buff = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  secondary_decimal value_ten = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};
  secondary_decimal rem = div_secondary(*result, value_ten, &buff);
  buff.modif = result->modif;
  buff.sign = result->sign;
  *result = buff;
  result->modif--;
  return rem.gigabits[0];
}

int multiply_10(secondary_decimal *result) {
  unsigned long long buff1[TMP_DEC_SIZE];
  for (int i = 0; i < TMP_DEC_SIZE; i++) {
    buff1[i] = (unsigned int)result->gigabits[i];
    buff1[i] = buff1[i] << 1;
    buff1[i] = buff1[i] + (buff1[i] << 2);
  }
  for (int i = 0; i < (TMP_DEC_SIZE - 1); i++) {
    buff1[i + 1] = buff1[i + 1] + (buff1[i] >> 32);
    result->gigabits[i] = buff1[i] & 0xFFFFFFFF;
  }
  result->gigabits[TMP_DEC_SIZE - 1] = buff1[TMP_DEC_SIZE - 1] & 0xFFFFFFFF;
  result->modif++;
  return 1;
}

secondary_decimal convert(s21_decimal x) {
  secondary_decimal result;
  result.gigabits[0] = (unsigned int)x.bits[0];
  result.gigabits[1] = (unsigned int)x.bits[1];
  result.gigabits[2] = (unsigned int)x.bits[2];
  result.gigabits[3] = 0;
  result.gigabits[4] = 0;
  result.gigabits[5] = 0;
  result.gigabits[6] = 0;
  result.modif = modif(x);
  result.sign = INT_GET_BIT(x.bits[3], 31);
  return result;
}

s21_decimal reconvert(secondary_decimal x) {
  s21_decimal result;
  result.bits[0] = (unsigned int)x.gigabits[0];
  result.bits[1] = (unsigned int)x.gigabits[1];
  result.bits[2] = (unsigned int)x.gigabits[2];
  result.bits[3] = x.sign << 15;
  result.bits[3] |= x.modif;
  result.bits[3] = result.bits[3] << 16;
  return result;
}

secondary_decimal div_secondary(secondary_decimal v1, secondary_decimal v2,
                                secondary_decimal *result) {
  int new_length = first_bit(v1) - first_bit(v2);
  for (int i = new_length; i >= 0; i--) {
    secondary_decimal buff_to_right = shift_to_right(v1, i);
    if (div_comparision(buff_to_right, v2)) {
      secondary_decimal buff_to_left = shift_to_left(v2, i);
      v1 = add_and_sub_calculation(v1, buff_to_left, -1);
      INT_SET_BIT(result->gigabits[i / 32], i % 32);
    }
  }
  return v1;
}

secondary_decimal add_and_sub_calculation(secondary_decimal v1,
                                          secondary_decimal v2, int x) {
  secondary_decimal res = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  int superfluous = 0;
  for (int i = 0; i < TMP_DEC_SIZE; i++) {
    for (int j = 0; j < 32; j++) {
      int r = INT_GET_BIT(v1.gigabits[i], j) +
              (INT_GET_BIT(v2.gigabits[i], j) * x) + superfluous;
      if ((r > 1) || ((r < 0))) {
        r += (2 * (x * -1));
        superfluous = x;
      } else {
        superfluous = 0;
      }
      res.gigabits[i] |= (r << j);
    }
  }
  return res;
}

secondary_decimal shift_to_left(secondary_decimal value, int x) {
  secondary_decimal buff_result = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  unsigned long long buff[TMP_DEC_SIZE] = {0, 0, 0, 0, 0, 0};
  buff[0] = (unsigned int)value.gigabits[0];
  buff[0] = (buff[0] << (x % 32));
  buff_result.gigabits[x / 32] = (buff[0] & 0xFFFFFFFF);
  for (int j = 1; j < TMP_DEC_SIZE - (x / 32); j++) {
    buff[j] = (unsigned int)value.gigabits[j];
    buff[j] = buff[j] << (x % 32);
    buff_result.gigabits[j + (x / 32)] = (unsigned int)(buff[j - 1] >> 32) +
                                         (unsigned int)(buff[j] & 0xFFFFFFFF);
  }
  return buff_result;
}

secondary_decimal shift_to_right(secondary_decimal value, int x) {
  secondary_decimal buff_result = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  unsigned long long buff[TMP_DEC_SIZE + 1] = {0, 0, 0, 0, 0, 0, 0};
  for (int j = TMP_DEC_SIZE - 1; j >= (0 + (x / 32)); j--) {
    buff[j] = (unsigned int)value.gigabits[j];
    buff[j] = buff[j] << (32 - (x % 32));
    buff_result.gigabits[j - (x / 32)] =
        ((buff[j] >> 32) + (buff[j + 1] & 0xFFFFFFFF));
  }
  return buff_result;
}

int first_bit(secondary_decimal value) {
  int result = 0;
  for (int num = TMP_DEC_SIZE - 1; num >= 0; num--) {
    for (int i = 31; i >= 0; i--) {
      if (INT_GET_BIT(value.gigabits[num], i)) {
        result = (num * 32) + i + 1;
        i = -1;
        num = -1;
      }
    }
  }
  return result;
}

int div_comparision(secondary_decimal v1, secondary_decimal v2) {
  int result = 1;
  for (int num = TMP_DEC_SIZE - 2; num >= 0; num--) {
    for (int i = 31; i >= 0; i--) {
      if (INT_GET_BIT(v1.gigabits[num], i) < INT_GET_BIT(v2.gigabits[num], i)) {
        result = 0;
        i = -1;
        num = -1;
      } else if (INT_GET_BIT(v1.gigabits[num], i) >
                 INT_GET_BIT(v2.gigabits[num], i)) {
        i = -1;
        num = -1;
      }
    }
  }
  return result;
}

int normalization(secondary_decimal value, s21_decimal *result) {
  int error = 0;
  secondary_decimal one_no_global = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  if (decimal_is_null(value)) {
    value.sign = 0;
  } else {
    while ((value.modif > 0 &&
            ((value.gigabits[3] != 0) || (value.gigabits[4] != 0) ||
             (value.gigabits[5] != 0) || (value.gigabits[6] != 0))) ||
           (value.modif > 28)) {
      int rem = division_10(&value);
      if ((rem >= ((int)(6 - INT_GET_BIT(value.gigabits[0], 0)))) &&
          (rem != 0)) {
        secondary_decimal buff = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
        buff = add_and_sub_calculation(value, one_no_global, 1);
        buff.modif = value.modif;
        buff.sign = value.sign;
        value = buff;
      }
    }
    if (decimal_is_null(value)) {
      error = 2;
    } else if ((value.gigabits[3] != 0) || (value.gigabits[4] != 0) ||
               (value.gigabits[5] != 0) || (value.gigabits[6] != 0)) {
      if (value.sign) {
        error = 2;
      } else {
        error = 1;
      }
    } else if (value.modif) {
      secondary_decimal buff = value;
      while ((!division_10(&buff)) && value.modif) {
        value = buff;
      }
    }
  }
  if (!error) {
    *result = reconvert(value);
  }
  return error;
}

int decimal_is_null(secondary_decimal x) {
  int result = 0;
  if ((x.gigabits[0] == 0) && (x.gigabits[1] == 0) && (x.gigabits[2] == 0) &&
      (x.gigabits[3] == 0) && (x.gigabits[4] == 0) && (x.gigabits[5] == 0) &&
      (x.gigabits[6] == 0)) {
    result = 1;
  }
  return result;
}

secondary_decimal add_and_sub(s21_decimal value_1, s21_decimal value_2, int x) {
  secondary_decimal v1 = convert(value_1);
  secondary_decimal v2 = convert(value_2);
  equalization(&v1, &v2);
  secondary_decimal res = add_and_sub_calculation(v1, v2, x);
  res.modif = v1.modif;
  res.sign = v1.sign;
  return res;
}

int is_it_normal(s21_decimal dec) {
  int res = 0;
  // проверяем что все биты 0-15 и 24-30 равны 0
  for (int i = 0; i != 16; i++) {
    if (INT_GET_BIT(dec.bits[3], i) != 0) {
      res = 1;
    }
  }
  for (int i = 24; i != 31; i++) {
    if (INT_GET_BIT(dec.bits[3], i) != 0) {
      res = 1;
    }
  }
  if (modif(dec) > 28) {
    res = 1;
  }
  return res;
}

void s21_set_bit(s21_decimal *decl, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 1) {
    decl->bits[num_int] |= (1u << num_bit);
  } else {
    decl->bits[num_int] &= (~((1u) << num_bit));
  }
  return;
}

void s21_set_scale(s21_decimal *decl, int scale) {
  for (int i = 96 + 16; i < 96 + 23; i++) {
    s21_set_bit(decl, i, scale & 1);
    scale >>= 1;
  }
}

int s21_remove(s21_decimal value, s21_decimal *result) {
  int scale = get_scale(value);

  // Устанавливаем масштаб числа value в 0 для удаления дробной части
  s21_set_scale(&value, 0);

  // Уменьшаем число value, удаляя scale десятичных разрядов
  for (int i = 0; i < scale; i++) {
    // Простое деление на 10 для удаления дробной части
    unsigned int remainder = 0;  // Переменная для хранения остатка от деления

    for (int i = 3 - 1; i >= 0; i--) {
      // Собираем число из текущего элемента и остатка от предыдущего деления
      unsigned long int tmp =
          (unsigned long int)remainder << 32 | ((unsigned *)value.bits)[i];

      // Делим число на 10 и записываем результат обратно в массив
      ((unsigned *)value.bits)[i] = tmp / 10;

      // Обновляем значение остатка для следующей итерации
      remainder = tmp % 10;
    }
  }

  if (result != NULL) {
    // Копируем значения массива
    for (int i = 0; i < 4; ++i) {
      result->bits[i] = value.bits[i];
    }
  }

  return 0;
}

int take_bit(int x, int position) {
  x = x << (31 - position);
  return ((x >> 31) * -1);
}

int get_bit(s21_decimal dec, int index) {
  // определяем индекс в котором находится нужный бит
  int num_int = index / 32;
  // в каком бите находится нужный бит bits[num_int]
  int num_bit = index % 32;
  // возвращаем значение нужного бита(0 или 1)
  return (dec.bits[num_int] & (1u << num_bit)) >> num_bit;
}
int get_scale(s21_decimal dec) {
  int scale = 0;
  for (int i = 96 + 23; i >= 96 + 16; i--) {
    scale <<= 1;
    scale |= get_bit(dec, i);
  }
  return scale;
}

void s21_decl_to_zero(s21_decimal *decl) {
  for (int i = 0; i < 128; ++i) {
    s21_set_bit(decl, i, 0);
  }
}

void s21_set_sign(s21_decimal *decl, int sign) {
  s21_set_bit(decl, 127, sign);
  return;
}