#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *res) {
  int return_code = 0;
  if (res) {
    s21_big_decimal big_value = s21_convert_std_to_big(value);
    s21_truncate_big(&big_value);
    if (big_value.sign &&
        s21_is_not_equal(s21_convert_big_to_std(big_value), value)) {
      s21_big_decimal one;
      s21_null_big_decimal(&one);
      one.bits[0] = 1;
      one.sign = 1;
      s21_add_big(one, big_value, &big_value);
    }
    *res = s21_convert_big_to_std(big_value);
  } else {
    return_code = 1;
  }
  return return_code;
}
