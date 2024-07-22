#include <check.h>
#include <errno.h>

#include "../s21_matrix.h"

START_TEST(s21_create_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_02) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(4, 10, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_03) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_04) {
  int res = 0;

  res = s21_create_matrix(10, 6, NULL);
  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_05) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_06) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_07) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(-1, 12, &A);
  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_08) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(12, -1, &A);
  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_remove_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_02) {
  matrix_t A = {};
  s21_remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(s21_eq_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_matrix_init(1.0, &A);

  s21_create_matrix(3, 2, &B);
  s21_matrix_init(1.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_eq_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_matrix_init(1.0, &A);

  s21_create_matrix(3, 2, &B);
  s21_matrix_init(2.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_matrix_init(1.1234567, &A);

  s21_create_matrix(3, 2, &B);
  s21_matrix_init(1.1234567, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_eq_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_matrix_init(1.1234567, &A);

  s21_create_matrix(3, 2, &B);
  s21_matrix_init(1.1234568, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(0, 2, &A);

  s21_create_matrix(3, 2, &B);
  s21_matrix_init(1.1234568, &B);

  res = s21_eq_matrix(&A, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 2, &A);
  s21_matrix_init(1.1234568, &A);

  s21_create_matrix(3, 2, &B);
  s21_matrix_init(1.1234568, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_sum_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  // s21_isCorrectMatrix(&A);
  s21_matrix_init(1.0, &A);

  s21_create_matrix(4, 4, &B);
  // s21_isCorrectMatrix(&B);
  s21_matrix_init(1.0, &B);

  s21_sum_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 6.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 10.0;
  X.matrix[1][1] = 12.0;
  X.matrix[1][2] = 14.0;
  X.matrix[1][3] = 16.0;
  X.matrix[2][0] = 18.0;
  X.matrix[2][1] = 20.0;
  X.matrix[2][2] = 22.0;
  X.matrix[2][3] = 24.0;
  X.matrix[3][0] = 26.0;
  X.matrix[3][1] = 28.0;
  X.matrix[3][2] = 30.0;
  X.matrix[3][3] = 32.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sum_matrix_02) {
  int res = 0;
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  matrix_t B = {0};
  matrix_t Z = {0};
  res = s21_sum_matrix(&A, &B, &Z);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_sum_matrix_03) {
  int res = 0;
  matrix_t A;
  matrix_t B = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 6, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  res = s21_sum_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(s21_sum_matrix_04) {
  int res = 0;
  matrix_t A;
  matrix_t B = {0};
  s21_create_matrix(4, 4, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  res = s21_sum_matrix(&A, &B, NULL);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_sub_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_matrix_init(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  s21_sub_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = 0.0;
  X.matrix[1][1] = 0.0;
  X.matrix[1][2] = 0.0;
  X.matrix[1][3] = 0.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 0.0;
  X.matrix[2][2] = 0.0;
  X.matrix[2][3] = 0.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 0.0;
  X.matrix[3][2] = 0.0;
  X.matrix[3][3] = 0.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sub_matrix_02) {
  //нужно ли очищать матрицы?
  int res = 0;
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  matrix_t B = {0};
  matrix_t Z = {0};
  res = s21_sub_matrix(&A, &B, &Z);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_sub_matrix_03) {
  //Нужно ли очищать матрицы?
  int res = 0;
  matrix_t A;
  matrix_t B = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 6, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  res = s21_sub_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(s21_sub_matrix_04) {
  int res = 0;
  matrix_t A;
  matrix_t B = {0};
  s21_create_matrix(4, 4, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  res = s21_sub_matrix(&A, &B, NULL);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_mult_number_01) {
  int res = 0;
  double number = 3.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);

  s21_matrix_init(1.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 3.0;
  X.matrix[0][1] = 6.0;
  X.matrix[0][2] = 9.0;
  X.matrix[0][3] = 12.0;
  X.matrix[1][0] = 15.0;
  X.matrix[1][1] = 18.0;
  X.matrix[1][2] = 21.0;
  X.matrix[1][3] = 24.0;
  X.matrix[2][0] = 27.0;
  X.matrix[2][1] = 30.0;
  X.matrix[2][2] = 33.0;
  X.matrix[2][3] = 36.0;
  X.matrix[3][0] = 39.0;
  X.matrix[3][1] = 42.0;
  X.matrix[3][2] = 45.0;
  X.matrix[3][3] = 48.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_02) {
  //нужно ли очищать матрицы?
  int res = 0;
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  matrix_t Z = {0};
  res = s21_mult_number(&A, 3, &Z);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_mult_number_03) {
  int res = 0;
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  s21_matrix_init(1.0, &A);

  res = s21_mult_number(&A, 2, NULL);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_mult_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_matrix_init(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 90.0;
  X.matrix[0][1] = 100.0;
  X.matrix[0][2] = 110.0;
  X.matrix[0][3] = 120.0;
  X.matrix[1][0] = 202.0;
  X.matrix[1][1] = 228.0;
  X.matrix[1][2] = 254.0;
  X.matrix[1][3] = 280.0;
  X.matrix[2][0] = 314.0;
  X.matrix[2][1] = 356.0;
  X.matrix[2][2] = 398.0;
  X.matrix[2][3] = 440.0;
  X.matrix[3][0] = 426.0;
  X.matrix[3][1] = 484.0;
  X.matrix[3][2] = 542.0;
  X.matrix[3][3] = 600.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_matrix_02) {
  //нужно ли очищать матрицы?
  int res = 0;
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  matrix_t B = {0};
  matrix_t Z = {0};
  res = s21_mult_matrix(&A, &B, &Z);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_mult_matrix_03) {
  //Нужно ли очищать матрицы?
  int res = 0;
  matrix_t A;
  matrix_t B = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 6, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(4, 8, &B);
  s21_matrix_init(1.0, &B);

  res = s21_mult_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(s21_mult_matrix_04) {
  int res = 0;
  matrix_t A;
  matrix_t B = {0};
  s21_create_matrix(4, 4, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(4, 4, &B);
  s21_matrix_init(1.0, &B);

  res = s21_mult_matrix(&A, &B, NULL);

  ck_assert_int_eq(res, ERROR_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 2, &A);
  s21_matrix_init(-5.0, &A);

  s21_create_matrix(2, 4, &B);
  s21_matrix_init(1.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = -25.0;
  X.matrix[0][1] = -34.0;
  X.matrix[0][2] = -43.0;
  X.matrix[0][3] = -52.0;
  X.matrix[1][0] = -13.0;
  X.matrix[1][1] = -18.0;
  X.matrix[1][2] = -23.0;
  X.matrix[1][3] = -28.0;
  X.matrix[2][0] = -1.0;
  X.matrix[2][1] = -2.0;
  X.matrix[2][2] = -3.0;
  X.matrix[2][3] = -4.0;
  X.matrix[3][0] = 11.0;
  X.matrix[3][1] = 14.0;
  X.matrix[3][2] = 17.0;
  X.matrix[3][3] = 20.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_transpose_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_transpose(&A, &A);
  ck_assert_int_eq(res, ERROR_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_transpose_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t T = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 3, &A);
  s21_matrix_init(1.0, &A);
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 5.0;
  B.matrix[2][0] = 3.0;
  B.matrix[2][1] = 6.0;

  res = s21_transpose(&A, &T);
  res = s21_eq_matrix(&T, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&T);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_transpose_03) {
  int res = 0;
  matrix_t A = {0};
  s21_create_matrix(2, 3, &A);
  s21_matrix_init(1.0, &A);
  res = s21_transpose(&A, NULL);
  ck_assert_int_eq(res, ERROR_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_01) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {NULL, 0, 0};
  s21_is_true_matrix(&A);
  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, ERROR_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_02) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);

  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_03) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(1, 1, &A);
  s21_matrix_init(1.0, &A);

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, 1.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_04) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 4000.87;
  A.matrix[0][1] = 454.0;
  A.matrix[0][2] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.897;
  A.matrix[1][2] = 3.0;
  A.matrix[2][0] = 0.000087;
  A.matrix[2][1] = 2.5668;
  A.matrix[2][2] = 1.0;

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, -24105.9967241559970716480165719986);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_05) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = -677700.0;
  A.matrix[0][1] = 654.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = -0.00001;

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, -1301.223);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_06) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(8, 8, &A);
  s21_matrix_init(1.0, &A);

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_07) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {0};
  s21_create_matrix(0, 0, &A);
  s21_is_true_matrix(&A);
  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, ERROR_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 112.0;
  A.matrix[0][1] = 243.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = -8.0;
  A.matrix[1][0] = 47.0;
  A.matrix[1][1] = 51.0;
  A.matrix[1][2] = -66.0;
  A.matrix[1][3] = 99.0;
  A.matrix[2][0] = -74.0;
  A.matrix[2][1] = 85.0;
  A.matrix[2][2] = 97.0;
  A.matrix[2][3] = 63.0;
  A.matrix[3][0] = -13.0;
  A.matrix[3][1] = 79.0;
  A.matrix[3][2] = -99.0;
  A.matrix[3][3] = -121.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = -2879514.0;
  X.matrix[0][1] = -1236631.0;
  X.matrix[0][2] = -1685096.0;
  X.matrix[0][3] = 880697.0;
  X.matrix[1][0] = 1162090.0;
  X.matrix[1][1] = -714015.0;
  X.matrix[1][2] = 4046255.0;
  X.matrix[1][3] = -3901600.0;
  X.matrix[2][0] = 4362897.0;
  X.matrix[2][1] = -2049432.0;
  X.matrix[2][2] = -532912.0;
  X.matrix[2][3] = -1370781.0;
  X.matrix[3][0] = 3412773.0;
  X.matrix[3][1] = -1569493.0;
  X.matrix[3][2] = 3144517.0;
  X.matrix[3][3] = 1284666.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_calc_complements_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = -30.0;
  X.matrix[0][2] = -108.0;
  X.matrix[0][3] = 106.0;
  X.matrix[1][0] = 138.0;
  X.matrix[1][1] = -726.0;
  X.matrix[1][2] = -1137.0;
  X.matrix[1][3] = 1061.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 12.0;
  X.matrix[2][2] = 57.0;
  X.matrix[2][3] = -47.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 6.0;
  X.matrix[3][2] = -75.0;
  X.matrix[3][3] = 57.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_calc_complements_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 3, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;

  res = s21_calc_complements(&A, &Z);

  s21_remove_matrix(&A);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(s21_calc_complements_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  res = s21_calc_complements(&A, &Z);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements_05) {
  int res = 0;
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);

  res = s21_calc_complements(&A, NULL);

  ck_assert_int_eq(res, ERROR_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 1.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = -5.0 / 23.0;
  X.matrix[1][1] = -121.0 / 23.0;
  X.matrix[1][2] = 2.0 / 23.0;
  X.matrix[1][3] = 1.0 / 23.0;
  X.matrix[2][0] = -18.0 / 23.0;
  X.matrix[2][1] = -379.0 / 46.0;
  X.matrix[2][2] = 19.0 / 46.0;
  X.matrix[2][3] = -25.0 / 46.0;
  X.matrix[3][0] = 53.0 / 69.0;
  X.matrix[3][1] = 1061.0 / 138.0;
  X.matrix[3][2] = -47.0 / 138.0;
  X.matrix[3][3] = 19.0 / 46.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_inverse_matrix_02) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(s21_inverse_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 3, &A);
  s21_matrix_init(1.0, &A);

  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 2, &A);
  s21_matrix_init(1.0, &A);

  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 3, &A);
  s21_matrix_init(1.0, &A);
  s21_remove_matrix(&A);

  res = s21_inverse_matrix(&A, &Z);

  ck_assert_int_eq(res, ERROR_MATRIX);
}
END_TEST

START_TEST(s21_inverse_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(1, 1, &X);

  X.matrix[0][0] = 1.0 / 2.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("S21MatrixUtils");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_create_matrix_01);
  tcase_add_test(tc_core, s21_create_matrix_02);
  tcase_add_test(tc_core, s21_create_matrix_03);
  tcase_add_test(tc_core, s21_create_matrix_04);
  tcase_add_test(tc_core, s21_create_matrix_05);
  tcase_add_test(tc_core, s21_create_matrix_06);
  tcase_add_test(tc_core, s21_create_matrix_07);
  tcase_add_test(tc_core, s21_create_matrix_08);
  tcase_add_test(tc_core, s21_remove_matrix_01);
  tcase_add_test(tc_core, s21_remove_matrix_02);
  tcase_add_test(tc_core, s21_eq_matrix_01);
  tcase_add_test(tc_core, s21_eq_matrix_02);
  tcase_add_test(tc_core, s21_eq_matrix_03);
  tcase_add_test(tc_core, s21_eq_matrix_04);
  tcase_add_test(tc_core, s21_eq_matrix_05);
  tcase_add_test(tc_core, s21_eq_matrix_06);
  tcase_add_test(tc_core, s21_sum_matrix_01);
  tcase_add_test(tc_core, s21_sum_matrix_02);
  tcase_add_test(tc_core, s21_sum_matrix_03);
  tcase_add_test(tc_core, s21_sum_matrix_04);
  tcase_add_test(tc_core, s21_sub_matrix_01);
  tcase_add_test(tc_core, s21_sub_matrix_02);
  tcase_add_test(tc_core, s21_sub_matrix_03);
  tcase_add_test(tc_core, s21_sub_matrix_04);
  tcase_add_test(tc_core, s21_mult_number_01);
  tcase_add_test(tc_core, s21_mult_number_02);
  tcase_add_test(tc_core, s21_mult_number_03);
  tcase_add_test(tc_core, s21_mult_matrix_01);
  tcase_add_test(tc_core, s21_mult_matrix_02);
  tcase_add_test(tc_core, s21_mult_matrix_03);
  tcase_add_test(tc_core, s21_mult_matrix_04);
  tcase_add_test(tc_core, s21_mult_matrix_05);
  tcase_add_test(tc_core, s21_transpose_01);
  tcase_add_test(tc_core, s21_transpose_02);
  tcase_add_test(tc_core, s21_transpose_03);
  tcase_add_test(tc_core, s21_determinant_01);
  tcase_add_test(tc_core, s21_determinant_02);
  tcase_add_test(tc_core, s21_determinant_03);
  tcase_add_test(tc_core, s21_determinant_04);
  tcase_add_test(tc_core, s21_determinant_05);
  tcase_add_test(tc_core, s21_determinant_06);
  tcase_add_test(tc_core, s21_determinant_07);
  tcase_add_test(tc_core, s21_calc_complements_01);
  tcase_add_test(tc_core, s21_calc_complements_02);
  tcase_add_test(tc_core, s21_calc_complements_03);
  tcase_add_test(tc_core, s21_calc_complements_04);
  tcase_add_test(tc_core, s21_calc_complements_05);
  tcase_add_test(tc_core, s21_inverse_matrix_01);
  tcase_add_test(tc_core, s21_inverse_matrix_02);
  tcase_add_test(tc_core, s21_inverse_matrix_03);
  tcase_add_test(tc_core, s21_inverse_matrix_04);
  tcase_add_test(tc_core, s21_inverse_matrix_05);
  tcase_add_test(tc_core, s21_inverse_matrix_06);

  suite_add_tcase(suite, tc_core);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_VERBOSE);

  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failures == 0) ? 0 : 1;
}
