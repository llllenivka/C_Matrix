#include <check.h>

#include "s21_matrix.h"

/***********************************/
/********** CREATE MATRIX **********/
/***********************************/

START_TEST(test_create_matrix_1) {
  int rows = 6;
  int columns = 12;
  matrix_t A;

  int my_result = s21_create_matrix(rows, columns, &A);
  int check = CODE_OK;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST;

START_TEST(test_create_matrix_2) {
  int rows = -7;
  int columns = 12;
  matrix_t A;

  int my_result = s21_create_matrix(rows, columns, &A);
  int check = CODE_INVALID_MATRIX;

  ck_assert_int_eq(my_result, check);
}
END_TEST;

START_TEST(test_create_matrix_3) {
  int rows = 7;
  int columns = 0;
  matrix_t A;

  int my_result = s21_create_matrix(rows, columns, &A);

  int check = CODE_INVALID_MATRIX;
  ck_assert_int_eq(my_result, check);
}
END_TEST;

Suite *s21_test_create_matrix() {
  Suite *result;
  TCase *tc_create_matrix;

  result = suite_create("\033[105m  ★︎  CREATE_MATRIX  ★︎  \033[049m");
  tc_create_matrix = tcase_create("CREATE_MATRIX");

  tcase_add_test(tc_create_matrix, test_create_matrix_1);
  tcase_add_test(tc_create_matrix, test_create_matrix_2);
  tcase_add_test(tc_create_matrix, test_create_matrix_3);

  suite_add_tcase(result, tc_create_matrix);

  return result;
}

/***********************************/
/************ EQ MATRIX ************/
/***********************************/

START_TEST(test_eq_matrix_1) {
  matrix_t A;
  matrix_t B;

  int rows = 5;
  int columns = 12;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  int my_result = s21_eq_matrix(&A, &B);
  int check = SUCCESS;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

START_TEST(test_eq_matrix_2) {
  matrix_t A;
  matrix_t B;

  int rows = 5;
  int columns = 12;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows + 1, columns, &B);

  int my_result = s21_eq_matrix(&A, &B);
  int check = FAILURE;

  ck_assert_int_eq(my_result, check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

START_TEST(test_eq_matrix_3) {
  matrix_t A;
  matrix_t B;

  int rows = 5;
  int columns = 12;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  filling_matrix(&A, 1);
  filling_matrix(&B, 1);

  int my_result = s21_eq_matrix(&A, &B);
  int check = SUCCESS;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

START_TEST(test_eq_matrix_4) {
  matrix_t A;
  matrix_t B;

  int rows = 5;
  int columns = 12;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  filling_matrix(&A, 1);
  filling_matrix(&B, 2);

  int my_result = s21_eq_matrix(&A, &B);
  int check = FAILURE;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

Suite *s21_test_eq_matrix() {
  Suite *result;
  TCase *tc_eq_matrix;

  result = suite_create("\033[105m  ★︎    EQ_MATRIX    ★︎  \033[049m");
  tc_eq_matrix = tcase_create("CREATE_MATRIX");

  tcase_add_test(tc_eq_matrix, test_eq_matrix_1);
  tcase_add_test(tc_eq_matrix, test_eq_matrix_2);
  tcase_add_test(tc_eq_matrix, test_eq_matrix_3);
  tcase_add_test(tc_eq_matrix, test_eq_matrix_4);

  suite_add_tcase(result, tc_eq_matrix);

  return result;
}

/***********************************/
/*********** SUM MATRIX ************/
/***********************************/

START_TEST(test_sum_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t my_result;

  matrix_t check;

  int rows = 5;
  int columns = 12;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  s21_create_matrix(rows, columns, &check);

  filling_matrix(&A, 1);
  filling_matrix(&B, 2);
  filling_matrix(&check, 3);

  s21_sum_matrix(&A, &B, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t my_result;

  matrix_t check;

  int rows = 5;
  int columns = 5;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  s21_create_matrix(rows, columns, &check);

  filling_matrix(&A, 5);
  filling_matrix(&B, -5);

  s21_sum_matrix(&A, &B, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_sum_matrix_3) {
  matrix_t A;
  matrix_t my_result;

  int rows = 5;
  int columns = 5;

  s21_create_matrix(rows, columns, &A);

  int check = CODE_INVALID_MATRIX;

  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &my_result), check);

  s21_remove_matrix(&A);
}
END_TEST;

START_TEST(test_sum_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;

  int my_result;
  int check;

  int rows = 5;
  int columns = 5;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows + 6, columns, &B);

  my_result = s21_sum_matrix(&A, &B, &C);
  check = CODE_CALCULATION_ERROR;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

Suite *s21_test_sum_matrix() {
  Suite *result;
  TCase *tc_sum_matrix;

  result = suite_create("\033[105m  ★︎   SUM_MATRIX    ★︎  \033[049m");
  tc_sum_matrix = tcase_create("SUM_MATRIX");

  tcase_add_test(tc_sum_matrix, test_sum_matrix_1);
  tcase_add_test(tc_sum_matrix, test_sum_matrix_2);
  tcase_add_test(tc_sum_matrix, test_sum_matrix_3);
  tcase_add_test(tc_sum_matrix, test_sum_matrix_4);

  suite_add_tcase(result, tc_sum_matrix);

  return result;
}

/***********************************/
/*********** SUB MATRIX ************/
/***********************************/

START_TEST(test_sub_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t my_result;

  matrix_t check;

  int rows = 5;
  int columns = 12;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  s21_create_matrix(rows, columns, &check);

  filling_matrix(&A, 1);
  filling_matrix(&B, 2);
  filling_matrix(&check, -1);

  s21_sub_matrix(&A, &B, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t my_result;

  matrix_t check;

  int rows = 5;
  int columns = 5;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  s21_create_matrix(rows, columns, &check);

  filling_matrix(&A, 5);
  filling_matrix(&B, -5);
  filling_matrix(&check, 10);

  s21_sub_matrix(&A, &B, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_sub_matrix_3) {
  matrix_t A;
  matrix_t my_result;

  int rows = 5;
  int columns = 5;

  s21_create_matrix(rows, columns, &A);

  int check = CODE_INVALID_MATRIX;

  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &my_result), check);

  s21_remove_matrix(&A);
}
END_TEST;

START_TEST(test_sub_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;

  int my_result;
  int check;

  int rows = 5;
  int columns = 5;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows + 6, columns, &B);

  my_result = s21_sub_matrix(&A, &B, &C);
  check = CODE_CALCULATION_ERROR;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

Suite *s21_test_sub_matrix() {
  Suite *result;
  TCase *tc_sub_matrix;

  result = suite_create("\033[105m  ★︎   SUB_MATRIX    ★︎  \033[049m");
  tc_sub_matrix = tcase_create("SUM_MATRIX");

  tcase_add_test(tc_sub_matrix, test_sub_matrix_1);
  tcase_add_test(tc_sub_matrix, test_sub_matrix_2);
  tcase_add_test(tc_sub_matrix, test_sub_matrix_3);
  tcase_add_test(tc_sub_matrix, test_sub_matrix_4);

  suite_add_tcase(result, tc_sub_matrix);

  return result;
}

/***********************************/
/*********** MULT NUMBER ***********/
/***********************************/

START_TEST(test_mult_number_1) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  int rows = 5;
  int columns = 5;
  double number = 2.7;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &check);

  filling_matrix(&A, 5);
  filling_matrix(&check, 5 * number);

  s21_mult_number(&A, number, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_mult_number_2) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  int rows = 10;
  int columns = 10;
  double number = -1.123;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &check);

  filling_matrix(&A, 0.08);
  filling_matrix(&check, 0.08 * number);

  s21_mult_number(&A, number, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_mult_number_3) {
  matrix_t my_result;

  double number = -1.123;
  int check = CODE_INVALID_MATRIX;

  ck_assert_int_eq(s21_mult_number(NULL, number, &my_result), check);
}
END_TEST;

Suite *s21_test_mult_number() {
  Suite *result;
  TCase *tc_mult_number;

  result = suite_create("\033[105m  ★︎   MULT_NUMBER   ★︎  \033[049m");
  tc_mult_number = tcase_create("MULT_NUMBER");

  tcase_add_test(tc_mult_number, test_mult_number_1);
  tcase_add_test(tc_mult_number, test_mult_number_2);
  tcase_add_test(tc_mult_number, test_mult_number_3);

  suite_add_tcase(result, tc_mult_number);

  return result;
}

/***********************************/
/*********** MULT MATRIX ***********/
/***********************************/

START_TEST(test_mult_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t my_result;
  matrix_t check;

  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &check);

  A.matrix[0][0] = 244;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 3;

  A.matrix[2][0] = 743;
  A.matrix[2][1] = 18;
  A.matrix[2][2] = 94;

  B.matrix[0][0] = 2;
  B.matrix[0][1] = 33;
  B.matrix[0][2] = 2;

  B.matrix[1][0] = 22;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 33;

  B.matrix[2][0] = 1;
  B.matrix[2][1] = 22;
  B.matrix[2][2] = 3;

  check.matrix[0][0] = 535;
  check.matrix[0][1] = 8124;
  check.matrix[0][2] = 563;

  check.matrix[1][0] = 77;
  check.matrix[1][1] = 207;
  check.matrix[1][2] = 116;

  check.matrix[2][0] = 1976;
  check.matrix[2][1] = 26641;
  check.matrix[2][2] = 2362;

  s21_mult_matrix(&A, &B, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_mult_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t my_result;
  matrix_t check;

  int rows = 2;
  int columns = 2;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &check);

  A.matrix[0][0] = 244;
  A.matrix[0][1] = 2;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 3;

  B.matrix[0][0] = 2;
  B.matrix[0][1] = 33;

  B.matrix[1][0] = 22;
  B.matrix[1][1] = 3;

  check.matrix[0][0] = 532;
  check.matrix[0][1] = 8058;

  check.matrix[1][0] = 74;
  check.matrix[1][1] = 141;

  s21_mult_matrix(&A, &B, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_mult_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  int my_result = 0;
  int check = CODE_CALCULATION_ERROR;

  int rows = 2;
  int columns = 2;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows + 10, columns, &B);

  my_result = s21_mult_matrix(&A, &B, &C);

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST;

START_TEST(test_mult_matrix_4) {
  matrix_t A;
  matrix_t C;

  int my_result = 0;
  int check = CODE_INVALID_MATRIX;

  int rows = 2;
  int columns = 2;

  s21_create_matrix(rows, columns, &A);

  my_result = s21_mult_matrix(&A, NULL, &C);

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST;

Suite *s21_test_mult_matrix() {
  Suite *result;
  TCase *tc_mult_matrix;

  result = suite_create("\033[105m  ★︎   MULT_MATRIX   ★︎  \033[049m");
  tc_mult_matrix = tcase_create("MULT_MATRIX");

  tcase_add_test(tc_mult_matrix, test_mult_matrix_1);
  tcase_add_test(tc_mult_matrix, test_mult_matrix_2);
  tcase_add_test(tc_mult_matrix, test_mult_matrix_3);
  tcase_add_test(tc_mult_matrix, test_mult_matrix_4);

  suite_add_tcase(result, tc_mult_matrix);

  return result;
}

/***********************************/
/***********  TRANSPOSE  ***********/
/***********************************/

START_TEST(test_transpose_1) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  int rows = 2;
  int columns = 2;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &check);

  A.matrix[0][0] = 8;
  A.matrix[0][1] = 9;

  A.matrix[1][0] = 238;
  A.matrix[1][1] = 19;

  check.matrix[0][0] = 8;
  check.matrix[0][1] = 238;

  check.matrix[1][0] = 9;
  check.matrix[1][1] = 19;

  s21_transpose(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&check, &my_result), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_transpose_2) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  int rows = 1;
  int columns = 6;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &check);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 238;
  A.matrix[0][3] = 4;
  A.matrix[0][4] = 3;
  A.matrix[0][5] = 9;

  check.matrix[0][0] = 1;
  check.matrix[1][0] = 2;
  check.matrix[2][0] = 238;
  check.matrix[3][0] = 4;
  check.matrix[4][0] = 3;
  check.matrix[5][0] = 9;

  s21_transpose(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&check, &my_result), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST;

START_TEST(test_transpose_3) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &check);

  A.matrix[0][0] = 1.25;
  check.matrix[0][0] = 1.25;

  s21_transpose(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *s21_test_transpose() {
  Suite *result;
  TCase *tc_transpose;

  result = suite_create("\033[105m  ★︎    TRANSPOSE    ★︎  \033[049m");
  tc_transpose = tcase_create("TRANSPOSE");

  tcase_add_test(tc_transpose, test_transpose_1);
  tcase_add_test(tc_transpose, test_transpose_2);
  tcase_add_test(tc_transpose, test_transpose_3);

  suite_add_tcase(result, tc_transpose);

  return result;
}

/***********************************/
/********* CALC COMPLEMENTS ********/
/***********************************/

START_TEST(test_calc_complements_1) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);

  A.matrix[0][0] = 23;
  A.matrix[0][1] = -1.5;
  A.matrix[0][2] = 2;

  A.matrix[1][0] = 33;
  A.matrix[1][1] = 245;
  A.matrix[1][2] = -9;

  A.matrix[2][0] = 0;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 7.12;

  check.matrix[0][0] = 1798.4;
  check.matrix[0][1] = -234.96;
  check.matrix[0][2] = 198;

  check.matrix[1][0] = 22.68;
  check.matrix[1][1] = 163.76;
  check.matrix[1][2] = -138;

  check.matrix[2][0] = -476.5;
  check.matrix[2][1] = 273;
  check.matrix[2][2] = 5684.5;

  s21_calc_complements(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &check);

  A.matrix[0][0] = 23.23;
  A.matrix[0][1] = 23.23;

  A.matrix[1][0] = 23.23;
  A.matrix[1][1] = 23.23;

  check.matrix[0][0] = 23.23;
  check.matrix[0][1] = -23.23;

  check.matrix[1][0] = -23.23;
  check.matrix[1][1] = 23.23;

  s21_calc_complements(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);

  A.matrix[0][0] = 43;
  A.matrix[0][1] = -0.15;
  A.matrix[0][2] = 3.67;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 11;
  A.matrix[1][2] = 45;

  A.matrix[2][0] = -45;
  A.matrix[2][1] = 3.25;
  A.matrix[2][2] = 6;

  check.matrix[0][0] = -80.25;
  check.matrix[0][1] = -2085;
  check.matrix[0][2] = 527.5;

  check.matrix[1][0] = 12.8275;
  check.matrix[1][1] = 423.15;
  check.matrix[1][2] = -133;

  check.matrix[2][0] = -47.12;
  check.matrix[2][1] = -1898.3;
  check.matrix[2][2] = 474.5;

  s21_calc_complements(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *s21_test_calc_complements() {
  Suite *result;
  TCase *tc_calc_complements;

  result = suite_create("\033[105m  ★︎ CALC COMPLIMENT ★︎  \033[049m");
  tc_calc_complements = tcase_create("CALC COMPLIMENTS");

  tcase_add_test(tc_calc_complements, test_calc_complements_1);
  tcase_add_test(tc_calc_complements, test_calc_complements_2);
  tcase_add_test(tc_calc_complements, test_calc_complements_3);

  suite_add_tcase(result, tc_calc_complements);

  return result;
}

/***********************************/
/*********   DETERMINANT   *********/
/***********************************/

START_TEST(test_determinant_1) {
  matrix_t A;
  double my_result = 0;
  double check = 0;

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 43;
  A.matrix[0][1] = -0.15;
  A.matrix[0][2] = 3.67;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 11;
  A.matrix[1][2] = 45;

  A.matrix[2][0] = -45;
  A.matrix[2][1] = 3.25;
  A.matrix[2][2] = 6;

  s21_determinant(&A, &my_result);
  check = -1202.075;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2) {
  matrix_t A;
  double my_result = 0;
  double check = 0;

  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = -36;
  A.matrix[0][2] = 0;
  A.matrix[0][3] = 3.67;
  A.matrix[0][4] = 24;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 11;
  A.matrix[1][2] = 45;
  A.matrix[1][3] = 45;
  A.matrix[1][4] = 45;

  A.matrix[2][0] = -45;
  A.matrix[2][1] = 3.25;
  A.matrix[2][2] = 6;
  A.matrix[2][3] = -6;
  A.matrix[2][4] = 0.1;

  A.matrix[3][0] = 89;
  A.matrix[3][1] = 344;
  A.matrix[3][2] = 0.6;
  A.matrix[3][3] = -7;
  A.matrix[3][4] = -8;

  A.matrix[4][0] = 12.12;
  A.matrix[4][1] = 23;
  A.matrix[4][2] = 83;
  A.matrix[4][3] = 0;
  A.matrix[4][4] = 99;

  s21_determinant(&A, &my_result);
  check = 1284391732.2850361;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A;
  double B;

  s21_create_matrix(2, 5, &A);

  int my_result = s21_determinant(&A, &B);
  int check = CODE_CALCULATION_ERROR;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4) {
  matrix_t A;
  double my_result = 0;
  double check = 0;

  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.123;

  s21_determinant(&A, &my_result);
  check = 1.123;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5) {
  matrix_t A;
  double my_result = 0;
  double check = 0;

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = -36;

  A.matrix[1][0] = 0.025;
  A.matrix[1][1] = 7;

  s21_determinant(&A, &my_result);
  check = 7.9;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_determinant() {
  Suite *result;
  TCase *tc_determinant;

  result = suite_create("\033[105m  ★︎   DETERMINANT   ★︎  \033[049m");
  tc_determinant = tcase_create("DETERMINANT");

  tcase_add_test(tc_determinant, test_determinant_1);
  tcase_add_test(tc_determinant, test_determinant_2);
  tcase_add_test(tc_determinant, test_determinant_3);
  tcase_add_test(tc_determinant, test_determinant_4);
  tcase_add_test(tc_determinant, test_determinant_5);

  suite_add_tcase(result, tc_determinant);

  return result;
}

/***********************************/
/********  INVERSE MATRIX  *********/
/***********************************/

START_TEST(test_inverse_matrix_1) {
  matrix_t A;
  matrix_t B;
  int my_result;
  int check;

  s21_create_matrix(2, 2, &A);

  my_result = s21_inverse_matrix(&A, &B);
  check = CODE_CALCULATION_ERROR;

  ck_assert_int_eq(my_result, check);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &check);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = -36;

  A.matrix[1][0] = 0.025;
  A.matrix[1][1] = 7;

  check.matrix[0][0] = 0.8860759;
  check.matrix[0][1] = 4.5569620;

  check.matrix[1][0] = -0.0031645;
  check.matrix[1][1] = 0.12658227;

  s21_inverse_matrix(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_inverse_matrix_3) {
  matrix_t A;
  matrix_t my_result;
  matrix_t check;

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &check);

  A.matrix[0][0] = -0.25;

  check.matrix[0][0] = -4;

  s21_inverse_matrix(&A, &my_result);

  ck_assert_int_eq(s21_eq_matrix(&my_result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&my_result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *s21_test_inverse_matrix() {
  Suite *result;
  TCase *tc_inverse_matrix;

  result = suite_create("\033[105m  ★︎  INVERSE_MATRIX ★︎  \033[049m");
  tc_inverse_matrix = tcase_create("INVERSE MATRIX");

  tcase_add_test(tc_inverse_matrix, test_inverse_matrix_1);
  tcase_add_test(tc_inverse_matrix, test_inverse_matrix_2);
  tcase_add_test(tc_inverse_matrix, test_inverse_matrix_3);

  suite_add_tcase(result, tc_inverse_matrix);

  return result;
}

int main() {
  Suite *result;
  int failed = 0;
  SRunner *runner;

  result = s21_test_create_matrix();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_eq_matrix();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_sum_matrix();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_sub_matrix();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_mult_number();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_mult_matrix();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_transpose();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_calc_complements();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_determinant();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_test_inverse_matrix();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : CK_FAILURE;
}
