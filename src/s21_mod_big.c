#include "s21_decimal.h"

int s21_mod_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  int return_code = 0;
  bool sign = big_value_1.sign;
  big_value_1.sign = 0;
  big_value_2.sign = 0;
  s21_big_decimal factor;

  s21_div_big(big_value_1, big_value_2, &factor);
  s21_truncate_big(&factor);
  s21_mul_big(big_value_2, factor, &factor);
  s21_rescale_big(&big_value_1, &factor);
  s21_sub_big(big_value_1, factor, big_result);
  big_result->exp = factor.exp;
  if (s21_last_bit(*big_result) > 95) s21_truncate_big(big_result);
  if (s21_last_bit(*big_result) > 95) return_code = 1;

  big_result->sign = sign;
  return return_code;
}
