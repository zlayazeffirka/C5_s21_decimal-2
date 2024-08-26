#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *res) {
  operation_result result = 1;
  if (res) {
    result = OPERATION_OK;
    value.bits[3] ^= MINUS_SIGN;
    *res = value;
  }

  return result;
}
