#include "s21_decimal.h"

int s21_add_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  int return_code = 0;
  bool t_bit = 0;
  s21_null_big_decimal(big_result);
  for (int i = 0; i < 192; i++) {
    big_result->bits[i] = (big_value_1.bits[i] ^ big_value_2.bits[i]) ^ t_bit;
    if ((big_value_1.bits[i] & big_value_2.bits[i]) ||
        (big_value_1.bits[i] & t_bit) || (big_value_2.bits[i] & t_bit))
      t_bit = 1;
    else
      t_bit = 0;
  }
  big_result->exp = big_value_1.exp;
  big_result->sign = big_value_1.sign;
  if (s21_last_bit(*big_result) > 95) {
    if (big_result->exp <= 0) {
      return_code = 1;
    } else {
      int mod = s21_div_by_ten(big_result);
      s21_bank_rounding(big_result, mod);
    }
  }
  return return_code;
}
