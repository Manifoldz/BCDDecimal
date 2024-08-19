#include "test.h"

START_TEST(test_s21_is_less) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  int result = 0;
  // -0 < 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec1);
  // s21_set_bit(dec1, 95);
  // s21_print_scale(*dec1);
  // s21_print_bin_dec(*dec1);
  // s21_set_scale(dec1, 3);
  dec2->bits[0] = 0;

  result = s21_is_less(*dec1, *dec2);

  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 < 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 < -0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 < 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 0;

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 < 10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -10 < 10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;
  s21_set_sign(dec1);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 < -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 100 < -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -100 < -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-100 * 10^-2) < -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-1000 * 10^-2) < -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 1000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-10000 * 10^-2) < -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 * 10^-1 < 1000 * 10^-3 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 1000;

  // s21_set_sign(dec1);
  // s21_set_sign(dec2);
  s21_set_scale(dec1, 1);
  s21_set_scale(dec2, 3);

  result = s21_is_less(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  int result = 0;
  // -0 <= 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec2->bits[0] = 0;

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 <= 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 <= -0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 <= 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 0;

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 <= 10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -10 <= 10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;
  s21_set_sign(dec1);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 <= -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 100 <= -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -100 <= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-100 * 10^-2) <= -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-1000 * 10^-2) <= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 1000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-10000 * 10^-2) <= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_less_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
}
END_TEST

START_TEST(test_s21_is_greater) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  int result = 0;
  // -0 > 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec2->bits[0] = 0;

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 > 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 > -0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 > 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 0;

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 > 10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -10 > 10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;
  s21_set_sign(dec1);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 > -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 100 > -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -100 > -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-100 * 10^-2) > -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-1000 * 10^-2) > -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 1000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-10000 * 10^-2) > -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_greater(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  int result = 0;
  // -0 >= 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec2->bits[0] = 0;

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 >= 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 >= -0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 >= 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 0;

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 >= 10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -10 >= 10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;
  s21_set_sign(dec1);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 >= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 100 >= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -100 >= -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-100 * 10^-2) >= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-1000 * 10^-2) >= -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 1000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-10000 * 10^-2) >= -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_greater_or_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
}
END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  int result = 0;
  // -0 == 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec2->bits[0] = 0;

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 == 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 == -0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 == 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 0;

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 == 10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -10 == 10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;
  s21_set_sign(dec1);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 == -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 100 == -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -100 == -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-100 * 10^-2) == -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-1000 * 10^-2) == -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 1000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-10000 * 10^-2) == -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 70 * 10^-1 == 7 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 70;
  dec2->bits[0] = 7;

  s21_set_scale(dec1, 1);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -21,21300 == -21,213 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 2121300;
  dec2->bits[0] = 21213;

  s21_set_scale(dec1, 5);
  s21_set_sign(dec1);
  s21_set_scale(dec2, 3);
  s21_set_sign(dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -01,0 == -1,0 -> true

  s21_str_to_dec("-01,0", dec1);
  s21_str_to_dec("-1,0", dec2);

  result = s21_is_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
}
END_TEST

START_TEST(test_s21_is_not_equal) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  int result = 0;
  // -0 != 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec2->bits[0] = 0;

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 != 0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 0 != -0 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 != 0 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 0;

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 != 10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -10 != 10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;
  s21_set_sign(dec1);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 10 != -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // 100 != -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // -100 != -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-100 * 10^-2) != -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 100;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-1000 * 10^-2) != -10 -> false
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 1000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  // (-10000 * 10^-2) != -10 -> true
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 10000;
  dec2->bits[0] = 10;

  s21_set_sign(dec1);
  s21_set_sign(dec2);
  s21_set_scale(dec1, 2);

  result = s21_is_not_equal(*dec1, *dec2);
  if (result != kErrMemory) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(result, kErrMemory);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
}
END_TEST

START_TEST(test_s21_bcd_more_max_mantissa) {
  int res = 0;
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // 15845632502852 8675187087900675
  bcd1->number[0] = 9688677044947256949ULL;
  bcd1->number[1] = 6056480257091666ULL;
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 1);
  }

  s21_clean_bcd(bcd1);

  // 15845632502852867518708790068
  // 1584563250285 2867518708790068

  bcd1->number[0] = 2911385324522897512ULL;
  bcd1->number[1] = 378530016068229ULL;

  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_bcd_mantissa_compare) {
  int res = 0;
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  bcd *bcd2 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  // the same
  bcd1->number[0] = 4843438009562235701ULL;
  bcd1->number[1] = 2131025704850470ULL;

  bcd2->number[0] = 4843438009562235701ULL;
  bcd2->number[1] = 2131025704850470ULL;

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 1), 0);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 1), 0);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // 1>2
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  bcd1->number[0] = 4843438009562235701ULL;
  bcd1->number[1] = 2131025704850470ULL;

  bcd2->number[0] = 4843438009562235701ULL;

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 1), 1);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 1), -1);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // 1>2 anyway
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  bcd1->number[0] = 4843438009562235701ULL;
  bcd1->number[1] = 2131025704850470ULL;

  bcd1->scale = 28;

  bcd2->number[0] = 4843438009562235701ULL;

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 1), 1);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 1), -1);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // third arg 0 the same
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  s21_str_to_bcd("123456789", bcd1);
  s21_str_to_bcd("123456,789", bcd2);

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 0), 0);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 0), 0);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // third arg 0 first negative
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  s21_str_to_bcd("-123456789", bcd1);
  s21_str_to_bcd("123456789", bcd2);

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 0), 0);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 0), 0);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // third arg 0 second negative
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  s21_str_to_bcd("123456789", bcd1);
  s21_str_to_bcd("-123456789", bcd2);

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 0), 0);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 0), 0);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // third arg 0 both negative
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  s21_str_to_bcd("-123456789", bcd1);
  s21_str_to_bcd("-123456789", bcd2);

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 0), 0);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 0), 0);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // third arg 0 first less
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  s21_str_to_bcd("123456788", bcd1);
  s21_str_to_bcd("123456789", bcd2);

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 0), -1);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 0), 1);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  // third arg 0 first more
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);

  s21_str_to_bcd("123456789", bcd1);
  s21_str_to_bcd("123456788", bcd2);

  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd1, bcd2, 0), 1);
  ck_assert_int_eq(s21_bcd_mantissa_compare(bcd2, bcd1, 0), -1);
  res = s21_bcd_more_than_max_dec(bcd1, 0);
  if (res != kErrMemory) {
    ck_assert_int_eq(res, 0);
  }

  s21_free_bcd(&bcd1);

  s21_free_bcd(&bcd2);
}
END_TEST

Suite *suite_compares(void) {
  Suite *s = suite_create("compares");
  TCase *tcase_core = tcase_create("compares");
  // tcase_add_test(tcase_core, test_s21_compare);
  tcase_add_test(tcase_core, test_s21_is_less);
  tcase_add_test(tcase_core, test_s21_is_less_or_equal);
  tcase_add_test(tcase_core, test_s21_is_greater);
  tcase_add_test(tcase_core, test_s21_is_greater_or_equal);
  tcase_add_test(tcase_core, test_s21_is_equal);
  tcase_add_test(tcase_core, test_s21_is_not_equal);
  tcase_add_test(tcase_core, test_s21_bcd_mantissa_compare);
  tcase_add_test(tcase_core, test_s21_bcd_more_max_mantissa);

  suite_add_tcase(s, tcase_core);

  return s;
}