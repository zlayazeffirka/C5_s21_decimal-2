#include "s21_decimal.h"

int s21_div_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  s21_big_decimal ten;
  s21_null_big_decimal(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_null_big_decimal(big_result);
  int return_code = 0;
  bool sign = big_value_1.sign ^ big_value_2.sign;
  big_value_1.sign = 0;
  big_value_2.sign = 0;

  s21_rescale_big_to_zero(&big_value_1, &big_value_2);
  s21_big_decimal modulo;
  s21_null_big_decimal(&modulo);
  modulo = s21_div_with_modulo(big_value_1, big_value_2, &big_value_1);
  int exp = 0;
  int status = 0;
  while (!s21_is_null(big_value_1) || !s21_is_null(modulo)) {
    exp++;
    s21_mul_big(modulo, ten, &modulo);
    s21_mul_big(*big_result, ten, big_result);
    status = s21_add_big(*big_result, big_value_1, big_result);
    modulo = s21_div_with_modulo(modulo, big_value_2, &big_value_1);
    if (status == 1) break;
  }
  int mod;
  if (status == 1) {
    mod = s21_div_by_ten(big_result);
    while (s21_last_bit(*big_result) > 95 && exp > 0) {
      mod = s21_div_by_ten(big_result);
      exp--;
    }
    s21_bank_rounding(big_result, mod);
    exp--;
  }
  big_result->exp = exp - 1;
  mod = 10;
  while (big_result->exp > 28) mod = s21_div_by_ten(big_result);
  if (s21_is_null(*big_result))
    return_code = 2;
  else if (mod != 10)
    s21_bank_rounding(big_result, mod);
  if (s21_last_bit(*big_result) > 95) return_code = 1;
  big_result->sign = sign;
  return return_code;
}

s21_big_decimal s21_div_with_modulo(s21_big_decimal big_value_1,
                                    s21_big_decimal big_value_2,
                                    s21_big_decimal *big_result) {
  int denominator_left_bit = s21_last_bit(big_value_2);
  s21_big_decimal modulo;
  s21_null_big_decimal(&modulo);
  s21_null_big_decimal(big_result);
  if (s21_compare_bits(big_value_1, big_value_2)) {
    s21_align(&big_value_1, &big_value_2);
  }
  for (int i = 0; i < 191; i++) {
    if (s21_compare_bits(big_value_1, big_value_2)) {
      s21_sub_big(big_value_1, big_value_2, &big_value_1);
      big_result->bits[0] = 1;
    }
    if (s21_last_bit(big_value_2) <= denominator_left_bit) break;
    if (s21_last_bit(big_value_2) > denominator_left_bit)
      s21_right_shift(&big_value_2);
    s21_left_shift(big_result);
  }
  return big_value_1;
}
