#include "s21_decimal.h"

void s21_truncate_big(s21_big_decimal *big_value) {
  while (big_value->exp > 0) s21_div_by_ten(big_value);
}
