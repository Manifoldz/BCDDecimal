#include "s21_decimal.h"
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value_1) || !s21_is_valid_dec(&value_2))
    return kErrIncorrect;
  if (s21_is_dec_zero(value_1) && s21_is_dec_zero(value_2)) {
    s21_clean_dec(result);
    return kOk;
  }

  int error = 0;
  bcd *bcd_value_1 = s21_init_bcd(&error);
  bcd *bcd_value_2 = s21_init_bcd(&error);
  bcd *bcd_result = s21_init_bcd(&error);

  if (!error) {
    s21_dec_to_bcd(value_1, bcd_value_1);
    s21_dec_to_bcd(value_2, bcd_value_2);
    int sign_1 = s21_get_sign(&value_1);
    int sign_2 = s21_get_sign(&value_2);
    if (sign_1 != sign_2) {
      bcd_value_1->sign = 0;
      bcd_value_2->sign = 0;
      int who_is_more = s21_bcd_compare(*bcd_value_1, *bcd_value_2);

      if (who_is_more == 1) {
        s21_bcd_sub(*bcd_value_1, *bcd_value_2, bcd_result);
        bcd_result->sign = sign_1;
      } else if (who_is_more == -1) {
        s21_bcd_sub(*bcd_value_2, *bcd_value_1, bcd_result);
        bcd_result->sign = sign_2;
      }
    } else {
      s21_bcd_add(*bcd_value_1, *bcd_value_2, bcd_result);
      if (bcd_value_1->sign) {
        bcd_result->sign = 1;
      }
    }
    error = s21_prepare_for_dec(bcd_result);

    if (error == kOk) {
      s21_bcd_to_dec(*bcd_result, result);
    }
  }

  s21_free_bcd(&bcd_value_1);
  s21_free_bcd(&bcd_value_2);
  s21_free_bcd(&bcd_result);

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value_1) || !s21_is_valid_dec(&value_2))
    return kErrIncorrect;
  if (s21_is_dec_zero(value_1) && s21_is_dec_zero(value_2)) {
    s21_clean_dec(result);
    return kOk;
  }

  int error = 0;
  bcd *bcd_value_1 = s21_init_bcd(&error);
  bcd *bcd_value_2 = s21_init_bcd(&error);
  bcd *bcd_result = s21_init_bcd(&error);

  if (!error) {
    s21_dec_to_bcd(value_1, bcd_value_1);
    s21_dec_to_bcd(value_2, bcd_value_2);

    if (!bcd_value_1->sign && bcd_value_2->sign) {
      bcd_value_2->sign = 0;
      s21_bcd_add(*bcd_value_1, *bcd_value_2, bcd_result);
    } else if (bcd_value_1->sign && !bcd_value_2->sign) {
      bcd_value_1->sign = 0;
      s21_bcd_add(*bcd_value_1, *bcd_value_2, bcd_result);
      bcd_result->sign = 1;
    } else {
      int flag = (bcd_value_1->sign) ? -1 : 1;
      int compare_res = s21_bcd_compare(*bcd_value_1, *bcd_value_2);
      if (compare_res * flag == 1) {
        s21_bcd_sub(*bcd_value_1, *bcd_value_2, bcd_result);
      } else {
        s21_bcd_sub(*bcd_value_2, *bcd_value_1, bcd_result);
      }
      if (compare_res == -1) {
        bcd_result->sign = 1;
      }
    }

    error = s21_prepare_for_dec(bcd_result);
    if (error == kOk) {
      s21_bcd_to_dec(*bcd_result, result);
    }
  }

  s21_free_bcd(&bcd_value_1);
  s21_free_bcd(&bcd_value_2);
  s21_free_bcd(&bcd_result);

  return error;
}

void s21_bcd_add(bcd bcd_value_1, bcd bcd_value_2, bcd *bcd_result) {
  int tmp_in_memory = 0;

  int scale_diff = bcd_value_1.scale - bcd_value_2.scale;

  if (scale_diff < 0) {
    s21_bcd_normalize(&bcd_value_1, &bcd_value_2, -1 * scale_diff);
  } else if (scale_diff > 0) {
    s21_bcd_normalize(&bcd_value_2, &bcd_value_1, scale_diff);
  }

  bcd_result->scale = bcd_value_1.scale;

  for (int i = 0; i < BITS_IN_ULLINT; i++) {
    int digit_1 = s21_get_digit_from_bcd(bcd_value_1, i);
    int digit_2 = s21_get_digit_from_bcd(bcd_value_2, i);
    int digits_sum = digit_1 + digit_2 + tmp_in_memory;

    tmp_in_memory = digits_sum / 10;
    s21_set_digit_to_bcd(bcd_result, i, digits_sum % 10);
  }
}

