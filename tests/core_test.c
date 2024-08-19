#include "test.h"

START_TEST(test_s21_is_valid_dec) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));

  // not allowed bits
  s21_clean_dec(dec1);
  dec1->bits[3] = 1 << 29;
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);

  s21_clean_dec(dec1);
  dec1->bits[3] = 1;
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);

  s21_clean_dec(dec1);
  dec1->bits[3] = 1 << 14;
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);

  s21_clean_dec(dec1);
  dec1->bits[3] = 1 << 4;
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);

  // not allowed scale
  s21_clean_dec(dec1);
  dec1->bits[3] = 29 << 16;
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);
  s21_set_scale(dec1, 13123);
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);
  s21_clean_dec(dec1);
  dec1->bits[3] = 1 << 21;
  ck_assert_int_eq(s21_is_valid_dec(dec1), FALSE);

  // ok
  s21_clean_dec(dec1);
  ck_assert_int_eq(s21_is_valid_dec(dec1), TRUE);
  s21_clean_dec(dec1);
  dec1->bits[3] = 28 << 16;
  ck_assert_int_eq(s21_is_valid_dec(dec1), TRUE);
  s21_clean_dec(dec1);
  dec1->bits[1] = 1 << 29;
  dec1->bits[2] = 1 << 29;
  ck_assert_int_eq(s21_is_valid_dec(dec1), TRUE);
  s21_clean_dec(dec1);
  dec1->bits[1] = 1 << 5;
  dec1->bits[2] = 1 << 5;
  ck_assert_int_eq(s21_is_valid_dec(dec1), TRUE);
  s21_clean_dec(dec1);
  dec1->bits[2] = ~0;
  s21_set_scale(dec1, 28);
  ck_assert_int_eq(s21_is_valid_dec(dec1), TRUE);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_copy_dec) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *res = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(res);

  s21_copy_dec(dec1, res);
  ck_assert_int_eq(dec1->bits[0], res->bits[0]);
  ck_assert_int_eq(dec1->bits[1], res->bits[1]);
  ck_assert_int_eq(dec1->bits[2], res->bits[2]);
  ck_assert_int_eq(dec1->bits[3], res->bits[3]);
  ck_assert_int_eq(s21_is_equal(*dec1, *res), TRUE);

  s21_clean_dec(dec1);
  s21_clean_dec(res);
  dec1->bits[0] = 1;
  dec1->bits[1] = ~0;
  dec1->bits[2] = 1 << 31;
  dec1->bits[3] = 54;

  s21_set_scale(dec1, 28);

  s21_copy_dec(dec1, res);
  ck_assert_int_eq(dec1->bits[0], res->bits[0]);
  ck_assert_int_eq(dec1->bits[1], res->bits[1]);
  ck_assert_int_eq(dec1->bits[2], res->bits[2]);
  ck_assert_int_eq(dec1->bits[3], res->bits[3]);
  ck_assert_int_eq(s21_is_equal(*dec1, *res), TRUE);

  s21_free_dec(&dec1);
  s21_free_dec(&res);
}
END_TEST

Suite *suite_core(void) {
  Suite *s = suite_create("core");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, test_s21_is_valid_dec);
  tcase_add_test(tcase_core, test_s21_copy_dec);

  suite_add_tcase(s, tcase_core);

  return s;
}