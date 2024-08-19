#include "test.h"

START_TEST(test_is_bit_set_dec) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  int res = 1;

  // False all
  for (int i = 0; i < BITS_IN_DEC; i++) {
    res = s21_is_bit_set(dec1, i);
    ck_assert_int_eq(res, FALSE);
  }
  // 100 (2)
  dec1->bits[0] = 4;
  res = s21_is_bit_set(dec1, 2);
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set(dec1, 0);
  ck_assert_int_eq(res, FALSE);
  // 0111111111111111111111111111111
  dec1->bits[1] = 2147483647;
  res = s21_is_bit_set(dec1, 16 + BITS_IN_INT);
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set(dec1, 31 + BITS_IN_INT);
  ck_assert_int_eq(res, FALSE);

  // 10101010100
  dec1->bits[2] = 1364;
  res = s21_is_bit_set(dec1, 2 + (BITS_IN_INT * 2));
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set(dec1, 3 + (BITS_IN_INT * 2));
  ck_assert_int_eq(res, FALSE);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_is_bit_set_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  int res = 1;
  // False all
  for (int i = 0; i < BITS_IN_BCD; i++) {
    res = s21_is_bit_set_bcd(bcd1, i);
    ck_assert_int_eq(res, FALSE);
  }
  // ..010 (1)
  bcd1->number[0] = 2ULL;
  res = s21_is_bit_set_bcd(bcd1, 1);
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set_bcd(bcd1, 2);
  ck_assert_int_eq(res, FALSE);
  // ...0111111111111111111111111111111
  bcd1->number[1] = 2147483647ULL;
  res = s21_is_bit_set_bcd(bcd1, 9 + BITS_IN_ULLINT);
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set_bcd(bcd1, 31 + BITS_IN_ULLINT);
  ck_assert_int_eq(res, FALSE);
  // ...01000  (3)
  bcd1->number[2] = 8ULL;
  res = s21_is_bit_set_bcd(bcd1, 3 + (BITS_IN_ULLINT * 2));
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set_bcd(bcd1, 2 + (BITS_IN_ULLINT * 2));
  ck_assert_int_eq(res, FALSE);
  // ...010101010100
  bcd1->number[3] = 1364ULL;
  res = s21_is_bit_set_bcd(bcd1, 4 + (BITS_IN_ULLINT * 3));
  ck_assert_int_eq(res, TRUE);
  res = s21_is_bit_set_bcd(bcd1, 5 + (BITS_IN_ULLINT * 3));
  ck_assert_int_eq(res, FALSE);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_set_bit) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  s21_set_bit(dec1, 1);
  ck_assert_int_eq(dec1->bits[0], 1 << 1);

  s21_set_bit(dec1, 2 + BITS_IN_INT);
  s21_set_bit(dec1, 0 + BITS_IN_INT);
  ck_assert_int_eq(dec1->bits[1], 5);

  s21_set_bit(dec1, 31 + (BITS_IN_INT * 2));
  //-2147483648
  ck_assert_int_eq(dec1->bits[2], 1 << 31);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_unset_bit) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  dec1->bits[0] = 4;
  dec1->bits[1] = 8;
  dec1->bits[2] = 1024;

  ck_assert_int_eq(dec1->bits[0], 4);
  s21_unset_bit(dec1, 2);
  ck_assert_int_eq(dec1->bits[0], 0);

  ck_assert_int_eq(dec1->bits[1], 8);
  s21_unset_bit(dec1, 3 + BITS_IN_INT);
  ck_assert_int_eq(dec1->bits[1], 0);

  ck_assert_int_eq(dec1->bits[2], 1024);
  s21_unset_bit(dec1, 10 + (BITS_IN_INT * 2));
  ck_assert_int_eq(dec1->bits[2], 0);

  s21_free_dec(&dec1);
}

