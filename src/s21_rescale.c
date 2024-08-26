#include "s21_decimal.h"

void s21_rescale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_big_decimal big_value_1 = s21_convert_std_to_big(*value_1);
  s21_big_decimal big_value_2 = s21_convert_std_to_big(*value_2);
  s21_rescale_big(&big_value_1, &big_value_2);
  *value_1 = s21_convert_big_to_std(big_value_1);
  *value_2 = s21_convert_big_to_std(big_value_2);
}

void s21_rescale_big(s21_big_decimal *big_value_1,
                     s21_big_decimal *big_value_2) {
  s21_big_decimal ten;
  s21_null_big_decimal(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (!s21_is_null(*big_value_1) && !s21_is_null(*big_value_2)) {
    if (big_value_1->exp > big_value_2->exp) {
      int exp_dif = big_value_1->exp - big_value_2->exp;
      for (int i = 0; i < exp_dif; i++)
        s21_mul_big(*big_value_2, ten, big_value_2);
      if (s21_last_bit(*big_value_2) > 95) {
        s21_rescale_big_to_smaller(big_value_1, big_value_2);
      }
      big_value_2->exp = big_value_1->exp;
    } else if (big_value_2->exp > big_value_1->exp) {
      s21_rescale_big(big_value_2, big_value_1);
    }
  } else if (s21_is_null(*big_value_1)) {
    big_value_1->exp = big_value_2->exp;
  } else {
    big_value_2->exp = big_value_1->exp;
  }
}

void s21_rescale_big_to_zero(s21_big_decimal *big_value_1,
                             s21_big_decimal *big_value_2) {
  s21_big_decimal ten;
  s21_null_big_decimal(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (big_value_1->exp > big_value_2->exp) {
    big_value_1->exp -= big_value_2->exp;
    big_value_2->exp = 0;
    while (big_value_1->exp != 0) {
      big_value_1->exp--;
      s21_mul_big(*big_value_2, ten, big_value_2);
    }
  } else {
    big_value_2->exp -= big_value_1->exp;
    big_value_1->exp = 0;
    while (big_value_2->exp != 0) {
      big_value_2->exp--;
      s21_mul_big(*big_value_1, ten, big_value_1);
    }
  }
}
