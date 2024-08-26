#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *res) {
  int return_code = 1;
  if (res) {
    s21_big_decimal big_value = s21_convert_std_to_big(value);
    int mod = 0;
    while (big_value.exp > 0) mod = s21_div_by_ten(&big_value);
    if (mod >= 5) {
      s21_big_decimal one;
      s21_null_big_decimal(&one);
      one.bits[0] = 1;
      one.sign = big_value.sign;
      s21_add_big(one, big_value, &big_value);
    }
    *res = s21_convert_big_to_std(big_value);
    return_code = 0;
  }
  return return_code;
}
