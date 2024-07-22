#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows < 1 || columns < 1 || result == NULL) {
    res = ERROR_MATRIX;
  } else {
    result->rows = rows;
    result->matrix = (double **)calloc(rows, sizeof(double *));

    if (result->matrix == NULL) {
      res = ERROR_MATRIX;
    } else {
      result->columns = columns;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
    }
  }

  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (!A) return;
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A->columns) A->columns = 0;
  if (A->rows) A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (s21_is_true_matrix(A) || s21_is_true_matrix(B)) {
    res = FAILURE;
  } else {
    if (A->columns == B->columns && A->rows == B->rows && A->matrix != NULL &&
        B->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
            res = FAILURE;
          }
        }
      }
    } else {
      res = FAILURE;
    }
  }

  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_is_true_matrix(A) || s21_is_true_matrix(B)) {
    res = ERROR_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns ||
             A->matrix == NULL || B->matrix == NULL) {
    res = ERROR_CALC;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    res = ERROR_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_is_true_matrix(A) || s21_is_true_matrix(B)) {
    res = ERROR_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns ||
             A->matrix == NULL || B->matrix == NULL) {
    res = ERROR_CALC;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    res = ERROR_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (s21_is_true_matrix(A)) {
    res = ERROR_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    res = ERROR_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_is_true_matrix(A) || s21_is_true_matrix(B)) {
    res = ERROR_MATRIX;
  } else if (A->columns != B->rows || A->matrix == NULL || B->matrix == NULL) {
    res = ERROR_CALC;
  } else {
    if ((s21_create_matrix(A->rows, B->columns, result)) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      res = ERROR_MATRIX;
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (s21_is_true_matrix(A)) {
    res = ERROR_MATRIX;
  } else if ((s21_create_matrix(A->columns, A->rows, result)) != OK) {
    res = ERROR_MATRIX;
  } else {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (s21_is_true_matrix(A)) {
    res = ERROR_MATRIX;
  } else if (A->rows != A->columns) {
    res = ERROR_CALC;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0.0;
      for (int i = 0; i < A->rows; i++) {
        matrix_t minor;
        double res_min = 0.0;
        s21_minor(A, i, 0, &minor);
        s21_determinant(&minor, &res_min);
        *result += pow((-1), i) * A->matrix[i][0] * res_min;
        s21_remove_matrix(&minor);
      }
    }
  }

  return res;
}

void s21_minor(matrix_t *A, int row, int column, matrix_t *result) {
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int r = 0;
  for (int i = 0; i < A->rows; i++) {
    int c = 0;
    for (int j = 0; j < A->columns; j++) {
      if (i != row && j != column) {
        result->matrix[i - r][j - c] = A->matrix[i][j];
      } else if (i == row) {
        r = 1;
      } else if (j == column) {
        c = 1;
      }
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_is_true_matrix(A)) {
    res = ERROR_MATRIX;
  } else if (A->rows != A->columns) {
    res = ERROR_CALC;
  } else {
    if ((res = s21_create_matrix(A->rows, A->columns, result)) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          double det = 0.0;
          s21_minor(A, i, j, &minor);
          s21_determinant(&minor, &det);
          result->matrix[i][j] = pow(-1, i + j) * det;
          s21_remove_matrix(&minor);
        }
      }
    } else {
      res = ERROR_MATRIX;
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_is_true_matrix(A)) {
    res = ERROR_MATRIX;
  } else if (A->rows != A->columns) {
    res = ERROR_CALC;
  } else {
    double det = 0.0;
    s21_determinant(A, &det);
    if (det == 0) {
      res = ERROR_CALC;
    } else {
      if ((A->rows == 1) &&
          (res = s21_create_matrix(A->rows, A->columns, result)) == OK) {
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        matrix_t algebr;
        if ((res = s21_calc_complements(A, &algebr)) == OK) {
          matrix_t transposed;
          if ((res = s21_transpose(&algebr, &transposed)) == OK) {
            s21_mult_number(&transposed, 1 / det, result);
            s21_remove_matrix(&transposed);
          }
        }
        s21_remove_matrix(&algebr);
      }
    }
  }
  return res;
}

void s21_matrix_init(double number, matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    for (int k = 0; k < A->columns; ++number, ++k) A->matrix[i][k] = number;
  }
}

int s21_is_true_matrix(matrix_t *A) {
  int res = OK;
  if (A->rows < 1 || A->columns < 1 || A == NULL) {
    res = ERROR_MATRIX;
  }
  return res;
}