void s21_bcd_sub(bcd bcd_value_1, bcd bcd_value_2, bcd *bcd_result) {
  int tmp_in_memory = 0;
  int first_digit_of_bcd_1 = 0;
  int scale_diff = bcd_value_1.scale - bcd_value_2.scale;

  if (scale_diff < 0) {
    s21_bcd_normalize(&bcd_value_1, &bcd_value_2, -1 * scale_diff);
  } else if (scale_diff > 0) {
    s21_bcd_normalize(&bcd_value_2, &bcd_value_1, scale_diff);
  }

  bcd_result->scale = bcd_value_1.scale;
  first_digit_of_bcd_1 = s21_find_first_digit_bcd(&bcd_value_1);
  if (first_digit_of_bcd_1 != -1) {
    for (int i = 0; i <= first_digit_of_bcd_1; i++) {
      int digit_1 = s21_get_digit_from_bcd(bcd_value_1, i);
      int digit_2 = s21_get_digit_from_bcd(bcd_value_2, i);
      int digits_sub = digit_1 - digit_2 - tmp_in_memory;

      if (digits_sub < 0) {
        s21_set_digit_to_bcd(bcd_result, i, digits_sub + 10);
        tmp_in_memory = 1;
      } else {
        s21_set_digit_to_bcd(bcd_result, i, digits_sub);
        tmp_in_memory = 0;
      }
    }
  } else {
    s21_copy_bcd(&bcd_value_2, bcd_result);
  }
}

int s21_bcd_add_one(bcd *bcd_in, int pos) {
  int err = kOk;
  if (pos >= 0 && pos <= 63) {
    bcd *temp = s21_init_bcd(&err);

    if (temp) {
      temp->scale = bcd_in->scale;
      s21_set_digit_to_bcd(temp, pos, 1);
      s21_bcd_add(*bcd_in, *temp, bcd_in);
    }

    s21_free_bcd(&temp);
  } else {
    err = kErrInternal;
  }

  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value_1) || !s21_is_valid_dec(&value_2))
    return kErrIncorrect;
  if (s21_is_dec_zero(value_1) || s21_is_dec_zero(value_2)) {
    s21_clean_dec(result);
    return kOk;
  }

  int error = 0;
  bcd *bcd_value_1 = s21_init_bcd(&error);
  bcd *bcd_value_2 = s21_init_bcd(&error);
  bcd *bcd_result = s21_init_bcd(&error);
  bcd *bcd_tmp_result = s21_init_bcd(&error);

  if (!error) {
    s21_dec_to_bcd(value_1, bcd_value_1);
    s21_dec_to_bcd(value_2, bcd_value_2);

    s21_bcd_mul(*bcd_value_1, *bcd_value_2, bcd_result, bcd_tmp_result);

    error = s21_prepare_for_dec(bcd_result);
    if (error == kOk && !s21_bcd_is_empty(*bcd_result)) {
      s21_bcd_to_dec(*bcd_result, result);
    }
  }

  s21_free_bcd(&bcd_value_1);
  s21_free_bcd(&bcd_value_2);
  s21_free_bcd(&bcd_result);
  s21_free_bcd(&bcd_tmp_result);

  return error;
}

