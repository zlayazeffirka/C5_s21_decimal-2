#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int res = 1;
  int zero_num = 0;
  if ((a.bits[0] + a.bits[1] + a.bits[2] + b.bits[0] + b.bits[1] + b.bits[2]) ==
      0) {
    zero_num = 1;
  }

  bool aSign = s21_get_sign_std(a);
  bool bSign = s21_get_sign_std(b);

  if (zero_num) {
    res = 1;
  } else if (aSign != bSign) {
    res = 0;
  } else {
    s21_rescale(&a, &b);
    for (register int i = 0; i <= 2; i++) {
      if (a.bits[i] != b.bits[i]) {
        res = 0;
      }
    }
  }
  return res;
}
