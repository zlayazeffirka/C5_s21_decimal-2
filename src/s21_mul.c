#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  s21_big_decimal big_value_1 = s21_convert_std_to_big(value_1);
  s21_big_decimal big_value_2 = s21_convert_std_to_big(value_2);
  s21_big_decimal big_result;

  s21_null_big_decimal(&big_result);
  return_code = s21_mul_big(big_value_1, big_value_2, &big_result);
  *result = s21_convert_big_to_std(big_result);

  return return_code;
}
