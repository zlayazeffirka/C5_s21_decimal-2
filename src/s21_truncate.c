#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *res) {
  int return_code = 1;
  if (res) {
    s21_big_decimal big_value = s21_convert_std_to_big(value);
    s21_truncate_big(&big_value);
    *res = s21_convert_big_to_std(big_value);
    return_code = 0;
  }

  return return_code;
}
