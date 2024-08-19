#include "s21_decimal.h"

int s21_get_int_pos(int index, int is_in_ullint) {
  return (is_in_ullint) ? index / BITS_IN_ULLINT : index / BITS_IN_INT;
}

int s21_get_bit_pos(int index, int is_in_ullint) {
  return (is_in_ullint) ? index % BITS_IN_ULLINT : index % BITS_IN_INT;
}

int s21_is_bit_set_bcd(bcd *num, int index) {
  unsigned long long mask = 1ULL << s21_get_bit_pos(index, 1);
  return (num->number[s21_get_int_pos(index, 1)] & mask) ? 1 : 0;
}

int s21_is_bit_set(s21_decimal *number, int index) {
  int mask = 1 << s21_get_bit_pos(index, 0);
  return (number->bits[s21_get_int_pos(index, 0)] & mask) ? 1 : 0;
}

void s21_set_bit(s21_decimal *number, int index) {
  int mask = 1 << s21_get_bit_pos(index, 0);
  number->bits[s21_get_int_pos(index, 0)] |= mask;
}

void s21_unset_bit(s21_decimal *num, int index) {
  int mask = ~(1 << s21_get_bit_pos(index, 0));
  num->bits[s21_get_int_pos(index, 0)] &= mask;
}

void s21_unset_sign(s21_decimal *num) {
  if (s21_is_bit_set(num, SIGN_BIT_INDEX)) {
    s21_unset_bit(num, SIGN_BIT_INDEX);
  }
}

void s21_set_sign(s21_decimal *num) {
  if (!s21_is_bit_set(num, SIGN_BIT_INDEX)) {
    s21_set_bit(num, SIGN_BIT_INDEX);
  }
}

int s21_get_sign(s21_decimal *num) {
  return s21_is_bit_set(num, SIGN_BIT_INDEX);
}

int s21_is_dec_zero(s21_decimal num) {
  int is_zero = 1;

  for (int i = DEC_INTS - 2; i >= 0 && is_zero; i--) {
    if (num.bits[i] != 0) {
      is_zero = 0;
    }
  }
  return is_zero;
}

void s21_set_bit_bcd(bcd *num, int index) {
  unsigned long long mask = 1ULL << s21_get_bit_pos(index, 1);
  num->number[s21_get_int_pos(index, 1)] |= mask;
}

void s21_unset_bit_bcd(bcd *num, int index) {
  unsigned long long mask = 1ULL << s21_get_bit_pos(index, 1);
  num->number[s21_get_int_pos(index, 1)] &= ~mask;
}

void s21_left_shift_dec(s21_decimal *num) {
  // start from highest int bits[2]
  for (int i = DEC_INTS - 2; i >= 0; i--) {
    num->bits[i] <<= 1;
    if (i > 0) {
      int highest_bit_in_smaller_int_index = i * BITS_IN_INT - 1;
      if (s21_is_bit_set(num, highest_bit_in_smaller_int_index)) {
        s21_set_bit(num, highest_bit_in_smaller_int_index + 1);
      }
    }
  }
}

void s21_right_shift_dec(s21_decimal *num) {
  for (int i = 0; i < DEC_INTS - 1; i++) {
    num->bits[i] >>= 1;
    // unset sign bit
    num->bits[i] &= ~(1 << 31);
    if (i < DEC_INTS - 2) {
      int smallest_bit_in_higher_int_index = (i + 1) * BITS_IN_INT;
      if (s21_is_bit_set(num, smallest_bit_in_higher_int_index)) {
        s21_set_bit(num, smallest_bit_in_higher_int_index - 1);
      }
    }
  }
}

void s21_left_shift_bcd(bcd *num) {
  for (int i = BCD_INTS - 1; i >= 0; i--) {
    num->number[i] <<= 1;
    if (i > 0) {
      int highest_bit_in_smaller_int_index = i * BITS_IN_ULLINT - 1;
      if (s21_is_bit_set_bcd(num, highest_bit_in_smaller_int_index)) {
        s21_set_bit_bcd(num, highest_bit_in_smaller_int_index + 1);
      }
    }
  }
}

void s21_right_shift_bcd(bcd *num) {
  for (int i = 0; i < BCD_INTS; i++) {
    num->number[i] >>= 1;
    if (i < BCD_INTS - 1) {
      int smallest_bit_in_higher_uint_index = (i + 1) * BITS_IN_ULLINT;
      if (s21_is_bit_set_bcd(num, smallest_bit_in_higher_uint_index)) {
        s21_set_bit_bcd(num, smallest_bit_in_higher_uint_index - 1);
      }
    }
  }
}

int s21_get_scale(s21_decimal *num) {
  int result = 0;
  int mask = 0xFF0000;
  result = ((num->bits[DEC_INTS - 1] & mask) >> 16);
  return result;
}

void s21_set_scale(s21_decimal *num, int scale) {
  int result = 0;
  // 11111111000000001111111111111111
  int mask0 = 0xFF00FFFF;
  result = ((num->bits[DEC_INTS - 1] & mask0));
  int mask = scale << 16;
  result |= mask;
  num->bits[DEC_INTS - 1] = result;
}

int s21_get_digit_from_bcd(bcd bcd_in, int number_nibble) {
  for (int i = 0; i < number_nibble * 4; i++) {
    s21_right_shift_bcd(&bcd_in);
  }
  return bcd_in.number[0] & 15ULL;
}

void s21_set_digit_to_bcd(bcd *bcd_in, int number_nibble, int digit) {
  int num_uint = number_nibble / (BITS_IN_ULLINT / 4);
  int nibble_in_uint = number_nibble % (BITS_IN_ULLINT / 4);
  unsigned long long mask = (unsigned long long)digit;
  mask <<= nibble_in_uint * 4;

  // before to put digit we need to clear old bits
  bcd_in->number[num_uint] &= ~(15ULL << nibble_in_uint * 4);
  bcd_in->number[num_uint] |= mask;
}

// void s21_unset_digit_from_bcd(bcd *bcd_in, int number_nibble) {
//   int num_uint = number_nibble / (BITS_IN_ULLINT / 4);
//   int nibble_in_uint = number_nibble % (BITS_IN_ULLINT / 4);
//   unsigned long long mask = 15ULL << nibble_in_uint * 4;
//   bcd_in->number[num_uint] &= ~mask;
// }

int s21_bcd_is_empty(bcd bcd_value) {
  for (int i = 0; i < BCD_INTS; i++) {
    if (bcd_value.number[i] != 0) {
      return 0;
    }
  }
  return 1;
}