START_TEST(test_s21_set_bit_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);
  // 10101010100
  bcd1->number[0] = 1364ULL;
  s21_set_bit_bcd(bcd1, 3);
  // 10101011100
  ck_assert_uint_eq(bcd1->number[0], 1372ULL);

  s21_set_bit_bcd(bcd1, 2 + BITS_IN_ULLINT);
  s21_set_bit_bcd(bcd1, 0 + BITS_IN_ULLINT);
  // 5
  ck_assert_uint_eq(bcd1->number[1], 5ULL);

  s21_set_bit_bcd(bcd1, 31 + (BITS_IN_ULLINT * 2));
  // 2147483648
  ck_assert_uint_eq(bcd1->number[2], 1ULL << 31);

  s21_set_bit_bcd(bcd1, 63 + (BITS_IN_ULLINT * 3));
  // 9223372036854775808
  ck_assert_uint_eq(bcd1->number[3], 1ULL << 63);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_unset_bit_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->number[0] = 5ULL;
  s21_unset_bit_bcd(bcd1, 1);
  ck_assert_uint_eq(bcd1->number[0], 5ULL);

  bcd1->number[1] = 1ULL << 63;
  s21_unset_bit_bcd(bcd1, 63 + BITS_IN_ULLINT);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);

  bcd1->number[2] = 1ULL << 0;
  s21_unset_bit_bcd(bcd1, 0 + (BITS_IN_ULLINT * 2));
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  // 10101011100
  bcd1->number[3] = 1372ULL;
  s21_unset_bit_bcd(bcd1, 3 + (BITS_IN_ULLINT * 3));
  // 10101010100
  ck_assert_uint_eq(bcd1->number[3], 1364ULL);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_left_shift_dec) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  dec1->bits[0] = 4;
  dec1->bits[1] = -2147483648;
  dec1->bits[2] = 1024;

  s21_left_shift_dec(dec1);
  ck_assert_int_eq(dec1->bits[0], 1 << 3);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], (1 << 11) + 1);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_left_shift_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->number[0] = 4ULL;
  bcd1->number[1] = 3ULL;
  bcd1->number[2] = 9223372036854775808ULL;
  bcd1->number[3] = 1025ULL;

  s21_left_shift_bcd(bcd1);

  ck_assert_uint_eq(bcd1->number[0], 4ULL << 1);
  ck_assert_uint_eq(bcd1->number[1], 6ULL);
  ck_assert_uint_eq(bcd1->number[2], 9223372036854775808ULL << 1);
  ck_assert_uint_eq(bcd1->number[3], (1025ULL << 1) + 1);

  s21_free_bcd(&bcd1);
  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_right_shift_dec) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  dec1->bits[0] = 4;
  dec1->bits[1] = 1;
  dec1->bits[2] = ~0 - 2;

  s21_right_shift_dec(dec1);
  ck_assert_int_eq(dec1->bits[0], (1 << 31) + 2);
  ck_assert_int_eq(dec1->bits[1], 1 << 31);
  ck_assert_int_eq(dec1->bits[2], ~(1 << 31) - 1);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_right_shift_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->number[0] = 4ULL;
  bcd1->number[1] = 3ULL;
  bcd1->number[2] = ~0ULL;
  bcd1->number[3] = 1024ULL;

  s21_right_shift_bcd(bcd1);

  ck_assert_uint_eq(bcd1->number[0], 2ULL + (1ULL << (BITS_IN_ULLINT - 1)));
  ck_assert_uint_eq(bcd1->number[1], 1ULL + (1ULL << (BITS_IN_ULLINT - 1)));
  ck_assert_uint_eq(bcd1->number[2], ~0ULL >> 1);
  ck_assert_uint_eq(bcd1->number[3], (1024ULL >> 1));

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_unset_sign) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  dec1->bits[3] = 1 << 31;
  ck_assert_int_eq(dec1->bits[3], 1 << 31);
  s21_unset_sign(dec1);
  ck_assert_int_eq(dec1->bits[3], 0);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_set_sign) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  ck_assert_int_eq(dec1->bits[3], 0);
  s21_set_sign(dec1);
  ck_assert_int_eq(dec1->bits[3], 1 << 31);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_get_sign) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  ck_assert_int_eq(s21_get_sign(dec1), 0);

  dec1->bits[3] = 1 << 31;
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  dec1->bits[3] = 0 << 31;
  ck_assert_int_eq(s21_get_sign(dec1), 0);

  s21_str_to_dec("72228162514264337593543950335", dec1);
  ck_assert_int_eq(s21_get_sign(dec1), 0);

  s21_str_to_dec("722281625142643375,93543950335", dec1);
  ck_assert_int_eq(s21_get_sign(dec1), 0);

  s21_str_to_dec("-72228162514264337593543950335", dec1);
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  s21_str_to_dec("-0", dec1);
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_add) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *result = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_clean_dec(result);

  dec1->bits[0] = 109;
  dec2->bits[0] = 1;

  s21_add(*dec1, *dec2, result);

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
  s21_free_dec(&result);
}
END_TEST

