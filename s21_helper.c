#include "s21_matrix.h"

/**
 * @brief вывод матрицы в терминал
 * */
void print_matrix(matrix_t matrix) {
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      printf("\t%f\t|", matrix.matrix[i][j]);
    }
    putchar('\n');
    putchar('\n');
  }
  for (int i = 0; i < 120; i++) putchar('-');
  putchar('\n');
}

/**
 * @brief заполнение матрицы n числом, увеличивающийся на заданный
 * интервал
 * */
void filling_matrix(matrix_t *matrix, double interval) {
  double n = 0;
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = n;
      n += interval;
    }
  }
}

/**
 * @brief переделывает матрицу А без определенных строки и ряда
 * Пример:
 *           pass_i = 0; pass_j = 0;
 *
 *           1 2 3      5 6
 *           4 5 6 -->  8 9
 *           7 8 9
 * */
void filling_buffer(int pass_i, int pass_j, matrix_t A, matrix_t *buffer) {
  int flag_i = 0;

  for (int i = 0; i < A.rows; i++) {
    if (i == pass_i) {
      flag_i = 1;
      continue;
    }
    int flag_j = 0;

    for (int j = 0; j < A.columns; j++) {
      if (j == pass_j) {
        flag_j = 1;
        continue;
      }

      if (flag_i == 0 && flag_j == 1)
        buffer->matrix[i][j - 1] = A.matrix[i][j];
      else if (flag_i == 1 && flag_j == 0)
        buffer->matrix[i - 1][j] = A.matrix[i][j];
      else if (flag_i == 1 && flag_j == 1)
        buffer->matrix[i - 1][j - 1] = A.matrix[i][j];
      else
        buffer->matrix[i][j] = A.matrix[i][j];
    }
  }
}

/**
 * @brief приводит матрицу к верхнетреугольному виду
 * */
void upper_triangular_matrix(matrix_t *A) {
  int rows_pass = 0;

  for (int j = 0; j < A->columns - 1; j++) {
    for (int i = A->rows - 1; i > 0 + rows_pass; i--) {
      if (A->matrix[i - 1][j] - 0.0 < 1e-7) {
        for (int k = 0; k < A->columns; k++)
          A->matrix[i - 1][k] += A->matrix[i][k];
        if (fabsf((float)(A->matrix[i][j] - 0.0)) < 1e-7) continue;
      }

      matrix_t buffer;
      s21_create_matrix(1, A->columns, &buffer);

      for (int k = 0; k < buffer.columns; k++) {
        buffer.matrix[0][k] = A->matrix[i - 1][k];
      }

      double buffer_divider = buffer.matrix[0][j];

      for (int k = 0; k < buffer.columns; k++) {
        buffer.matrix[0][k] /= buffer_divider;
        buffer.matrix[0][k] *= -(A->matrix[i][j]);
      }

      for (int k = 0; k < A->columns; k++) {
        A->matrix[i][k] += buffer.matrix[0][k];
      }

      s21_remove_matrix(&buffer);
    }
    rows_pass++;
  }
}

/**
 * @brief проверка на корректную матрицу: 0 - корректная; 1 - ошибка;
 * */
int incorrect_matrix(matrix_t *A) {
  int code = 0;
  if (A == NULL || A->columns <= 0 || A->rows <= 0) code = 1;

  return code;
}

/**
 * @brief проверка на определитель матрицы: 0 - если детерминант не равен нулю;
 * 1 - если равен;
 * */
int determinant_eq_zero(matrix_t A) {
  int code = 0;
  double determinant = 0;
  s21_determinant(&A, &determinant);
  if (determinant == 0.0) code = 1;
  return code;
}

/**
 * @brief возвращает значение детерминанта матрицы
 * */
double determenant_A(matrix_t A) {
  double result = 0;
  s21_determinant(&A, &result);

  return result;
}