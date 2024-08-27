#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define FAILURE 0
#define SUCCESS 1

enum code_error_matrix { CODE_OK, CODE_INVALID_MATRIX, CODE_CALCULATION_ERROR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/*-------------- helper ----------------*/

void print_matrix(matrix_t);
void filling_matrix(matrix_t *matrix, double interval);
int incorrect_matrix(matrix_t *A);
void filling_buffer(int pass_i, int pass_j, matrix_t A, matrix_t *buffer);
void upper_triangular_matrix(matrix_t *A);
int determinant_eq_zero(matrix_t A);
double determenant_A(matrix_t A);

#endif