#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "secondary_functions.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int rez = 0;
  if (dst) {
    // Проверяем, является ли src отрицательным
    int is_negative = src < 0 ? 1 : 0;

    // Преобразуем src в абсолютное значение
    int abs_src = abs(src);

    // Записываем результат в массив bits структуры s21_decimal
    dst->bits[0] = abs_src;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    dst->bits[3] |= is_negative << 31;
  } else {
    rez = 1;
  }

  return rez;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int rez = 0;
  s21_decimal temp;  // для хранения усеченного числа
  s21_remove(src,
             &temp);  // Усекаем исходное число src и сохраняем результат в temp
  if (((unsigned)temp.bits[0] < 0x80000000 ||
       ((unsigned)temp.bits[0] == 0x80000000 && take_bit(temp.bits[3], 31)))) {
    if (dst) {
      *dst = temp.bits[0];
      if (take_bit(src.bits[3], 31)) {
        *dst = -*dst;
      }
    } else {
      rez = 1;
    }
  } else {
    if (dst) *dst = 0;
    rez = 1;
  }

  return rez;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int rez = 0;
  if (dst) {
    *dst = 0.0;
    // с 0 по 96 хранится наша мантиса
    //  с 96+16 по 96+23 бит лежит коэф. масштабирования
    //  в этом цикле получим значение коэф
    int scale = 0;
    scale = get_scale(src);

    // переводим биты src в десятичное значение
    //  значения float представляются в виде 2^i
    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i)) {
        *dst += pow(2, i);
      }
    }
    // ставим запятую где нам нужно
    *dst /= pow(10, scale);
    // если последний бит(127) равен 1-число отрицательное
    if (get_bit(src, 127)) {
      *dst = *dst * (-1);
    }
  } else {
    rez = 1;
  }

  return rez;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int rez = 0;
  // s21_decl_to_zero(dst);
  if (fabs(src) < powl(10.0, -1 * 28)) {
    rez = 1;
  } else if (src >= powl(2.0, 96)) {
    rez = 1;
  } else if (src <= -1 * (powl(2.0, 96))) {
    rez = 1;
  } else if (dst == NULL) {
    rez = 1;
  } else {
    s21_decl_to_zero(dst);
    int scale = 0;
    // если число отрицательное, 127 бит = 1
    if (src < 0.0) {
      s21_set_sign(dst, 1);
    }

    // абсолютное значение long double
    src = fabsl(src);
    // цикл выполняется если целая часть равна 0(пример 0.000023424124)
    //  выполняется до 2.34...
    for (; !(int)src && scale < 28; src *= 10) {
      scale++;
    }
    int i = 0;
    // избавляемся от дробной части, но не более 7 знаков
    for (; src < powl(2.0, 96) && scale < 28 && i < 7; i++) {
      src *= (long double)10.0;
      scale++;
    }
    // перевод в двоичную систему, если есть остаток этот бит 1, иначе 0
    for (i = 0; src >= powl(10.0, -1 * (7 + 1)) && i < 96; i++) {
      src = floorl(src) / 2;
      // проверяем есть ли остаток, если есть то бит принимает значение 1
      if (src - floorl(src) > powl(10.0, -1 * (7 + 1))) {
        s21_set_bit(dst, i, 1);
      }
    }

    s21_set_scale(dst, scale);
  }

  return rez;
}
