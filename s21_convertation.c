#include "s21_decimal.h"

void s21_dec_to_bcd(s21_decimal dec, bcd *bcd_out) {
  int nibbles_in_uint = BCD_NIBBLES / 4;
  if (s21_get_sign(&dec)) {
    bcd_out->sign = 1;
  }
  bcd_out->scale = s21_get_scale(&dec);

  for (int i = 0; i < BITS_IN_DEC; i++) {
    // Correction +3 in all nibbles
    for (int nibble = 0; nibble < BCD_INTS * nibbles_in_uint; nibble++) {
      int num_int = nibble / nibbles_in_uint;
      int num_nibble = nibble % nibbles_in_uint;
      if ((bcd_out->number[num_int] >> (4 * num_nibble) & 15ULL) >= 5) {
        bcd_out->number[num_int] += (3ULL << (4 * num_nibble));
      }
    }

    s21_left_shift_bcd(bcd_out);
    if (s21_is_bit_set(&dec, BITS_IN_DEC - 1)) {
      s21_set_bit_bcd(bcd_out, 0);
    }
    s21_left_shift_dec(&dec);
  }
}

void s21_bcd_to_dec(bcd bcd_in, s21_decimal *dec) {
  int nibbles_in_uint = BCD_NIBBLES / 4;
  s21_clean_dec(dec);

  for (int i = 0; i < BITS_IN_DEC; i++) {
    s21_right_shift_dec(dec);
    if (s21_is_bit_set_bcd(&bcd_in, 0)) {
      s21_set_bit(dec, BITS_IN_DEC - 1);
    }
    s21_right_shift_bcd(&bcd_in);
    // Correction -3 in all nibbles
    for (int nibble = 0; nibble < BCD_INTS * nibbles_in_uint; nibble++) {
      int num_int = nibble / nibbles_in_uint;
      int num_nibble = nibble % nibbles_in_uint;
      if ((bcd_in.number[num_int] >> (4 * num_nibble) & 15ULL) >= 8) {
        bcd_in.number[num_int] -= (3ULL << (4 * num_nibble));
      }
    }
  }

  if (bcd_in.sign) {
    s21_set_sign(dec);
  }
  s21_set_scale(dec, bcd_in.scale);
}

int s21_bcd_to_str(bcd *num, char *str) {
  // max str must to include 64 digits, 1 comma, 1 sign and \0
  if (!str || !num) {
    return kErrConvert;
  }

  int str_pos = 0;
  int lead_zero = 0;
  if (num->sign == 1) {
    str[str_pos++] = '-';
  }

  for (int i = BCD_INTS - 1; i >= 0; i--) {
    for (int j = BITS_IN_ULLINT - 4; j >= 0; j -= 4) {
      // Let's move it to the righ every time check 4 bits
      int digit = ((num->number[i] >> j) & 15ULL);
      if ((j + i * BITS_IN_ULLINT) / 4 == num->scale - 1) {
        if (!lead_zero) {
          str[str_pos++] = '0';
          lead_zero = 1;
        }
        str[str_pos++] = ',';
      }
      if (digit || lead_zero) {
        str[str_pos++] = digit + '0';
        lead_zero = 1;
      }
    }
  }
  if (str_pos == 0) {
    str[str_pos++] = '0';
  }
  str[str_pos] = '\0';
  return kOk;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  double d = (double)src;
  if (!dst || isnan(src) || isinf(src) ||
      fabs(d) > 79228162514264337593543950335.0) {
    return kErrConvert;
  }
  s21_clean_dec(dst);
  if (fabs(d) > 0 && (fabs(d) < 0.0000000000000000000000000001)) {
    return kErrConvert;
  }
  if (src == 0.0) {
    return kOk;
  }
  int scale = 0;
  int sign = 0;
  if (d < 0) {
    sign = 1;
    d *= -1;
  }

  s21_norm_scale(&d, &scale);

  int exp = 0;
  if (scale > 0) {
    exp = scale;
    scale = 0;
  }
  int newf = (int)d;
  scale = scale * -1;
  if (sign == 1) {
    s21_set_bit(dst, 127);
  }
  s21_set_scale(dst, scale);
  dst->bits[0] = newf;
  int err = kOk;
  bcd *bcd_out = s21_init_bcd(&err);

  if (!err) {
    s21_dec_to_bcd(*dst, bcd_out);
    for (int i = 0; i < (exp); i++) {
      s21_bcd_multiply10(bcd_out);
    }
    s21_bcd_to_dec(*bcd_out, dst);
  }

  s21_free_bcd(&bcd_out);
  return (err) ? kErrConvert : kOk;
}

void s21_norm_scale(double *d, int *scale) {
  while (*d >= 10000000) {
    *d = *d / 10;
    (*scale)++;
  }
  while (*d < 1000000) {
    *d = *d * 10;
    (*scale)--;
  }
  if (*scale >= -28) {
    *d = lround(*d);
  }
  while (*scale < (-28)) {
    *d = *d / 10;
    if (*scale == -29) {
      *d = lround(*d);
    }
    (*scale)++;
  }
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) {
    return kErrConvert;
  }
  *dst = 0;
  double array = 0;
  for (int i = 0; i < 96; i++) {
    array += s21_is_bit_set(&src, i) * pow(2, i);
  }

  array *= pow(10, -s21_get_scale(&src));

  if (s21_is_bit_set(&src, 127) == 1) {
    array *= -1;
  }
  *dst = (float)array;
  return kOk;
}

void s21_bcd_multiply10(bcd *num) {
  for (int i = 0; i < 4; i++) {
    s21_left_shift_bcd(num);
  }
}

//------------------------------------------------------------------------------------------------------------

// COVERT DEC INT / INT DEC

//------------------------------------------------------------------------------------------------------------
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  code_of_error error = kOk;
  if (!dst) {
    error = kErrConvert;
  } else {
    s21_decimal truncated_decimal = {0};
    s21_decimal min_int_decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    s21_decimal max_int_decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

    error = s21_truncate(src, &truncated_decimal);
    if (!error) {
      error = s21_is_less(truncated_decimal, min_int_decimal);
    }

    if (!error) {
      error = s21_is_greater(truncated_decimal, max_int_decimal);
    }

    if (!error) {
      *dst = 0;
      for (int i = 0; i < BITS_IN_DEC; i++) {
        *dst += s21_is_bit_set(&truncated_decimal, i) * pow(2, i);
      }
      if (s21_get_sign(&src) == 1 && *dst != -2147483648) {
        *dst = -*dst;
      }
    }
  }
  return (error) ? kErrConvert : kOk;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  code_of_error result = kOk;

  if (!dst) {
    // Если указатель на dst нулевой, возвращаем ошибку
    result = kErrConvert;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      // Устанавливаем 31-й бит для отрицательного числа
      dst->bits[3] = 1 << 31;
      // Меняем знак на положительный для дальнейшей обработки
      src = -src;
    }

    // Проверка на переполнение
    if (src > INT_MAX || src < INT_MIN) {
      // Указываем на переполнение
      result = kErrConvert;
    } else {
      dst->bits[0] = src;
    }
  }

  return result;
}