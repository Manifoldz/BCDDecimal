#include "s21_decimal.h"

void s21_bcd_normalize(bcd *bcd1, bcd *bcd2, int scale_diff) {
  int first_digit = s21_find_first_digit_bcd(bcd1);
  int max_num_multiply = (BCD_NIBBLES - 1) - first_digit;
  int num_divides = 0;
  int num_multiply = scale_diff;

  if (scale_diff > max_num_multiply) {
    num_multiply = max_num_multiply;
    num_divides = scale_diff - num_multiply;
  }

  if (bcd1) {
    for (int i = 0; i < num_multiply; i++) {
      s21_bcd_multiply10(bcd1);
    }
    bcd1->scale += scale_diff;
    if (num_divides) {
      int first_digit2 = s21_find_first_digit_bcd(bcd2);
      s21_bank_round_bcd(bcd2, first_digit2 + 1 - num_divides);
    }
  }
}

int s21_bcd_compare(bcd value_1, bcd value_2) {
  int scale_diff = value_1.scale - value_2.scale;
  if (scale_diff < 0) {
    s21_bcd_normalize(&value_1, &value_2, -1 * scale_diff);
  } else if (scale_diff > 0) {
    s21_bcd_normalize(&value_2, &value_1, scale_diff);
  }

  return s21_bcd_mantissa_compare(&value_1, &value_2, 1);
}

int s21_dec_compare(s21_decimal *value_1, s21_decimal *value_2) {
  int result = 0;
  bcd *bcd_value_1 = s21_init_bcd(&result);
  bcd *bcd_value_2 = s21_init_bcd(&result);
  if (result != kErrMemory) {
    s21_dec_to_bcd(*value_1, bcd_value_1);
    s21_dec_to_bcd(*value_2, bcd_value_2);
    result = s21_bcd_compare(*bcd_value_1, *bcd_value_2);
  }
  s21_free_bcd(&bcd_value_1);
  s21_free_bcd(&bcd_value_2);
  return result;
}

int s21_bcd_mantissa_compare(bcd *value_1, bcd *value_2, int is_check_sign) {
  int result = 0;
  for (int i = BCD_INTS - 1; i >= 0 && !result; i--) {
    if (value_1->number[i] > value_2->number[i]) {
      result = 1;
      if (is_check_sign && value_1->sign) {
        result = -1;
      }
    } else if (value_1->number[i] < value_2->number[i]) {
      result = -1;
      if (is_check_sign && value_2->sign) {
        result = 1;
      }
    } else if (value_1->number[i] == value_2->number[i] &&
               value_1->number[i] != 0) {
      if (is_check_sign && value_1->sign > value_2->sign) {
        result = -1;
      } else if (is_check_sign && value_1->sign < value_2->sign) {
        result = 1;
      }
    }
  }

  return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int is_less = 0;
  int res_compare = s21_dec_compare(&value_1, &value_2);
  if (res_compare == -1)
    is_less = 1;
  else if (res_compare == kErrMemory)
    is_less = kErrMemory;
  return is_less;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int is_less_or_equal = 0;
  int res_compare = s21_dec_compare(&value_1, &value_2);
  if (res_compare == -1 || res_compare == 0)
    is_less_or_equal = 1;
  else if (res_compare == kErrMemory)
    is_less_or_equal = kErrMemory;
  return is_less_or_equal;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int temp = s21_is_less_or_equal(value_1, value_2);
  if (temp != kErrMemory) {
    temp = !temp;
  }
  return temp;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int temp = s21_is_less(value_1, value_2);
  if (temp != kErrMemory) {
    temp = !temp;
  }
  return temp;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int is_equal = 0;
  int res_compare = s21_dec_compare(&value_1, &value_2);
  if (res_compare == 0)
    is_equal = 1;
  else if (res_compare == kErrMemory)
    is_equal = kErrMemory;
  return is_equal;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int temp = s21_is_equal(value_1, value_2);
  if (temp != kErrMemory) {
    temp = !temp;
  }
  return temp;
}

int s21_bcd_more_than_max_dec(bcd *bcd_in, int is_need_to_full_cmp) {
  int res = 0;
  int err = 0;
  bcd *max = s21_init_bcd(&err);
  int sign_in = bcd_in->sign;
  if (err != kErrMemory) {
    max->number[0] = MAX_DEC_IN_BCD_UINT0;
    max->number[1] = MAX_DEC_IN_BCD_UINT1;
    max->sign = sign_in;

    if (!is_need_to_full_cmp && s21_bcd_mantissa_compare(bcd_in, max, 0) == 1) {
      res = 1;
    } else if ((!sign_in && s21_bcd_compare(*bcd_in, *max) == 1) ||
               (sign_in && s21_bcd_compare(*bcd_in, *max) == -1)) {
      res = 1;
    }
  }
  s21_free_bcd(&max);

  return (err == kOk) ? res : err;
}
