/*

#include "secondary_functions.h"

// void print_decimal_2(s21_decimal res) {
//   for (int i = 3; i >= 0; i--) {  // не удалять це вывод в двоичной
//     for (int ii = 7; ii >= 0; ii--) {
//       for (int iii = 3; iii >= 0; iii--) {
//         printf("%d", INT_GET_BIT(res.bits[i], ((ii * 4) + iii)));
//       }
//       printf(" ");
//     }
//     printf("\n");
//   }
// }

// void print_decimal_2_str(s21_decimal res) {
//   for (int i = 3; i > -1; i--) {  // не удалять це вывод в двоичной
//     for (int ii = 7; ii > -1; ii--) {
//       for (int iii = 3; iii > -1; iii--) {
//         printf("%d", INT_GET_BIT(res.bits[i], ((ii * 4) + iii)));
//       }
//     }
//   }
//   printf("\n");
// }

<<<<<<< HEAD
// 0b10000000 00001010 0000000000000000
/////10000000 00011100 0000000000000000
// s21_decimal f1 = {{21, 0, 0, 0b0 0000000 00001010 0000000000000000}};

int main() {
  unsigned long long norm =
      0b1111111111111111111111111111111111111111111111111111111111111111 /
      0b10101010101010101010101010101010;
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  print_decimal_2_str(decimal1);
  print_decimal_2_str(decimal2);
  // printf("\n\n%d\n\n", s21_is_greater(f1, f2));
  s21_decimal res = {{0, 0, 0, 0}};
  // printf("\nded\n");
  // int d = s21_mul(f1, f2, &res);
  int error = s21_div(decimal1, decimal2, &res);
  // secondary_decimal res_sub = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  // secondary_decimal ostat = div_secondary(convert(f1), convert(f2),
  // &res_sub); res = add_and_sub(f1,f2,-1); res = reconvert(res_sub);
  //  s21_negate(f1, &res);
  printf("1 %u\n2 %u\n3 %u\n4 %u\n5 %u\n", res.bits[0], res.bits[1],
         res.bits[2], modif(res), INT_GET_BIT(res.bits[3], 31));
  // print_decimal_2(res);

  print_decimal_2_str(res);
  printf("\n\n\n");
  printf("%llu\n", norm);
  printf("Error - %d", error);
  // print_decimal_2(reconvert(ostat));
  return 0;
}


 */
