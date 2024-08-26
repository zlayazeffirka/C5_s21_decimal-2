#include "s21_decimal.h"

bool s21_get_bit_int(unsigned int num, int pos) {
  bool res = (num >> pos) & 1;
  return res;
}

void s21_right_shift(s21_big_decimal *big) {
  for (int i = 0; i < 191; i++) {
    big->bits[i] = big->bits[i + 1];
  }
  big->bits[191] = 0;
}

void s21_left_shift(s21_big_decimal *big) {
  for (int i = 191; i > 0; i--) {
    big->bits[i] = big->bits[i - 1];
  }
  big->bits[0] = 0;
}

bool s21_get_sign_std(s21_decimal dec) {
  return s21_get_bit_int(dec.bits[3], 31);
}

int s21_get_exp_std(s21_decimal dec) {
  return (dec.bits[3] % 2147483648) >> 16;
}

void s21_null_big_decimal(s21_big_decimal *big) {
  big->sign = 0;
  big->exp = 0;
  for (int i = 0; i < 192; i++) big->bits[i] = 0;
}

void s21_init_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

bool s21_compare_bits(s21_big_decimal big1, s21_big_decimal big2) {
  int i = 191;
  while (i >= 0 && big1.bits[i] == big2.bits[i]) {
    i--;
  }
  return i == -1 ? 1 : big1.bits[i];
}

bool s21_is_null(s21_big_decimal big) {
  bool result = 0;
  for (int i = 0; i < 192; i++) {
    result += big.bits[i];
  }
  return !result;
}

int s21_last_bit(s21_big_decimal big) {
  int i = -1;
  if (!s21_is_null(big)) {
    for (i = 191; i >= 0; i--) {
      if (big.bits[i] == 1) {
        break;
      }
    }
  }
  return i;
}

void s21_align(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
  if (!s21_is_null(*big_value_1) && !s21_is_null(*big_value_2)) {
    int l1 = s21_last_bit(*big_value_1);
    int l2 = s21_last_bit(*big_value_2);

    while (s21_last_bit(*big_value_1) != s21_last_bit(*big_value_2))
      if (s21_compare_bits(*big_value_1, *big_value_2)) {
        s21_left_shift(big_value_2);
      } else {
        s21_left_shift(big_value_1);
      }
    if (!s21_compare_bits(*big_value_1, *big_value_2)) {
      s21_left_shift(big_value_1);
    }

    if (big_value_1->bits[0] == 0 && big_value_2->bits[0] == 0 &&
        s21_last_bit(*big_value_1) > l1 && s21_last_bit(*big_value_2) > l2) {
      s21_right_shift(big_value_1);
      s21_right_shift(big_value_2);
    }
  }
}

void s21_rescale_big_to_smaller(s21_big_decimal *big_value_1,
                                s21_big_decimal *big_value_2) {
  int mod1 = 0, mod2 = 0;
  while (s21_last_bit(*big_value_2) > 95) {
    mod1 = s21_div_by_ten(big_value_1);
    mod2 = s21_div_by_ten(big_value_2);
  }
  s21_bank_rounding(big_value_1, mod1);
  s21_bank_rounding(big_value_2, mod2);
  if (s21_last_bit(*big_value_2) > 95) {
    mod1 = s21_div_by_ten(big_value_1);
    mod2 = s21_div_by_ten(big_value_2);
    s21_bank_rounding(big_value_1, mod1);
    s21_bank_rounding(big_value_2, mod2);
  }
}