#include "s21_decimal.h"

// деление числа на 10
// возращает остаток от деления числа на 10
int s21_div_by_ten(s21_big_decimal *big) {
  s21_big_decimal result;
  s21_null_big_decimal(&result);
  int exp = big->exp;
  int sign = big->sign;
  result.sign = 0;
  result.exp = 0;
  s21_big_decimal ten;
  s21_null_big_decimal(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_big_decimal modulo = s21_div_with_modulo(*big, ten, big);
  int res = s21_convert_big_to_std(modulo).bits[0];
  big->exp = exp - 1;
  big->sign = sign;
  return res;
}

void s21_bank_rounding(s21_big_decimal *big, int mod) {
  if ((mod == 5 && big->bits[0]) || mod > 5) {
    s21_big_decimal one;
    s21_null_big_decimal(&one);
    one.bits[0] = 1;
    one.exp = big->exp;
    one.sign = big->sign;
    s21_add_big(*big, one, big);
    if (s21_last_bit(*big) > 95) {
      s21_sub_big(*big, one, big);
      mod = s21_div_by_ten(big);
      s21_bank_rounding(big, mod);
    }
  }
}
