#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUS_SIGN 2147483648
#define UINT_MAX 4294967295
#define SUCCES 1
#define FAIL 0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  bool bits[192];
  bool sign;
  int exp;
} s21_big_decimal;

typedef enum {
  OPERATION_OK = 0,
  NUMBER_TOO_BIG,
  NUMBER_TOO_SMALL,
  DIVISION_BY_ZERO
} operation_result;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_result;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_round(s21_decimal value, s21_decimal *res);
int s21_floor(s21_decimal value, s21_decimal *res);
int s21_negate(s21_decimal value, s21_decimal *res);
int s21_truncate(s21_decimal value, s21_decimal *res);

int s21_sub_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_add_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_mul_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_div_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_mod_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);

bool s21_get_bit_int(unsigned int num, int pos);
void s21_right_shift(s21_big_decimal *big);
void s21_left_shift(s21_big_decimal *big);
bool s21_get_sign_std(s21_decimal dec);
int s21_get_exp_std(s21_decimal dec);
void s21_null_big_decimal(s21_big_decimal *big);
s21_big_decimal s21_convert_std_to_big(s21_decimal std);
s21_decimal s21_convert_big_to_std(s21_big_decimal big);
void s21_rescale(s21_decimal *value_1, s21_decimal *value_2);
void s21_rescale_big(s21_big_decimal *big_value_1,
                     s21_big_decimal *big_value_2);
void s21_rescale_big_to_smaller(s21_big_decimal *big_value_1,
                                s21_big_decimal *big_value_2);
void s21_init_decimal(s21_decimal *decimal);
int s21_div_by_ten(s21_big_decimal *big);
bool s21_compare_bits(s21_big_decimal big1, s21_big_decimal big2);
bool s21_is_null(s21_big_decimal big);
int s21_last_bit(s21_big_decimal big);
void s21_bank_rounding(s21_big_decimal *big, int mod);
void s21_align(s21_big_decimal *big1, s21_big_decimal *big2);
void s21_rescale_big_to_zero(s21_big_decimal *big_value_1,
                             s21_big_decimal *big_value_2);
s21_big_decimal s21_div_with_modulo(s21_big_decimal big_value_1,
                                    s21_big_decimal big_value_2,
                                    s21_big_decimal *big_result);
void s21_truncate_big(s21_big_decimal *big_value);
void s21_set_minus(s21_decimal *dst);

s21_big_decimal s21_convert_int_to_big(unsigned long int number);
s21_decimal s21_convert_int_to_std(unsigned long int number);

#endif  // SRC_S21_DECIMAL_H_
