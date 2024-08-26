#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  convertation_result status = 0;
  if (dst) {
    int sign = (s21_get_sign_std(src) ? -1 : 1);
    *dst = src.bits[0] * sign;
  } else {
    status = CONVERTATION_ERROR;
  }
  return status;
}
