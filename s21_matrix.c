#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows <= 0 || columns <= 0) return CODE_INVALID_MATRIX;

  int code = CODE_OK;

  if ((result->matrix = (double **)calloc(rows, sizeof(double *)))) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) code = CODE_INVALID_MATRIX;
    }
  } else
    code = CODE_INVALID_MATRIX;

  if (code == CODE_OK) {
    result->rows = rows;
    result->columns = columns;
  }

  return code;
}

void s21_remove_matrix(matrix_t *A) {
  if (incorrect_matrix(A)) return;

  if (A->rows != 0) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    }
    if (A->matrix != NULL) free(A->matrix);

    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (incorrect_matrix(A) || incorrect_matrix(B) || (A->rows != B->rows) ||
      (A->columns != B->columns))
    return FAILURE;

  int code = SUCCESS;

  for (int i = 0; i < A->rows && code == SUCCESS; i++) {
    for (int j = 0; j < A->columns && code == SUCCESS; j++) {
      if (fabsf((float)(A->matrix[i][j] - B->matrix[i][j])) > 1e-6) {
        code = FAILURE;
      }
    }
  }

  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (incorrect_matrix(A) || incorrect_matrix(B) || result == NULL)
    return CODE_INVALID_MATRIX;

  int code = CODE_OK;

  if (A->rows != B->rows || A->columns != B->columns)
    code = CODE_CALCULATION_ERROR;
  else
    code = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows && code == CODE_OK; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (incorrect_matrix(A) || incorrect_matrix(B) || result == NULL)
    return CODE_INVALID_MATRIX;

  int code = CODE_OK;

  if (A->rows != B->rows || A->columns != B->columns)
    code = CODE_CALCULATION_ERROR;
  else
    code = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows && code == CODE_OK; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return CODE_INVALID_MATRIX;

  int code = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows && code == CODE_OK; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (incorrect_matrix(A) || incorrect_matrix(B) || result == NULL)
    return CODE_INVALID_MATRIX;

  int code = CODE_OK;

  if (A->columns != B->rows)
    code = CODE_CALCULATION_ERROR;
  else
    code = s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows && code == CODE_OK; i++) {
    for (int k = 0; k < B->columns; k++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][k] += A->matrix[i][j] * B->matrix[j][k];
      }
    }
  }

  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return CODE_INVALID_MATRIX;

  int code = s21_create_matrix(A->columns, A->rows, result);

  for (int i = 0; i < A->rows && code == CODE_OK; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  if (incorrect_matrix(A) || result == NULL) return CODE_INVALID_MATRIX;

  int code = CODE_OK;

  if (A->columns != A->rows) code = CODE_CALCULATION_ERROR;

  *result = 1;

  if (code == CODE_OK) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
      upper_triangular_matrix(A);
      for (int k = 0; k < A->columns; k++) *result *= A->matrix[k][k];
    }
  }

  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return CODE_INVALID_MATRIX;

  int code = s21_create_matrix(A->rows, A->columns, result);

  if (A->columns != A->rows) code = CODE_CALCULATION_ERROR;

  for (int i = 0; i < A->rows && code == CODE_OK; i++) {
    matrix_t buffer;
    s21_create_matrix(A->rows - 1, A->columns - 1, &buffer);

    for (int j = 0; j < A->columns; j++) {
      filling_buffer(i, j, *A, &buffer);
      s21_determinant(&buffer, &result->matrix[i][j]);
      result->matrix[i][j] *= pow(-1, (i + j));
    }

    s21_remove_matrix(&buffer);
  }

  return code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return CODE_INVALID_MATRIX;
  if (A->rows != A->columns || determinant_eq_zero(*A))
    return CODE_CALCULATION_ERROR;

  int code = CODE_OK;

  double determinant = determenant_A(*A);

  if (A->rows == 1 && code == CODE_OK) {
    code = s21_create_matrix(A->rows, A->columns, result);
    if (code == CODE_OK) result->matrix[0][0] = 1 / A->matrix[0][0];
  } else if (code == CODE_OK) {
    matrix_t minor_matrix;
    matrix_t transpose_matrix;

    if (code == CODE_OK) code = s21_calc_complements(A, &minor_matrix);
    if (code == CODE_OK) code = s21_transpose(&minor_matrix, &transpose_matrix);
    if (code == CODE_OK)
      code = s21_mult_number(&transpose_matrix, 1 / determinant, result);

    s21_remove_matrix(&transpose_matrix);
    s21_remove_matrix(&minor_matrix);
  }

  return code;
}
