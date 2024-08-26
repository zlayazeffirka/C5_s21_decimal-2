#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    return_code = 3;
  } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[2] == 0) {
    s21_init_decimal(result);
  } else {
    s21_big_decimal big_value_1 = s21_convert_std_to_big(value_1);
    s21_big_decimal big_value_2 = s21_convert_std_to_big(value_2);
    s21_big_decimal big_result;
    s21_null_big_decimal(&big_result);
    while (big_value_1.bits[0] == 0 && big_value_2.bits[0] == 0) {
      s21_right_shift(&big_value_1);
      s21_right_shift(&big_value_2);
    }
    return_code = s21_div_big(big_value_1, big_value_2, &big_result);
    *result = s21_convert_big_to_std(big_result);
  }
  return return_code;
}