void s21_bcd_mul(bcd bcd_value_1, bcd bcd_value_2, bcd *bcd_result,
                 bcd *bcd_tmp_result) {
  int tmp_in_memory = 0;
  if (bcd_value_1.sign != bcd_value_2.sign) {
    bcd_result->sign = 1;
  }
  int digits_counter = 0;
  int stop = 0;
  int first_bcd_value_1 = s21_find_first_digit_bcd(&bcd_value_1);
  int first_bcd_value_2 = s21_find_first_digit_bcd(&bcd_value_2);

  for (int i = 0; i < first_bcd_value_1 + 1 && !stop; i++) {
    int digit_1 = s21_get_digit_from_bcd(bcd_value_1, i);

    for (int j = 0; j <= first_bcd_value_2 || tmp_in_memory; j++) {
      int digit_2 = s21_get_digit_from_bcd(bcd_value_2, j);
      int digits_mul = digit_1 * digit_2 + tmp_in_memory;

      if (digits_mul > 9) {
        s21_set_digit_to_bcd(bcd_tmp_result, j, digits_mul % 10);
      } else {
        s21_set_digit_to_bcd(bcd_tmp_result, j, digits_mul);
      }
      tmp_in_memory = digits_mul / 10;
    }

    for (int k = 0; k < digits_counter; k++) {
      s21_bcd_multiply10(bcd_tmp_result);
    }
    s21_bcd_add(*bcd_tmp_result, *bcd_result, bcd_result);
    s21_clean_bcd(bcd_tmp_result);
    digits_counter++;
    if (s21_find_first_digit_bcd(bcd_result) == BCD_NIBBLES - 1) {
      stop = 1;
    }
  }
  bcd_result->scale = bcd_value_1.scale + bcd_value_2.scale;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // validate
  if (!result || !s21_is_valid_dec(&value_1) || !s21_is_valid_dec(&value_2))
    return kErrIncorrect;

  if (s21_is_dec_zero(value_2)) {
    return kErrDivByZero;
  }

  int error = 0;
  bcd *bcd_value_1 = s21_init_bcd(&error);
  bcd *bcd_value_2 = s21_init_bcd(&error);
  bcd *bcd_reminder = s21_init_bcd(&error);
  bcd *bcd_result = s21_init_bcd(&error);

  if (!error) {
    s21_dec_to_bcd(value_1, bcd_value_1);
    s21_dec_to_bcd(value_2, bcd_value_2);
    if (s21_get_sign(&value_1) && s21_get_sign(&value_2)) {
      bcd_result->sign = 0;
    } else if (s21_get_sign(&value_1) || s21_get_sign(&value_2)) {
      bcd_result->sign = 1;
    }
    bcd_value_1->sign = 0;
    bcd_value_2->sign = 0;
    s21_bcd_div(bcd_value_1, bcd_value_2, bcd_result, bcd_reminder);

    error = s21_prepare_for_dec(bcd_result);

    if (error == kOk) {
      s21_bcd_to_dec(*bcd_result, result);
    }
  }

  s21_free_bcd(&bcd_value_1);
  s21_free_bcd(&bcd_value_2);
  s21_free_bcd(&bcd_reminder);
  s21_free_bcd(&bcd_result);

  return error;
}

void s21_bcd_div(bcd *dividend, bcd *divisor, bcd *result, bcd *bcd_reminder) {
  int success_subtraction = 0;
  int scale_shift = 0;

  while (s21_bcd_mantissa_compare(dividend, divisor, 0) < 0) {
    s21_bcd_multiply10(dividend);
    scale_shift++;
  }

  result->scale = dividend->scale - divisor->scale + scale_shift;
  dividend->scale = 0;
  divisor->scale = 0;

  int idx = s21_find_first_digit_bcd(dividend);
  for (; idx >= 0; idx--) {
    int val = s21_get_digit_from_bcd(*dividend, idx);

    //  сдвигаем регистр остатка для нового разряда
    s21_bcd_multiply10(bcd_reminder);
    // переносим первую цифру с делимого в регистр остатка
    s21_set_digit_to_bcd(bcd_reminder, 0, val);
    // пока число из регистра остатка неотрицательное
    success_subtraction = 0;
    while (s21_bcd_compare(*bcd_reminder, *divisor) >= 0) {
      s21_bcd_sub(*bcd_reminder, *divisor, bcd_reminder);
      success_subtraction++;
    }
    // кол-во положительных вычитаний помещаем в результат
    s21_set_digit_to_bcd(result, idx, success_subtraction);
  }

  reminder_handler(bcd_reminder, divisor, result);
}

void reminder_handler(bcd *bcd_reminder, bcd *divisor, bcd *result) {
  int success_subtraction = 0;
  int current_first_digit_idx = s21_find_first_digit_bcd(result);
  while (!s21_bcd_is_empty(*bcd_reminder) && result->scale < BCD_NIBBLES - 1 &&
         current_first_digit_idx < BCD_NIBBLES - 1) {
    // сдвигаем регистр остатка для нового разряда
    s21_bcd_multiply10(bcd_reminder);
    success_subtraction = 0;
    while (s21_bcd_compare(*bcd_reminder, *divisor) >= 0) {
      // вычитаем из остатка делитель и подсчитываем кол-во вычитаний
      s21_bcd_sub(*bcd_reminder, *divisor, bcd_reminder);
      success_subtraction++;
    }
    if (success_subtraction >= 0) {
      s21_bcd_multiply10(result);
      s21_set_digit_to_bcd(result, 0, success_subtraction);
      result->scale++;
    }
    current_first_digit_idx = s21_find_first_digit_bcd(result);
  }
}

int s21_overflow_handler(bcd *bcd_result, int error) {
  if (!error) {
    error = s21_bcd_more_than_max_dec(bcd_result, 1);

    if (error == 1 && bcd_result->sign) {
      error = kErrTooSmall;
    } else if (error == 1 && bcd_result->sign) {
      error = kErrTooMuch;
    }
  }

  return error;
}
