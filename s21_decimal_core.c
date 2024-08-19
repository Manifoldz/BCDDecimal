#include "s21_decimal.h"

void *s21_safe_malloc(size_t size, int *error) {
  if (error == NULL) {
    return NULL;
  }
  void *ptr = malloc(size);
  // void *ptr = s21_random_malloc(size); // ATTENTION! USE ONLY FOR LEAK TEST!
  if (ptr == NULL) {
    *error = kErrMemory;
  }
  return ptr;
}

// void *s21_random_malloc(size_t size) {
//   int fail_chance = 30;
//   int random_number = rand() % 100;
//   if (random_number < fail_chance) {
//     return NULL;
//   }
//   return malloc(size);
// }

void s21_free_bcd(bcd **bcd_in) {
  if (bcd_in) {
    free(*bcd_in);
    *bcd_in = NULL;
  }
}

void s21_free_dec(s21_decimal **dec_in) {
  if (dec_in) {
    free(*dec_in);
    *dec_in = NULL;
  }
}

bcd *s21_init_bcd(int *err) {
  bcd *new_bcd = (bcd *)s21_safe_malloc(sizeof(bcd), err);
  if (*err != kErrMemory) {
    s21_clean_bcd(new_bcd);
  }
  return new_bcd;
}

void s21_clean_bcd(bcd *num) {
  num->sign = 0;
  num->scale = 0;
  for (int i = 0; i < BCD_INTS; i++) {
    num->number[i] = 0ULL;
  }
}

s21_decimal *s21_init_dec(int *err) {
  s21_decimal *new = (s21_decimal *)s21_safe_malloc(sizeof(s21_decimal), err);
  if (*err != kErrMemory) {
    s21_clean_dec(new);
  }
  return new;
}

void s21_clean_dec(s21_decimal *num) {
  for (int i = 0; i < DEC_INTS; i++) {
    num->bits[i] = 0;
  }
}

int s21_is_valid_dec(s21_decimal *value) {
  if (!value) {
    return 0;
  }
  int res = 1;
  // check scale
  int scale = s21_get_scale(value);
  if (scale < 0 || scale > 28) {
    res = 0;
  }
  // check empty bits
  if (res) {
    // mask for 0-15 bits
    int mask1 = (1 << 16) - 1;
    // mask for 24-30 bits
    int mask2 = ((1 << 7) - 1) << 24;
    if ((value->bits[3] & mask1) || (value->bits[3] & mask2)) {
      res = 0;
    }
  }
  return res;
}

void s21_copy_dec(s21_decimal *source, s21_decimal *dest) {
  for (int i = 0; i < DEC_INTS; i++) {
    dest->bits[i] = source->bits[i];
  }
}

void s21_copy_bcd(bcd *source, bcd *dest) {
  for (int i = 0; i < BCD_INTS; i++) {
    dest->number[i] = source->number[i];
  }
  dest->sign = source->sign;
  dest->scale = source->scale;
}

int s21_find_first_digit_bcd(bcd *num) {
  int res = BCD_NIBBLES - 1;
  for (; res >= 0; res--) {
    if (s21_get_digit_from_bcd(*num, res) > 0) {
      break;
    }
  }
  return res;
}

int s21_find_last_digit_bcd(bcd *num) {
  int res = 0;
  for (; res < BCD_NIBBLES; res++) {
    if (s21_get_digit_from_bcd(*num, res) > 0) {
      break;
    }
  }
  return res;
}

void s21_skip_last_digit_bcd(bcd *num) {
  for (int i = 0; i < 4; i++) {
    s21_right_shift_bcd(num);
  }
}

// void s21_print_bin_dec(s21_decimal num) {
//   printf("DECIMAL:\n");
//   for (int i = BITS_IN_DEC - 1; i >= 0; i--) {
//     printf("|%2d", i);
//   }
//   printf("|\n");
//   for (int i = BITS_IN_DEC - 1; i >= 0; i--) {
//     int is_bit_set = s21_is_bit_set(&num, i);
//     printf("|%2d", is_bit_set);
//   }
//   printf("|\n");
// }

// void s21_print_bcd(bcd *num) {
//   int pos = 0;
//   if (num->sign == 1) {
//     printf("%c", '-');
//   }

