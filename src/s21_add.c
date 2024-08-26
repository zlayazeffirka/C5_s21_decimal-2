#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  s21_rescale(&value_1, &value_2);
  s21_big_decimal big_value_1 = s21_convert_std_to_big(value_1);
  s21_big_decimal big_value_2 = s21_convert_std_to_big(value_2);
  s21_big_decimal big_result;
  s21_null_big_decimal(&big_result);
  if (big_value_1.sign == big_value_2.sign) {
    return_code = s21_add_big(big_value_1, big_value_2, &big_result);
  } else {
    if (big_value_1.sign) {
      big_value_1.sign = 0;
      value_1 = s21_convert_big_to_std(big_value_1);
      return_code = s21_sub(value_2, value_1, result);
      big_result = s21_convert_std_to_big(*result);
    } else {
      big_value_2.sign = 0;
      value_2 = s21_convert_big_to_std(big_value_2);
      return_code = s21_sub(value_1, value_2, result);
      big_result = s21_convert_std_to_big(*result);
    }
  }
  *result = s21_convert_big_to_std(big_result);
  return return_code;
}
