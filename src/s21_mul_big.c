#include "s21_decimal.h"

// big cock - small brain

int s21_mul_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  int return_code = 0;
  s21_null_big_decimal(big_result);
  if (!s21_is_null(big_value_1) && !(s21_is_null(big_value_2))) {
    for (int i = 0; i < 192; i++) {
      if (big_value_2.bits[i] == 1)
        s21_add_big(*big_result, big_value_1, big_result);
      s21_left_shift(&big_value_1);
    }
    big_result->exp = big_value_1.exp + big_value_2.exp;
    big_result->sign = big_value_1.sign ^ big_value_2.sign;
    if (s21_last_bit(*big_result) > 95 || big_result->exp > 28) {
      int mod = 0;
      while (big_result->exp > 0 &&
             (s21_last_bit(*big_result) > 95 || big_result->exp > 28)) {
        if (big_result->exp == 0) break;
        mod = s21_div_by_ten(big_result);
      }
      if (big_result->exp > 0)
        s21_bank_rounding(big_result, mod);
      else
        return_code = 1;
    }
    if (s21_is_null(*big_result)) return_code = 2;
  }
  return return_code;
}
