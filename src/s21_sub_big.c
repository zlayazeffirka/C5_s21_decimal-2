#include "s21_decimal.h"

int s21_sub_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  int return_code = 0;
  bool t_bit = 0;
  for (int i = 0; i < 192; i++) {
    big_result->bits[i] = big_value_1.bits[i] ^ big_value_2.bits[i] ^ t_bit;
    if (big_value_1.bits[i] == 0 && big_value_2.bits[i] == 1)
      t_bit = 1;
    else if (big_value_1.bits[i] == 1 && big_value_2.bits[i] == 0)
      t_bit = 0;
  }
  return return_code;
}
