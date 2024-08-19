#ifndef s21_DECIMAL_H
#define s21_DECIMAL_H

#include <limits.h>
#include <math.h>
//  #include <stdio.h>
#include <stdlib.h>

#define BCD_INTS 4
#define BCD_NIBBLES 64
#define DEC_INTS 4
#define BITS_IN_BYTE 8
#define BITS_IN_INT 32
#define BITS_IN_ULLINT 64
#define BITS_IN_DEC 96
#define SIGN_BIT_INDEX 127
#define BITS_IN_BCD 256
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_DEC_IN_BCD_UINT0 4843438009562235701ULL
#define MAX_DEC_IN_BCD_UINT1 2131025704850470ULL

typedef struct {
  int bits[4];
} s21_decimal;

typedef enum code_of_error {
  kOk = 0,
  kErrCalc = 1,
  kErrConvert = 1,
  kErrTooMuch = 1,
  kErrTooSmall = 2,
  kErrDivByZero = 3,
  kErrMemory = 4,
  kErrInternal = 5,
  kErrIncorrect = 6
} code_of_error;

typedef struct {
  char sign;
  int scale;
  unsigned long long number[BCD_INTS];
} bcd;

/*
below common functions
*/

// Returns void allocated memory, if malloc error - changed error to ERRMEM
void *s21_safe_malloc(size_t size, int *error);

// Random allocated memory ATTENTION! USE ONLY FOR LEAK TEST!
void *s21_random_malloc(size_t size);

// Free bcd-memory and makes NULL-ptr
void s21_free_bcd(bcd **bcd_in);
// Free dec-memory and makes NULL-ptr
void s21_free_dec(s21_decimal **dec_in);

// Inits bcd with cleaned all fields and bits, if malloc error *err= kErrMemory
bcd *s21_init_bcd(int *err);
// Cleans all fields and bits
void s21_clean_bcd(bcd *num);

// Inits decimal with cleaned bits, if malloc error *err= kErrMemory
s21_decimal *s21_init_dec(int *err);
// Cleans all bits
void s21_clean_dec(s21_decimal *num);

void s21_unset_sign(s21_decimal *num);
void s21_set_sign(s21_decimal *num);

// Returns 0 - sign is unset, 1 - sign is set
int s21_get_sign(s21_decimal *num);

int s21_prepare_for_dec(bcd *num);

// Returns 1 - decimal correct, 0 - incorrect value
// incorrect - NULL, scale < 0 || > 28, bits 0-15 || 24-30 are not empty
int s21_is_valid_dec(s21_decimal *value);

// Copies dec all fields of source into dest
void s21_copy_dec(s21_decimal *source, s21_decimal *dest);
// Copies bcd all fields of source into dest
void s21_copy_bcd(bcd *source, bcd *dest);

// Returns position of the first digit of bcd value, if no digits returns -1
int s21_find_first_digit_bcd(bcd *num);
// Returns position of the last digit of bcd value, if no digits returns 64!
int s21_find_last_digit_bcd(bcd *num);

/*
below rounds functions
*/

// Deletes fract. part of decimal, leaves only int, returns kErrCalc or kOk
int s21_truncate(s21_decimal value, s21_decimal *result);

// Deletes fractional part in bcd, leaves only int, returns kErrCalc or kOk
int s21_truncate_bcd(bcd *bcd_in);

// Arithmetic round dec to nearest int value
// returns kErrCalc if any error, 0 - no error
int s21_round(s21_decimal value, s21_decimal *result);

// Arithmetic round bcd to nearest int value, returns kErrCalcm, kErrMemory or 0
int s21_round_bcd(bcd *bcd_in);

// Round bcd value by rules of bank round (makes 29 digits and decrease scale)
// returns 0 - no error, kErrMemory malloc error, kErrInternal algo error
int s21_bank_round_bcd(bcd *num, int max_digits);

// Makes multiplication by -1, returns 1 if error
int s21_negate(s21_decimal value, s21_decimal *result);

// Round to the closest integer toward negative infinity
int s21_floor(s21_decimal value, s21_decimal *result);
// Round bcd to the closest integer toward negative infinity
int s21_floor_bcd(bcd *bcd_in);

/*
below convertations functions
*/

// Converts decimal-struct into the bcd-struct
void s21_dec_to_bcd(s21_decimal dec, bcd *bcd_out);
// Converts bcd-struct into the decimal-struct
void s21_bcd_to_dec(bcd bcd_in, s21_decimal *dec);

// Converts bcd-struct into the str
// Returns 0 - no error or kErrConvert error
int s21_bcd_to_str(bcd *num, char *str);

int s21_from_float_to_decimal(float src, s21_decimal *dst);
void s21_norm_scale(double *d, int *scale);
void s21_bcd_multiply10(bcd *num);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/*
below bit manipulations functions
*/

// Returns number of bit in dec if is_in_ullint==0, otherwise in bcd
int s21_get_bit_pos(int index, int is_in_ullint);

