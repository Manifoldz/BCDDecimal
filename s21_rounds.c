#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value)) {
    return kErrCalc;
  }

  int err = kOk;
  if (s21_get_scale(&value) != 0) {
    bcd *bcd_temp = s21_init_bcd(&err);
    if (err != kErrMemory) {
      s21_dec_to_bcd(value, bcd_temp);
      err = s21_round_bcd(bcd_temp);
      s21_bcd_to_dec(*bcd_temp, result);
    }
    s21_free_bcd(&bcd_temp);
  } else {
    s21_copy_dec(&value, result);
  }

  // by the Task - returns only 0 or 1
  return (err) ? kErrCalc : kOk;
}

int s21_round_bcd(bcd *bcd_in) {
  // validate and check do we need round at all???
  if (!bcd_in) {
    return kErrCalc;
  }
  if ((bcd_in->scale == 0)) {
    return kOk;
  }

  int err = 0;
  // check first digit after comma
  if (s21_get_digit_from_bcd(*bcd_in, bcd_in->scale - 1) >= 5) {
    err = s21_bcd_add_one(bcd_in, bcd_in->scale);
  }
  if (!err) {
    s21_truncate_bcd(bcd_in);
  }

  return err;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value)) {
    return kErrCalc;
  }

  int err = kOk;
  if (s21_get_scale(&value) != 0) {
    bcd *bcd_temp = s21_init_bcd(&err);
    if (bcd_temp) {
      s21_dec_to_bcd(value, bcd_temp);
      err = s21_truncate_bcd(bcd_temp);
      s21_bcd_to_dec(*bcd_temp, result);
    }
    s21_free_bcd(&bcd_temp);
  } else {
    s21_copy_dec(&value, result);
  }

  // by the Task - returns only 0 or 1
  return (err) ? kErrCalc : kOk;
}

int s21_truncate_bcd(bcd *bcd_in) {
  if (!bcd_in) {
    return kErrCalc;
  }
  // skip 1 digit by scales's times
  for (int i = 0; i < bcd_in->scale; i++) {
    s21_skip_last_digit_bcd(bcd_in);
  }
  // Now our scale is 0!
  bcd_in->scale = 0;
  return kOk;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value)) {
    return kErrCalc;
  }

  s21_copy_dec(&value, result);
  if (s21_get_sign(result)) {
    s21_unset_sign(result);
  } else {
    s21_set_sign(result);
  }

  return kOk;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value)) {
    return kErrCalc;
  }

  int err = kOk;
  if (s21_get_scale(&value) != 0) {
    bcd *bcd_temp = s21_init_bcd(&err);
    if (err != kErrMemory) {
      s21_dec_to_bcd(value, bcd_temp);
      err = s21_floor_bcd(bcd_temp);
      s21_bcd_to_dec(*bcd_temp, result);
    }
    s21_free_bcd(&bcd_temp);
  } else {
    s21_copy_dec(&value, result);
  }

  // by the Task - returns only 0 or 1
  return (err) ? kErrCalc : kOk;
}

int s21_floor_bcd(bcd *bcd_in) {
  // validate and check do we need round at all???
  if (!bcd_in) {
    return kErrCalc;
  }
  if ((bcd_in->scale == 0)) {
    return kOk;
  }
  int err = 0;

  // check sign and existing digit after comma
  if (bcd_in->sign && bcd_in->scale > s21_find_last_digit_bcd(bcd_in)) {
    err = s21_bcd_add_one(bcd_in, bcd_in->scale);
  }

  if (!err) {
    s21_truncate_bcd(bcd_in);
  }

  return err;
}

int s21_bank_round_bcd(bcd *num, int max_digits) {
  int err = 0;
  int left_digit = s21_find_first_digit_bcd(num);
  int pos_extra_digit = left_digit - max_digits;
  if (left_digit < num->scale) {
    pos_extra_digit = num->scale - max_digits;
  }

  if (pos_extra_digit >= 0) {
    int extra_digit = s21_get_digit_from_bcd(*num, pos_extra_digit);
    if (extra_digit > 5) {
      err = s21_bcd_add_one(num, pos_extra_digit + 1);
    } else if (extra_digit == 5) {
      // let's check the next digits!
      int pos_last_digit = s21_find_last_digit_bcd(num);
      // if we found something after 5, add one!
      if (pos_extra_digit > pos_last_digit) {
        err = s21_bcd_add_one(num, pos_extra_digit + 1);
      } else if (s21_get_digit_from_bcd(*num, pos_extra_digit + 1) % 2 != 0) {
        // if not found, but the previous digit is odd - add one!
        err = s21_bcd_add_one(num, pos_extra_digit + 1);
      }
    }

    // skip extra digits
    if (!err) {
      for (int i = 0; i < pos_extra_digit + 1; i++) {
        num->scale--;
        s21_skip_last_digit_bcd(num);
      }
    }
  }

  return err;
}
// 79228162514264337593543950385
int s21_prepare_for_dec(bcd *num) {
  int error = kOk;
  int cmp = 0;
  error = s21_overflow_handler(num, error);

  if (error == kOk) {
    cmp = s21_bcd_more_than_max_dec(num, 0);
    if (cmp == kErrMemory) {
      error = kErrMemory;
    } else if (cmp == 1 || num->scale > 28) {
      error = s21_bank_round_bcd(num, 29);
    }

    do {
      cmp = s21_bcd_more_than_max_dec(num, 0);
      if (cmp == kErrMemory) {
        error = kErrMemory;
      } else if (cmp == 1) {
        error = s21_bank_round_bcd(num, 28);
      }

    } while (!error && cmp);
  }

  error = s21_overflow_handler(num, error);

  return error;
}