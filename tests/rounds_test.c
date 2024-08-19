#include "test.h"

START_TEST(test_s21_round_positive) {
  int returned_value = 0;
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(reference);

  // zero
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // zero
  s21_str_to_dec("0,009", dec1);
  s21_str_to_dec("0", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("12345", dec1);
  s21_str_to_dec("12345", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("79228162514264337593543950335", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("4327424924274247247,", dec1);
  s21_str_to_dec("4327424924274247247,0", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max up
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("8", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max down
  s21_str_to_dec("7,2228162514264337593543950335", dec1);
  s21_str_to_dec("7", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale random
  s21_str_to_dec("4327424924274,247247", dec1);
  s21_str_to_dec("4327424924274", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border1
  s21_str_to_dec("99999999999999999999999,5", dec1);
  s21_str_to_dec("100000000000000000000000", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border2
  s21_str_to_dec("4327424924274,5", dec1);
  s21_str_to_dec("4327424924275", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little more border
  s21_str_to_dec("4327424924274,50000000001", dec1);
  s21_str_to_dec("4327424924275", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little less border
  s21_str_to_dec("4327424924274,499999999", dec1);
  s21_str_to_dec("4327424924274", reference);

  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // check err incorrect scale
  s21_str_to_dec("4327424924274499999999", dec1);
  s21_set_scale(dec1, 29);
  returned_value = s21_round(*dec1, dec1);

  ck_assert_int_eq(returned_value, kErrCalc);

  s21_free_dec(&dec1);
  s21_free_dec(&reference);
}
END_TEST

START_TEST(test_s21_round_negative) {
  int returned_value = 0;
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(reference);

  // zero
  s21_str_to_dec("-0,009", dec1);
  s21_str_to_dec("0", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("-12345", dec1);
  s21_str_to_dec("-12345", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("-79228162514264337593543950335", dec1);
  s21_str_to_dec("-79228162514264337593543950335", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("-1,0", dec1);
  s21_str_to_dec("-1", reference);
  ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max down
  s21_str_to_dec("-7,9228162514264337593543950335", dec1);
  s21_str_to_dec("-8", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max up
  s21_str_to_dec("-7,2228162514264337593543950335", dec1);
  s21_str_to_dec("-7", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale random
  s21_str_to_dec("-4327424924274,247247", dec1);
  s21_str_to_dec("-4327424924274", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border1
  s21_str_to_dec("-99999999999999999999999,5", dec1);
  s21_str_to_dec("-100000000000000000000000", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border2
  s21_str_to_dec("-4327424924274,5", dec1);
  s21_str_to_dec("-4327424924275", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little more border
  s21_str_to_dec("-4327424924274,50000000001", dec1);
  s21_str_to_dec("-4327424924275", reference);
  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little less border
  s21_str_to_dec("-4327424924274,499999999", dec1);
  s21_str_to_dec("-4327424924274", reference);

  returned_value = s21_round(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&reference);
}
END_TEST

START_TEST(test_s21_negate) {
  int returned_value = 0;
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(reference);

  // with scale  < 0
  s21_str_to_dec("-0,009", dec1);
  s21_str_to_dec("0,009", reference);
  returned_value = s21_negate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // max  > 0
  s21_str_to_dec("72228162514264337593543950335", dec1);
  s21_str_to_dec("-72228162514264337593543950335", reference);
  returned_value = s21_negate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // max  < 0
  s21_str_to_dec("-72228162514264337593543950335", dec1);
  s21_str_to_dec("72228162514264337593543950335", reference);
  returned_value = s21_negate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // zero
  s21_str_to_dec("0", dec1);
  s21_str_to_dec("0", reference);
  returned_value = s21_negate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // random
  s21_str_to_dec("239398774000,000", dec1);
  s21_str_to_dec("-239398774000,000", reference);
  returned_value = s21_negate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // random
  s21_str_to_dec("-000003243244332", dec1);
  s21_str_to_dec("000003243244332", reference);
  returned_value = s21_negate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // check err from scale
  s21_set_scale(dec1, 29);

  returned_value = s21_negate(*dec1, dec1);

  ck_assert_int_eq(returned_value, kErrCalc);

  // check err from NULL
  s21_free_dec(&reference);

  returned_value = s21_negate(*dec1, reference);

  ck_assert_int_eq(returned_value, kErrCalc);

  s21_free_dec(&reference);
  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_truncate) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(reference);

  // without fractional part
  s21_str_to_dec("12345", dec1);
  s21_str_to_dec("12345", reference);
  int returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // with fraction part
  s21_str_to_dec("12,3456", dec1);
  s21_str_to_dec("12", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // with fraction part
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("7", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // with fraction part
  s21_str_to_dec("7922816251426433759354395033,5", dec1);
  s21_str_to_dec("7922816251426433759354395033", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // with fraction part
  s21_str_to_dec("39614081257132168,0000000", dec1);
  s21_str_to_dec("39614081257132168", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // negative fraction part
  s21_str_to_dec("-39614081257132168,0000000", dec1);
  s21_str_to_dec("-39614081257132168", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // negative fraction part
  s21_str_to_dec("-0,58473574", dec1);
  s21_str_to_dec("0", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // no changed
  s21_str_to_dec("-2000009", dec1);
  s21_str_to_dec("-2000009", reference);
  returned_value = s21_truncate(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // check err from scale
  s21_str_to_dec("-39614081257132168,0000000", dec1);
  s21_str_to_dec("-39614081257132168", reference);

  s21_set_scale(dec1, 29);

  returned_value = s21_truncate(*dec1, dec1);

  ck_assert_int_eq(returned_value, kErrCalc);

  // check err from NULL
  s21_free_dec(&reference);

  returned_value = s21_truncate(*dec1, reference);

  ck_assert_int_eq(returned_value, kErrCalc);

  s21_free_dec(&dec1);
  s21_free_dec(&reference);
}
END_TEST

START_TEST(test_s21_bank_round_bcd) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  bcd *reference = (bcd *)malloc(sizeof(bcd));

  s21_str_to_bcd("15845632502852867518708790067,5", bcd1);
  s21_str_to_bcd("15845632502852867518708790068", reference);

  int returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  s21_str_to_bcd("79228162514264337593543950335,3", bcd1);
  s21_str_to_bcd("79228162514264337593543950335", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  s21_str_to_bcd("7,9228162514264337593543950335", bcd1);
  s21_str_to_bcd("7,9228162514264337593543950335", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  s21_str_to_bcd("7,9228162514264337593543950336", bcd1);
  s21_str_to_bcd("7,922816251426433759354395034", reference);

  returned_value = s21_bank_round_bcd(bcd1, 28);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  // check all 9
  s21_str_to_bcd("9999999999999999999999999999,9", bcd1);
  s21_str_to_bcd("10000000000000000000000000000", reference);

  returned_value = s21_bank_round_bcd(bcd1, 28);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  // check all big with zero
  s21_str_to_bcd("1000000000000000000000000,000000000000000000000000000000000",
                 bcd1);
  s21_str_to_bcd("1000000000000000000000000,0000", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  // check odd

  s21_str_to_bcd("-32131232131244234432443244,1515", bcd1);
  s21_str_to_bcd("-32131232131244234432443244,152", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  // check even

  s21_str_to_bcd("-32131232131244234432443244,1525", bcd1);
  s21_str_to_bcd("-32131232131244234432443244,152", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  // check up

  s21_str_to_bcd("-32131232131244234432443244,152501", bcd1);
  s21_str_to_bcd("-32131232131244234432443244,153", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  // check down

  s21_str_to_bcd("-32131232131244234432443244,1524999", bcd1);
  s21_str_to_bcd("-32131232131244234432443244,152", reference);

  returned_value = s21_bank_round_bcd(bcd1, 29);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_bcd_compare(*bcd1, *reference), 0);
  } else {
    ck_assert_int_eq(returned_value, kErrMemory);
  }

  s21_free_bcd(&bcd1);
  s21_free_bcd(&reference);
}
END_TEST

START_TEST(test_s21_floor_positive) {
  int returned_value = 0;
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(reference);

  // zero
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // zero
  s21_str_to_dec("0,009", dec1);
  s21_str_to_dec("0", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("12345", dec1);
  s21_str_to_dec("12345", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("79228162514264337593543950335", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("4327424924274247247,", dec1);
  s21_str_to_dec("4327424924274247247,0", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("7", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max
  s21_str_to_dec("7,2228162514264337593543950335", dec1);
  s21_str_to_dec("7", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale random
  s21_str_to_dec("4327424924274,247247", dec1);
  s21_str_to_dec("4327424924274", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border1
  s21_str_to_dec("99999999999999999999999,5", dec1);
  s21_str_to_dec("99999999999999999999999", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border2
  s21_str_to_dec("4327424924274,5", dec1);
  s21_str_to_dec("4327424924274", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little more border
  s21_str_to_dec("4327424924274,50000000001", dec1);
  s21_str_to_dec("4327424924274", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little less border
  s21_str_to_dec("4327424924274,499999999", dec1);
  s21_str_to_dec("4327424924274", reference);

  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // check err incorrect scale
  s21_str_to_dec("4327424924274499999999", dec1);
  s21_set_scale(dec1, 29);
  returned_value = s21_floor(*dec1, dec1);

  ck_assert_int_eq(returned_value, kErrCalc);

  s21_free_dec(&dec1);
  s21_free_dec(&reference);
}
END_TEST

START_TEST(test_s21_floor_negative) {
  int returned_value = 0;
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(reference);

  // zero
  s21_str_to_dec("-0,009", dec1);
  s21_str_to_dec("-1", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("-12345", dec1);
  s21_str_to_dec("-12345", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("-79228162514264337593543950335", dec1);
  s21_str_to_dec("-79228162514264337593543950335", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale 0
  s21_str_to_dec("-1,0", dec1);
  s21_str_to_dec("-1", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max down
  s21_str_to_dec("-7,9228162514264337593543950335", dec1);
  s21_str_to_dec("-8", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale max up
  s21_str_to_dec("-7,2228162514264337593543950335", dec1);
  s21_str_to_dec("-8", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // scale random
  s21_str_to_dec("-4327424924274,247247", dec1);
  s21_str_to_dec("-4327424924275", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border1
  s21_str_to_dec("-99999999999999999999999,5", dec1);
  s21_str_to_dec("-100000000000000000000000", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // border2
  s21_str_to_dec("-4327424924274,5", dec1);
  s21_str_to_dec("-4327424924275", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little more border
  s21_str_to_dec("-4327424924274,50000000001", dec1);
  s21_str_to_dec("-4327424924275", reference);
  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  // a little less border
  s21_str_to_dec("-4327424924274,499999999", dec1);
  s21_str_to_dec("-4327424924275", reference);

  returned_value = s21_floor(*dec1, dec1);

  if (returned_value == kOk) {
    ck_assert_int_eq(s21_is_equal(*dec1, *reference), TRUE);
  } else {
    ck_assert_int_eq(returned_value, kErrCalc);
  }

  s21_free_dec(&dec1);
  s21_free_dec(&reference);
}
END_TEST

Suite *suite_rounds(void) {
  Suite *s = suite_create("rounds");
  TCase *tcase_core = tcase_create("rounds");

  tcase_add_test(tcase_core, test_s21_truncate);
  tcase_add_test(tcase_core, test_s21_negate);
  tcase_add_test(tcase_core, test_s21_round_positive);
  tcase_add_test(tcase_core, test_s21_round_negative);
  tcase_add_test(tcase_core, test_s21_floor_positive);
  tcase_add_test(tcase_core, test_s21_floor_negative);
  tcase_add_test(tcase_core, test_s21_bank_round_bcd);

  suite_add_tcase(s, tcase_core);

  return s;
}