START_TEST(test_s21_get_digit_from_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // 123456789
  // 0001 0010 0011 0100 0101 0110 0111 1000 1001
  bcd1->number[0] = 4886718345ULL;

  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 0), 9);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 1), 8);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 2), 7);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 3), 6);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 4), 5);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 5), 4);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 6), 3);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 7), 2);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 8), 1);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 9), 0);

  // 540000
  // 0101 0100 0000 0000 0000 0000
  bcd1->number[1] = 5505024ULL;
  // here we need to add 1*16 to number
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 22), 0);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 21), 5);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 20), 4);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 19), 0);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_set_digit_to_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // 123456789
  // 0001 0010 0011 0100 0101 0110 0111 1000 1001
  bcd1->number[0] = 4886718345ULL;

  s21_set_digit_to_bcd(bcd1, 0, 2);
  // 0001 0010 0011 0100 0101 0110 0111 1000 0010
  ck_assert_int_eq(bcd1->number[0], 4886718338ULL);

  // 0010000000000000000000000000000100100011010001010110011110000010
  s21_set_digit_to_bcd(bcd1, 15, 2);
  ck_assert_int_eq(bcd1->number[0], 4886718338ULL | (2ULL << 15 * 4));
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 15), 2);

  // 540000
  // 0101 0100 0000 0000 0000 0000
  bcd1->number[1] = 5505024ULL;
  // here we need to add 1*16 to number
  s21_set_digit_to_bcd(bcd1, 22, 3);
  ck_assert_int_eq(bcd1->number[1], 5505024ULL | (3ULL << 6 * 4));
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 23), 0);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 22), 3);
  ck_assert_int_eq(s21_get_digit_from_bcd(*bcd1, 21), 5);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_skip_last_digit_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  s21_skip_last_digit_bcd(bcd1);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  // 10
  bcd1->number[0] = 16ULL;

  s21_skip_last_digit_bcd(bcd1);

  ck_assert_uint_eq(bcd1->number[0], 1ULL);

  bcd1->number[1] = 5ULL << (4 * 5);
  s21_skip_last_digit_bcd(bcd1);
  ck_assert_uint_eq(bcd1->number[1], 5ULL << (4 * 4));

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_find_first_digit_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), -1);

  bcd1->number[3] = 1ULL << 63;
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), 63);

  bcd1->number[3] = 2ULL;
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), 48);

  bcd1->number[3] = 2ULL << (8 * 4);
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), 48 + 8);

  bcd1->number[3] = 0ULL;
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), -1);

  bcd1->number[2] = 1ULL;
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), 32);

  bcd1->number[2] = 0ULL;
  bcd1->number[0] = 1ULL;
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), 0);

  bcd1->number[0] = 1ULL << (4 * 10);
  ck_assert_int_eq(s21_find_first_digit_bcd(bcd1), 10);

  s21_free_bcd(&bcd1);
}
END_TEST

Suite *suite_bits_manipulation(void) {
  Suite *s = suite_create("bits");
  TCase *tcase_core = tcase_create("bits_core");
  tcase_add_test(tcase_core, test_is_bit_set_dec);
  tcase_add_test(tcase_core, test_is_bit_set_bcd);
  tcase_add_test(tcase_core, test_s21_set_bit);
  tcase_add_test(tcase_core, test_s21_unset_bit);
  tcase_add_test(tcase_core, test_s21_set_bit_bcd);
  tcase_add_test(tcase_core, test_s21_unset_bit_bcd);
  tcase_add_test(tcase_core, test_s21_left_shift_dec);
  tcase_add_test(tcase_core, test_s21_left_shift_bcd);
  tcase_add_test(tcase_core, test_s21_right_shift_dec);
  tcase_add_test(tcase_core, test_s21_right_shift_bcd);
  tcase_add_test(tcase_core, test_s21_unset_sign);
  tcase_add_test(tcase_core, test_s21_set_sign);
  tcase_add_test(tcase_core, test_s21_get_sign);
  tcase_add_test(tcase_core, test_s21_add);
  tcase_add_test(tcase_core, test_s21_get_digit_from_bcd);
  tcase_add_test(tcase_core, test_s21_set_digit_to_bcd);
  tcase_add_test(tcase_core, test_s21_skip_last_digit_bcd);
  tcase_add_test(tcase_core, test_s21_find_first_digit_bcd);

  suite_add_tcase(s, tcase_core);

  return s;
}
