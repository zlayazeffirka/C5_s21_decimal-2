#include <check.h>

#include "../s21_decimal.h"

int get_bit(s21_decimal value, int position);
void set_bit(s21_decimal *value, int position, int digit);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
void set_scale(s21_decimal *value, int scale);

int get_sign(s21_decimal value) { return (get_bit(value, 127)); }
void set_sign(s21_decimal *value, int sign) { set_bit(value, 127, sign); }

void set_bit(s21_decimal *value, int position, int digit) {
  int mask = 1U << (position % 32);
  if (digit == 1) {
    value->bits[position / 32] |= mask;
  } else {
    value->bits[position / 32] &= ~mask;
  }
}

void set_scale(s21_decimal *value, int scale) {
  for (int start_position = 96 + 16; start_position <= 118; start_position++) {
    set_bit(value, start_position, scale % 2);
    scale /= 2;
  }
}

int get_bit(s21_decimal value, int position) {
  return (value.bits[position / 32] >> (position % 32)) & 1U;
}

START_TEST(is_less_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  set_bit(&val1, 83, 1);
  set_scale(&val1, 12);
  set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  set_bit(&val1, 83, 1);
  set_bit(&val2, 83, 1);
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  set_bit(&val1, 83, 1);
  set_scale(&val1, 10);
  set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 0);
  set_bit(&val1, 83, 1);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_greater_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_0) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  set_sign(&val2, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val2, 127, 1);
  set_bit(&val1, 33, 1);
  set_bit(&val2, 33, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_scale(&val1, 3);
  set_scale(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val2, 127, 1);
  set_bit(&val1, 33, 1);
  set_bit(&val2, 33, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_scale(&val1, 3);
  set_scale(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// START_TEST(sub_11) {
//   s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{4, 0, 0, 0}};
//   s21_decimal res;
//   ck_assert_int_eq(2, s21_sub(val1, val2, &res));
// }
// END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// START_TEST(sub_14) {
//   s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
//   s21_decimal res;
//   ck_assert_int_eq(2, s21_sub(val1, val2, &res));
// }
// END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

// START_TEST(add_3) {
//   s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal res;
//   ck_assert_int_eq(2, s21_add(val1, val2, &res));
// }
// END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

// START_TEST(add_12) {
//   s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal res;
//   ck_assert_int_eq(2, s21_add(val1, val2, &res));
// }
// END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

// START_TEST(add_16) {
//   s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
//   s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
//   s21_decimal res;
//   ck_assert_int_eq(2, s21_add(val1, val2, &res));
// }
// END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal val1 = {{123, 123, 123, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(mod_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_4) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(negate_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(floor_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

// START_TEST(round_0) {
//   s21_decimal val = {{7, 7, 7, 0}};
//   s21_decimal res = {0};
//   s21_round(val, &res);
//   float fres = 0;
//   s21_from_decimal_to_float(res, &fres);
//   float need = 129127208515966861312.0;
//   ck_assert_float_eq(need, fres);
// }
// END_TEST

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_9) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_float_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = -1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = 1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

// END_TEST

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(mod_test_1) {
  int num1 = 3;
  int num2 = 2;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_2) {
  int num1 = -98765;
  int num2 = 1234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_3) {
  int num1 = 30198;
  int num2 = 20210;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_4) {
  int num1 = -98765;
  int num2 = -1234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_5) {
  int num1 = 98765;
  int num2 = 127234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_6) {
  int num1 = 342576;
  int num2 = 1542134;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_7) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 99;
  int tmp2 = 2;
  int res_s21 = 0;
  int res = tmp1 % tmp2;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_mod(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(mod_test_8) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 2;
  int res_s21 = 0;
  float res = tmp1 % tmp2;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_mod(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(mod_test_9) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = 2;
  float res_s21 = 0;
  float res = tmp1 % tmp2;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_mod(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq(res_s21, res);
}
END_TEST

START_TEST(mod_test_10) {
  s21_decimal dec1;
  s21_decimal dec2;
  float tmp1 = 0.2505;
  float tmp2 = 0.25;
  float res_s21 = 0.0;
  float res = fmod(tmp1, tmp2);
  s21_from_float_to_decimal(tmp1, &dec1);
  s21_from_float_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_mod(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal val;
  float num = -2.1474836E+09;
  s21_from_float_to_decimal(num, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal dec;
  s21_decimal ans;
  s21_init_decimal(&dec);
  dec.bits[0] = 2814903;
  dec.bits[3] = 65536 + MINUS_SIGN;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[3] = 65536;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(negate_5) {
  s21_decimal dec;
  s21_decimal ans;
  s21_init_decimal(&dec);
  dec.bits[0] = 2814903;
  dec.bits[1] = 2384901;
  dec.bits[2] = 27498;
  dec.bits[3] = 0;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[1] = 2384901;
  true_ans.bits[2] = 27498;
  true_ans.bits[3] = MINUS_SIGN;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  // s21_is_less
  tcase_add_test(tc1_1, is_less_0);
  tcase_add_test(tc1_1, is_less_1);
  tcase_add_test(tc1_1, is_less_2);
  tcase_add_test(tc1_1, is_less_3);
  tcase_add_test(tc1_1, is_less_4);
  tcase_add_test(tc1_1, is_less_5);
  tcase_add_test(tc1_1, is_less_6);
  tcase_add_test(tc1_1, is_less_7);
  tcase_add_test(tc1_1, is_less_8);
  tcase_add_test(tc1_1, is_less_9);
  tcase_add_test(tc1_1, is_less_10);
  tcase_add_test(tc1_1, is_less_11);
  tcase_add_test(tc1_1, is_less_12);
  // s21_is_greater
  tcase_add_test(tc1_1, is_greater_0);
  tcase_add_test(tc1_1, is_greater_1);
  tcase_add_test(tc1_1, is_greater_2);
  tcase_add_test(tc1_1, is_greater_3);
  tcase_add_test(tc1_1, is_greater_4);
  tcase_add_test(tc1_1, is_greater_5);
  tcase_add_test(tc1_1, is_greater_6);
  tcase_add_test(tc1_1, is_greater_7);
  tcase_add_test(tc1_1, is_greater_8);
  // s21_is_greater_or_equal
  tcase_add_test(tc1_1, is_greater_or_equal_0);
  tcase_add_test(tc1_1, is_greater_or_equal_1);
  tcase_add_test(tc1_1, is_greater_or_equal_2);
  tcase_add_test(tc1_1, is_greater_or_equal_3);
  tcase_add_test(tc1_1, is_greater_or_equal_4);
  tcase_add_test(tc1_1, is_greater_or_equal_5);
  tcase_add_test(tc1_1, is_greater_or_equal_6);
  tcase_add_test(tc1_1, is_greater_or_equal_7);
  // s21_is_less_or_equal
  tcase_add_test(tc1_1, is_less_or_equal_0);
  tcase_add_test(tc1_1, is_less_or_equal_1);
  tcase_add_test(tc1_1, is_less_or_equal_2);
  tcase_add_test(tc1_1, is_less_or_equal_3);
  tcase_add_test(tc1_1, is_less_or_equal_4);
  tcase_add_test(tc1_1, is_less_or_equal_5);
  tcase_add_test(tc1_1, is_less_or_equal_6);
  tcase_add_test(tc1_1, is_less_or_equal_7);
  // s21_is_equal
  tcase_add_test(tc1_1, is_equal_0);
  tcase_add_test(tc1_1, is_equal_1);
  tcase_add_test(tc1_1, is_equal_2);
  tcase_add_test(tc1_1, is_equal_3);
  tcase_add_test(tc1_1, is_equal_4);
  tcase_add_test(tc1_1, is_equal_5);
  tcase_add_test(tc1_1, is_equal_6);
  tcase_add_test(tc1_1, is_equal_7);
  tcase_add_test(tc1_1, is_equal_8);
  // s21_is_not_equal
  tcase_add_test(tc1_1, is_not_equal_0);
  tcase_add_test(tc1_1, is_not_equal_1);
  tcase_add_test(tc1_1, is_not_equal_2);
  tcase_add_test(tc1_1, is_not_equal_3);
  tcase_add_test(tc1_1, is_not_equal_4);
  tcase_add_test(tc1_1, is_not_equal_5);
  tcase_add_test(tc1_1, is_not_equal_6);
  tcase_add_test(tc1_1, is_not_equal_7);
  tcase_add_test(tc1_1, is_not_equal_8);
  // s21_sub
  tcase_add_test(tc1_1, sub_0);
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_12);
  tcase_add_test(tc1_1, sub_13);
  tcase_add_test(tc1_1, sub_15);
  tcase_add_test(tc1_1, sub_16);
  tcase_add_test(tc1_1, sub_17);
  tcase_add_test(tc1_1, sub_18);
  tcase_add_test(tc1_1, sub_19);
  tcase_add_test(tc1_1, sub_20);
  tcase_add_test(tc1_1, sub_21);
  // s21_add
  tcase_add_test(tc1_1, add_0);
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
  // s21_mul
  tcase_add_test(tc1_1, mul_0);
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, mul_8);
  tcase_add_test(tc1_1, mul_10);
  tcase_add_test(tc1_1, mul_11);
  // s21_div
  tcase_add_test(tc1_1, div_0);
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  // s21_mod
  tcase_add_test(tc1_1, mod_0);
  tcase_add_test(tc1_1, mod_1);
  tcase_add_test(tc1_1, mod_2);
  tcase_add_test(tc1_1, mod_3);
  tcase_add_test(tc1_1, mod_4);
  tcase_add_test(tc1_1, mod_test_1);
  tcase_add_test(tc1_1, mod_test_2);
  tcase_add_test(tc1_1, mod_test_3);
  tcase_add_test(tc1_1, mod_test_4);
  tcase_add_test(tc1_1, mod_test_5);
  tcase_add_test(tc1_1, mod_test_6);
  tcase_add_test(tc1_1, mod_test_7);
  tcase_add_test(tc1_1, mod_test_8);
  tcase_add_test(tc1_1, mod_test_9);
  tcase_add_test(tc1_1, mod_test_10);
  // negate
  tcase_add_test(tc1_1, negate_0);
  tcase_add_test(tc1_1, negate_1);
  tcase_add_test(tc1_1, negate_2);
  tcase_add_test(tc1_1, negate_3);
  tcase_add_test(tc1_1, negate_4);
  tcase_add_test(tc1_1, negate_5);
  // round
  tcase_add_test(tc1_1, round_1);
  tcase_add_test(tc1_1, round_2);
  tcase_add_test(tc1_1, round_3);
  tcase_add_test(tc1_1, round_4);
  tcase_add_test(tc1_1, round_5);
  tcase_add_test(tc1_1, round_6);
  tcase_add_test(tc1_1, round_7);
  tcase_add_test(tc1_1, round_8);
  tcase_add_test(tc1_1, round_9);
  // truncate
  tcase_add_test(tc1_1, truncate_1);
  tcase_add_test(tc1_1, truncate_2);
  tcase_add_test(tc1_1, truncate_3);
  tcase_add_test(tc1_1, truncate_4);
  // floor
  tcase_add_test(tc1_1, floor_0);
  tcase_add_test(tc1_1, floor_1);
  tcase_add_test(tc1_1, floor_2);
  tcase_add_test(tc1_1, floor_3);
  // from_decimal_to_float
  tcase_add_test(tc1_1, from_decimal_to_float_0);
  tcase_add_test(tc1_1, from_decimal_to_float_1);
  // from_float_to_decimal
  tcase_add_test(tc1_1, from_float_to_decimal_0);
  tcase_add_test(tc1_1, from_float_to_decimal_1);
  tcase_add_test(tc1_1, from_float_to_decimal_2);

  tcase_add_test(tc1_1, from_int_to_decimal_0);  // from_int_to_decimal
  tcase_add_test(tc1_1, from_int_to_decimal_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == FAIL ? FAIL : SUCCES;
}