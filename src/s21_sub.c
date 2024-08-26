#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  s21_rescale(&value_1, &value_2);
  s21_big_decimal big_value_1 = s21_convert_std_to_big(value_1);
  s21_big_decimal big_value_2 = s21_convert_std_to_big(value_2);
  s21_big_decimal big_result;
  s21_null_big_decimal(&big_result);
  if (big_value_1.sign == big_value_2.sign) {
    if ((s21_is_greater_or_equal(value_1, value_2) && !big_value_1.sign) ||
        (s21_is_less_or_equal(value_1, value_2) && big_value_1.sign)) {
      return_code = s21_sub_big(big_value_1, big_value_2, &big_result);
    } else {
      big_value_1.sign = big_value_1.sign ^ 1;
      big_value_2.sign = big_value_2.sign ^ 1;
      return_code = s21_sub_big(big_value_2, big_value_1, &big_result);
    }
    big_result.sign = big_value_1.sign;
  } else {
    big_value_2.sign = big_value_2.sign ^ 1;
    value_2 = s21_convert_big_to_std(big_value_2);
    return_code = s21_add(value_1, value_2, result);
    big_result = s21_convert_std_to_big(*result);
  }
  big_result.exp = big_value_1.exp;
  *result = s21_convert_big_to_std(big_result);
  return return_code;
}
