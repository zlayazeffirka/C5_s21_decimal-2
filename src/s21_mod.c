#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  s21_big_decimal big_value_1 = s21_convert_std_to_big(value_1);
  s21_big_decimal big_value_2 = s21_convert_std_to_big(value_2);
  s21_big_decimal big_result;
  s21_null_big_decimal(&big_result);
  if (s21_is_null(big_value_2))
    return_code = 3;
  else if (!s21_is_null(big_value_1))
    return_code = s21_mod_big(big_value_1, big_value_2, &big_result);
  *result = s21_convert_big_to_std(big_result);
  return return_code;
}
