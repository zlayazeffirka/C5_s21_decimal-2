#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  convertation_result status;
  if (dst) {
    status = CONVERTATION_OK;
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -(src);
    }
    long int new = (long int)src;
    long int exp = 0;
    while (src - ((float)new / (long int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(long int)(pow(10, exp));
    }
    *dst = s21_convert_int_to_std(new);
    if (sign) {
      s21_set_minus(dst);
    }
    dst->bits[3] += exp << 16;
  } else {
    status = CONVERTATION_ERROR;
  }
  return status;
}

void s21_set_minus(s21_decimal *dst) { dst->bits[3] = 1U << 31; }