//   for (int i = BCD_INTS - 1; i >= 0; i--) {
//     for (int j = BITS_IN_ULLINT - 4; j >= 0; j -= 4) {
//       // Let's move it to the righ every time check 4 bits
//       int digit = ((num->number[i] >> j) & 15ULL);
//       if ((j + i * BITS_IN_ULLINT) / 4 == num->scale - 1) {
//         if (!pos) {
//           printf("%c", '0');
//           pos++;
//         }
//         printf("%c", ',');
//         pos++;
//       }
//       if (digit || pos) {
//         printf("%c", digit + '0');
//         pos++;
//       }
//     }
//   }

//   if (pos == 0) {
//     printf("%c", '0');
//   }
// }

// void s21_print_scale(s21_decimal num) {
//   printf("DECIMAL:\n");
//   for (int i = BITS_IN_INT - 1; i >= 0; i--) {
//     printf("|%2d", i);
//   }
//   printf("|\n");

//   for (int i = BITS_IN_INT - 1; i >= 0; i--) {
//     int is_bit_set = s21_is_bit_set(&num, BITS_IN_DEC + i);
//     printf("|%2d", is_bit_set);
//   }
//   printf("|\n");
// }

// void s21_print_dec_fm(s21_decimal num) {
//   // printf("DECIMAL:\n");

//   int is_bit_set = s21_is_bit_set(&num, 127);
//   printf("%d x ", is_bit_set);

//   for (int i = 120 - 1; i >= 112; i--) {
//     int is_bit_set = s21_is_bit_set(&num, i);
//     printf("%d", is_bit_set);
//   }
//   printf(" x ");

//   for (int i = 96 - 1; i >= 0; i--) {
//     int is_bit_set = s21_is_bit_set(&num, i);
//     if (i == 31 || i == 63) {
//       printf(" ");
//     }
//     printf("%d", is_bit_set);
//   }
//   printf("|\n");
// }

int s21_str_to_dec(char *str, s21_decimal *dec_out) {
  // validate
  if (!dec_out || !s21_is_valid_str_for_convert(str, 1)) {
    return kErrConvert;
  }

  int err = kOk;
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  if (bcd1) {
    s21_clean_bcd(bcd1);
  } else {
    err = kErrMemory;
  }

  if (!err) {
    err = s21_str_to_bcd(str, bcd1);
  }

  if (!err) {
    s21_bcd_to_dec(*bcd1, dec_out);
  }

  s21_free_bcd(&bcd1);
  return err;
}

int s21_is_valid_str_for_convert(char *str, int is_for_dec) {
  // empty pointer
  if (str == NULL) {
    return 0;
  }

  int res = 1;

  char *slider = str;
  char *comma_pos = NULL;
  size_t num_digit = 0;

  // check sign
  if (*str == '-' || *str == '+') {
    slider++;
  }

  // main logic
  while (res && *slider != '\0') {
    if (*slider == ',') {
      if (comma_pos != NULL) {
        res = 0;
      } else {
        comma_pos = slider;
        slider++;
      }
    } else if (*slider < '0' || *slider > '9') {
      res = 0;
    } else {
      slider++;
      num_digit++;
    }
    // check num digits
    if (res && (num_digit > BITS_IN_ULLINT / 4 * BCD_INTS ||
                (is_for_dec && num_digit > 29))) {
      res = 0;
    }
  }
  // check scale
  if (res && comma_pos) {
    unsigned long long scale = slider - comma_pos;
    if (scale > 64ULL || (is_for_dec && scale > 29ULL)) {
      res = 0;
    }
  }

  return (res && num_digit != 0);
}

int s21_str_to_bcd(char *str, bcd *bcd_out) {
  // validate
  if (!bcd_out || !s21_is_valid_str_for_convert(str, 0)) {
    return kErrConvert;
  }

  s21_clean_bcd(bcd_out);

  char *slider = str;

  // get sign
  if (*slider == '-') {
    bcd_out->sign = 1;
    slider++;
  } else if (*slider == '+') {
    slider++;
  }

  int num_digit = 0;
  while (*slider != '\0') {
    if (*slider != ',') {
      num_digit++;
    }
    slider++;
  }
  slider--;

  int bcd_pos_to_put = 0;

  while (slider >= str) {
    if (*slider == ',') {
      bcd_out->scale = num_digit - (slider - str) + bcd_out->sign;
    } else if (*slider != '-' && *slider != '+') {
      s21_set_digit_to_bcd(bcd_out, bcd_pos_to_put, (*slider) - '0');
      bcd_pos_to_put++;
    }
    slider--;
  }

  return kOk;
}