#include "s21_decimal.h"

s21_big_decimal s21_convert_std_to_big(s21_decimal std) {
  s21_big_decimal big;
  s21_null_big_decimal(&big);
  big.sign = s21_get_sign_std(std);
  big.exp = s21_get_exp_std(std);
  int i = 0;
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 32; k++)
      big.bits[i++] = s21_get_bit_int(std.bits[j], k);
  }
  return big;
}

s21_decimal s21_convert_big_to_std(s21_big_decimal big) {
  s21_decimal std;
  s21_init_decimal(&std);
  int k = 95;
  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      std.bits[i] = (std.bits[i] << 1) + big.bits[k--];
    }
  }

  std.bits[3] = big.sign;
  std.bits[3] <<= 7;
  k = 128;
  for (int i = 7; i >= 0; i--) {
    std.bits[3] <<= 1;
    if (big.exp >= k) {
      big.exp -= k;
      std.bits[3]++;
    }
    k >>= 1;
  }
  std.bits[3] <<= 16;
  return std;
}

s21_decimal s21_convert_int_to_std(unsigned long int number) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  s21_big_decimal big_decimal;
  big_decimal = s21_convert_int_to_big(number);
  decimal = s21_convert_big_to_std(big_decimal);
  return decimal;
}

s21_big_decimal s21_convert_int_to_big(unsigned long int number) {
  s21_big_decimal big;
  s21_null_big_decimal(&big);
  int i = 0;
  while (number >= 1) {
    if (number % 2 == 1) {
      big.bits[i] = 1;
    }
    i++;
    number /= 2;
  }
  return big;
}