// Returns number of int in dec if is_in_ullint==0, otherwise num of uint in bcd
int s21_get_int_pos(int index, int is_in_ullint);

// Returns 1 if bit in index is set, otherwise 0 (for decimal)
int s21_is_bit_set(s21_decimal *num, int index);
// Returns 1 if bit in index is set, otherwise 0 (for bcd)
int s21_is_bit_set_bcd(bcd *num, int index);

// Sets bit in index (for decimal)
void s21_set_bit(s21_decimal *num, int index);
// Sets bit in index (for bcd)
void s21_set_bit_bcd(bcd *num, int index);

// Unsets bit in index (for decimal)
void s21_unset_bit(s21_decimal *num, int index);
// Unsets bit in index (for bcd)
void s21_unset_bit_bcd(bcd *num, int index);

// Makes 1 left shift (for decimal)
void s21_left_shift_dec(s21_decimal *num);
// Makes 1 right shift (for decimal)
void s21_right_shift_dec(s21_decimal *num);

// Makes 1 left shift (for bcd)
void s21_left_shift_bcd(bcd *num);
// Makes 1 right shift (for bcd)
void s21_right_shift_bcd(bcd *num);

// Returns digit at nibble with number (0-64)
// For example in 328315 8 have 3rd place - so call func with number 3
int s21_get_digit_from_bcd(bcd bcd_in, int number_nibble);

// Sets digit at nibble with number (0-64)
// For example in 328315, we set 9 at 4rd place - so we have 398315
void s21_set_digit_to_bcd(bcd *bcd_in, int number_nibble, int digit);

// Delete 1 last digit in bcd - makes 4 right shift
void s21_skip_last_digit_bcd(bcd *num);

void s21_unset_digit_from_bcd(bcd *bcd_in, int number_nibble);

int s21_bcd_is_empty(bcd bcd_value);

/*
  compare functions
*/

// return 1 - a > b, 0 - a == b, -1 - a < b
int s21_bcd_compare(bcd value_1, bcd value_2);
// 1 - a>b, 0 - a==b, -1 a<b or kErrMemory if malloc error
int s21_dec_compare(s21_decimal *value_1, s21_decimal *value_2);

// Returns 1 - a > b, 0 - a == b, -1 - a < b.
// To check with sign third arg must be 1, otherwise compares only
// mantisses!
int s21_bcd_mantissa_compare(bcd *value_1, bcd *value_2, int is_check_sign);

// Returns 1 - bcd > max_dec, otherwise 0, kErrMemory - if malloc error
// to compare number with scale, set the sec arg in 1, otherwhise 0
int s21_bcd_more_than_max_dec(bcd *bcd_in, int is_need_to_full_cmp);

/*
    normalizes bcd value
 */
void s21_bcd_normalize(bcd *bcd1, bcd *bcd2, int scale_diff);

// return 1 - dec is equal zero, 0 - isnt zero
// 0 and -0 is equals
int s21_is_dec_zero(s21_decimal num);

// return 1 - if true, 0 false, also kErrMemory  - if malloc error
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
// return 1 - if true, 0 false, also kErrMemory  - if malloc error
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
// return 1 - if true, 0 false, also kErrMemory  - if malloc error
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
// return 1 - if true, 0 false, also kErrMemory  - if malloc error
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
// return 1 - if true, 0 false, also kErrMemory  - if malloc error
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
// return 1 - if true, 0 false, also kErrMemory  - if malloc error
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_get_scale(s21_decimal *num);
void s21_set_scale(s21_decimal *num, int scale);

/*
  arithmetic funcs
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_bcd_add(bcd bcd_value_1, bcd bcd_value_2, bcd *bcd_result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_bcd_sub(bcd value_1, bcd value_2, bcd *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_bcd_mul(bcd bcd_value_1, bcd bcd_value_2, bcd *bcd_result,
                 bcd *bcd_tmp_result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_bcd_div(bcd *dividend, bcd *divisor, bcd *result, bcd *bcd_reminder);
void reminder_handler(bcd *bcd_reminder, bcd *divisor, bcd *result);

// Adds one to bcd into the showed position
// returns kErrMemory if malloc error, kErrInternal if incorrect response
int s21_bcd_add_one(bcd *bcd_in, int pos);

int s21_overflow_handler(bcd *bcd_result, int error);

/*
  Debug prints
*/

// Prints decimal in binary-format
void s21_print_bin_dec(s21_decimal num);

// Prints bcd in decimal-format
void s21_print_bcd(bcd *num);

// Prints scale (debug)
void s21_print_scale(s21_decimal num);

void s21_print_dec_fm(s21_decimal num);

int s21_str_to_dec(char *str, s21_decimal *dec_out);

int s21_is_valid_str_for_convert(char *str, int is_for_dec);

int s21_str_to_bcd(char *str, bcd *bcd_out);

#endif
