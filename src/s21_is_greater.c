#include "s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int greater = 0;
  int zero_num = 0;
  bool aSign = 0, bSign = 0;
  if ((a.bits[0] + a.bits[1] + a.bits[2] + b.bits[0] + b.bits[1] + b.bits[2]) ==
      0) {
    zero_num = 1;
  }

  aSign = s21_get_sign_std(a);
  bSign = s21_get_sign_std(b);

  if (zero_num) {
    greater = 0;
  } else if ((aSign == 0) && (bSign == 1)) {
    greater = 1;
  } else if ((aSign == 1) && (bSign == 0)) {
    greater = 0;
  } else if (aSign == bSign) {
    s21_rescale(&a, &b);
    for (int i = 2; i >= 0; i--) {
      if (a.bits[i] > b.bits[i]) {
        greater = aSign == 1 ? 0 : 1;
        break;
      } else if (a.bits[i] < b.bits[i]) {
        greater = aSign == 1 ? 1 : 0;
        break;
      }
    }
  }
  return greater;
}
