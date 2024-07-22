#include <stdio.h>

#include "s21_decimal.h"
/*Здесь задан размер нашей вспомогательной струкры
 */
#define TMP_DEC_SIZE 7
/*Устанавливает 1 в указанной позции int
 * в скобках - int(где ставим 1), int(какой бит)
 */
#define INT_SET_BIT(var, bit) *(unsigned int *)(&var) |= (1 << bit)

// #define INT_CLR_BIT(var, bit) *(unsigned int *)(&var) &= ~(1 << bit)
/*Получаем значения определенного бита
 * в скобках - int(где ищем), int(какой бит)
 */
#define INT_GET_BIT(var, bit) (((*(unsigned int *)(&var)) >> bit) & 0x01)
// #define INT_XOR_BIT(var, bit) *(unsigned int *)(&var) ^= (1 << bit)

/* Данную структуру используем для хранения результата арифметических
 * операций, чтобы в даньнейшем уменьшить результат до s21_decimal(3 инта)
 * Состав:
 * int gigabits[] - интов в 2 раза больше чем в decimal + 1 инт для
 * отслеживания переполнения храним значащее число unsigned char modif -
 * храним коэффициента масштабирования unsigned char sign - храним знак 1
 * или 0
 */
typedef struct {
  int gigabits[TMP_DEC_SIZE];
  int modif;
  int sign;
} secondary_decimal;

/* На вход получает структуру s21_decimal
 * Возвращает uchar число(8 бит) хранящее коэффициента масштабирования
 * С помощью смещения int[3] на 8 и 24 бит получаем положение запятой
 */
unsigned char modif(s21_decimal value);

/* Данная ф-ция выравнивает степени числа
 * число с меньшей степенью десятки домножается на 10 до большей
 * Используем для арифметических ф-ций чтобы дальше работать с числами как с
 * целыми выход - два числа промежуточного типа выход - сколько раз домножили на
 * 10
 */
int equalization(secondary_decimal *v1, secondary_decimal *v2);

/* Используем данную функцию чтобы сравнять коэфициент масштабирования
 * На вход получаем указатель на структуру secondary_decimal
 * Число умножаем на 10, складывая в помежуточный буффер 64 бита,
 * переполнение переносим на следующий int. Для корректного хранения int в
 * long int, запихиваем в uint сначала. Также modif у промежуточной
 * структуры увеличивается на 1. На выход выдает 1, можно использовать для
 * счетчика;
 */
int multiply_10(secondary_decimal *result);

/* Дeление на 10 для округления числа
 * Вход - число промежуточного типа
 * Выход - остаток(int)
 * ВАЖНО!!! Передаем числа строго больше 10
 */
int division_10(secondary_decimal *result);

/*На вход структура s21_decimal
 * записываем все значения в новую структуру secondary_decimal
 * На выход новая структура secondary_decimal
 */
secondary_decimal convert(s21_decimal x);
/*На вход структура secondary_decimal
 * записываем все значения в новую структуру secondary_decimal
 * На выход новая структура s21_decimal
 *
 * ВАЖНО!!! Обработки переполнения нет нужно обрабатывать до этой ф-ции
 */
s21_decimal reconvert(secondary_decimal x);

/* В данной ф-ции реализовано деление промежуточного типа на промежуточный тип
 * Вход - делимое, делитель(обязательно меньше делимого), сыллка на храние
 * результата На выход подается остаток от деления ВАЖНО!!! Не обрабатывает
 * запятую
 */
secondary_decimal div_secondary(secondary_decimal v1, secondary_decimal v2,
                                secondary_decimal *result);

/* Сдвиг промежуточного типа влево на х бит
 * вход - сдвигаемое число secondary_decimal
 * выход - результат сдвига secondary_decimal
 */
secondary_decimal shift_to_left(secondary_decimal value, int x);

/* Сдвиг промежуточного типа вправо на х бит
 * вход - сдвигаемое число secondary_decimal
 * выход - результат сдвига secondary_decimal
 */
secondary_decimal shift_to_right(secondary_decimal value, int x);

/* Поиск старшего бита в secondary_decimal
 * вход - число secondary_decimal
 * выход - позиция старшего бита
 */
int first_bit(secondary_decimal value);

/* Сравнение secondary_decimal чисел
 * вход - два secondary_decimal числа
 * выход:
 * 1 - v1 больше или равно v2
 * 0 - v2 больше v1
 */
int div_comparision(secondary_decimal v1, secondary_decimal v2);

/* Сложение и вычитание реализованно сложением каждого бита чисел по очереди и
 * переносом переполнения/озанимание бита на следующий.
 * вход - 2 decimal слагаемых и int(1 - сложение, -1 вычитание)
 * выход - decimal структура в кот.записан результат
 */
secondary_decimal add_and_sub_calculation(secondary_decimal v1,
                                          secondary_decimal v2, int x);
/* Приводит число к нормальному виду
 * Проверяет на переполнение, код ошибки - 1
 * Проверяет на малое число, код ошибки -2
 * Делает ноль положительным
 */
int normalization(secondary_decimal value, s21_decimal *result);

/* Данная ф-ция перекладывает входящие decimal в промежуточный тип и уравнивает
 * обе переменные до одинакового коэфициента масштабировани с помощью умножения
 * на 10.
 * Далее передаем в обработки промежуточных типов
 */
secondary_decimal add_and_sub(s21_decimal value_1, s21_decimal value_2, int x);

/*Проверяет четность value, если четное, то возвращает 1, если нечетное, то 0.
 */
int s21_decimal_is_even(s21_decimal value);

/*Обнуляет value.
 */
void s21_clear_decimal(s21_decimal *value);

/*Проверяет правильно ли заполнен служебный бит, если да, возвращает 0, если
 *ошибка, то возвращает 1
 */
int is_it_normal(s21_decimal dec);

/* Проверяет равен ли secondary_decimal 0
 * Вход - secondary_decimal
 * Выход - нет(0), да(1)
 */
int decimal_is_null(secondary_decimal x);

int take_bit(int x, int position);
/*
 * Получаем значение бита 0 или 1
 * принимает int из структуры s21_decimal и позицию
 */

int get_bit(s21_decimal dec, int index);
/*
 * Возвращаем значение нужного бита(0 или 1)
 * принимает структуру decimal и позицию
 */
int get_scale(s21_decimal dec);
/*
 * Возвращаем значение коэф-а масштабирования
 * принимает структуру s21_decimal
 */

void s21_set_scale(s21_decimal *decl, int scale);
/*
 * Устанавливаем нужный коэф. масштабирования
 * принимает структуру s21_decimal и значение коэф-а масштабирования
 */

int s21_remove(s21_decimal value, s21_decimal *result);
/*
 * Переводим decimal в int
 * принимает структуру s21_decimal и записывает в result
 * возвращает 0 если прошло успешно
 */

void s21_set_bit(s21_decimal *decl, int index, int bit);
/*
 * Устанавливаем значение нужного бита
 * принимает структуру s21_decimal и индекс index бита, значение bit бита
 */

void s21_decl_to_zero(s21_decimal *decl);
/*
 * Устанавливаем значение битов в 0
 * принимает структуру s21_decimal
 */

// функция для установки бита, который отвечает за знак числа
void s21_set_sign(s21_decimal *decl, int sign);
/*
 *
 * функция для установки бита, который отвечает за знак числа
 */
