#include "test.h"

START_TEST(test_s21_add) {
  int returned_value = 0;

  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *result = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *reference = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_clean_dec(result);
  s21_clean_dec(reference);

  // s21_add

  // 0,123456 + (-0,00879) = 0,114666
  s21_str_to_dec("-0,00879", dec1);
  s21_str_to_dec("0,123456", dec2);
  s21_str_to_dec("0,114666", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 0,123456 + (-0,00879) = 0,114666
  s21_str_to_dec("0,123456", dec1);
  s21_str_to_dec("-0,00879", dec2);
  s21_str_to_dec("0,114666", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 8790 + (-123456) = -114666
  s21_str_to_dec("8790", dec1);
  s21_str_to_dec("-123456", dec2);
  s21_str_to_dec("-114666", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 0 + 0 = 0
  s21_str_to_dec("0", dec1);
  s21_str_to_dec("0", dec2);
  s21_str_to_dec("0", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -7,9228162514264337593543950335 + 0,00000000000004 =
  // -7,9228162514263937593543950335

  s21_str_to_dec("-7,9228162514264337593543950335", dec1);
  s21_str_to_dec("0,00000000000004", dec2);
  s21_str_to_dec("-7,9228162514263937593543950335", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 109 + 1 = 110
  s21_str_to_dec("109", dec1);
  s21_str_to_dec("1", dec2);
  s21_str_to_dec("110", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 101 + 199 = 300
  s21_str_to_dec("101", dec1);
  s21_str_to_dec("199", dec2);
  s21_str_to_dec("300", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79,228,162,514,264,337,593,543,950,332 + 3 = ...335
  s21_str_to_dec("79228162514264337593543950332", dec1);
  s21_str_to_dec("3", dec2);
  s21_str_to_dec("79228162514264337593543950335", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79,228,162,514,264,337,593,543,950,335 * 10^-1 + 5 = 0
  s21_str_to_dec("7922816251426433759354395033,5", dec1);
  s21_str_to_dec("5", dec2);
  s21_str_to_dec("7922816251426433759354395038", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // printf("\n");
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 + (-79228162514264337593543950335) = 0
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("-79228162514264337593543950335", dec2);
  s21_str_to_dec("0", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 + 0 = same
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0", dec2);
  s21_str_to_dec("79228162514264337593543950335", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 + 1 = overflow
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("1", dec2);

  returned_value = s21_add(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooMuch);
  }

  // 79,228,162,514,264,337,593,543,950,335 * 10^-28 + 2
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("2", dec2);
  s21_str_to_dec("9,922816251426433759354395034", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79,228,162,514,264,337,593,543,950,335 * 10^-10 + 5 125 * 10 ^ -4
  s21_str_to_dec("7922816251426433759,3543950335", dec1);
  s21_str_to_dec("5126,2334", dec2);
  s21_str_to_dec("7922816251426438885,587795034", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  s21_str_to_dec("-654,73637984823622889775429300", dec1);
  s21_str_to_dec("593180685639578633,56066404516", dec2);
  s21_str_to_dec("593180685639577978,82428419692", reference);

  returned_value = s21_add(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // s21_sub

  // 7,9228162514264337593543950335 - 3,7593543950335
  // = 4,1634618563929337593543950335
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("3,7593543950335", dec2);
  s21_str_to_dec("4,1634618563929337593543950335", reference);

  returned_value = s21_sub(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 - 0 = same
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0", dec2);
  s21_str_to_dec("79228162514264337593543950335", reference);

  returned_value = s21_sub(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 0 - 0 = 0
  s21_str_to_dec("0", dec1);
  s21_str_to_dec("0", dec2);
  s21_str_to_dec("0", reference);

  returned_value = s21_sub(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 - 1 = ...334
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("1", dec2);
  s21_str_to_dec("79228162514264337593543950334", reference);

  returned_value = s21_sub(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 - 79228162514264337593543950335 = 0
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("79228162514264337593543950335", dec2);
  s21_str_to_dec("0", reference);

  returned_value = s21_sub(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 - 335 = 79228162514264337593543950000
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("335", dec2);
  s21_str_to_dec("79228162514264337593543950000", reference);

  returned_value = s21_sub(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  //-79228162514264337593543950335 - 1 = overflow (error 2)
  s21_str_to_dec("-79228162514264337593543950335", dec1);
  s21_str_to_dec("1", dec2);

  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);

  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooSmall);
  }

  // 1 - 79228162514264337593543950335 = ...334
  s21_str_to_dec("1", dec1);
  s21_str_to_dec("79228162514264337593543950335", dec2);
  s21_str_to_dec("-79228162514264337593543950334", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  //  s21_print_bin_dec(*reference);
  //  printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 1 - 79228162514264337593543950335 = ...334
  s21_str_to_dec("1", dec1);
  s21_str_to_dec("79228162514264337593543950335", dec2);
  s21_str_to_dec("-79228162514264337593543950334", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 1 - 79228162514264337593543950335 = ...334
  s21_str_to_dec("1", dec1);
  s21_str_to_dec("79228162514264337593543950335", dec2);
  s21_str_to_dec("-79228162514264337593543950334", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -12 - -1234 = 1222
  s21_str_to_dec("-12", dec1);
  s21_str_to_dec("-1234", dec2);
  s21_str_to_dec("1222", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 12 - -1234 = 1246
  s21_str_to_dec("12", dec1);
  s21_str_to_dec("-1234", dec2);
  s21_str_to_dec("1246", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 12 - 1234 = -1222
  s21_str_to_dec("12", dec1);
  s21_str_to_dec("1234", dec2);
  s21_str_to_dec("-1222", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -12 - 1234 = -1246
  s21_str_to_dec("-12", dec1);
  s21_str_to_dec("1234", dec2);
  s21_str_to_dec("-1246", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 1234 - 12 = 1222
  s21_str_to_dec("1234", dec1);
  s21_str_to_dec("12", dec2);
  s21_str_to_dec("1222", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 1234 - -12 = 1246
  s21_str_to_dec("1234", dec1);
  s21_str_to_dec("-12", dec2);
  s21_str_to_dec("1246", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -1234 - 12 = 1222
  s21_str_to_dec("-1234", dec1);
  s21_str_to_dec("12", dec2);
  s21_str_to_dec("-1246", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -1234 - -12 = -1222
  s21_str_to_dec("-1234", dec1);
  s21_str_to_dec("-12", dec2);
  s21_str_to_dec("-1222", reference);
  returned_value = s21_sub(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  // s21_print_bin_dec(*reference);
  // printf("%d - %d\n", s21_get_sign(result), returned_value);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // s21_mul

  // 7,9228162514264337593543950335 * 7,9228162514264337593543950335
  // = 62,77101735386680763835789423049210091073826769276946612225
  // = 62,77101735386680763835789423
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("7,9228162514264337593543950335", dec2);
  s21_str_to_dec("62,77101735386680763835789423", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -0,00879 * 0,123456 = -0,00108517824
  s21_str_to_dec("-0,00879", dec1);
  s21_str_to_dec("0,123456", dec2);
  s21_str_to_dec("-0,00108517824", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 8790 * -123456 = -1085178240
  s21_str_to_dec("8790", dec1);
  s21_str_to_dec("-123456", dec2);
  s21_str_to_dec("-1085178240", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // -7,9228162514264337593543950335 * 0,00000000000004
  // = -0,00000000000031691265005705735037417580134
  // = -0,0000000000003169126500570574
  s21_str_to_dec("-7,9228162514264337593543950335", dec1);
  s21_str_to_dec("0,00000000000004", dec2);
  s21_str_to_dec("-0,0000000000003169126500570574", reference);
  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 * 0,0000000000000000000000000001
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0,0000000000000000000000000001", dec2);
  s21_str_to_dec("7,9228162514264337593543950335", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 * 1,0000000000000000000000000000 = same
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("1,0000000000000000000000000000", dec2);
  s21_str_to_dec("79228162514264337593543950335", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 * 1,0000000000000000000000000001 =
  // overflow
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("1,0000000000000000000000000001", dec2);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooMuch);
  }

  // 79228162514264337593543950335 * 2 = overflow
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("2", dec2);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooMuch);
  }

  // 79228162514264337593543950335 * 0,8
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0,8", dec2);
  s21_str_to_dec("63382530011411470074835160268", reference);
  // s21_print_bin_dec(*dec1); 12946617,6
  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79,228,162,514,264,337,593,543,950,335 * 0,1
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0,1", dec2);
  s21_str_to_dec("7922816251426433759354395033,5", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  // s21_print_bin_dec(*result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // s21_div
  // -7,9228162514264337593543950335 / 0,00000000000004
  // = -198070406285660,8439838598758375
  // = -198070406285660,84398385987584
  s21_str_to_dec("-7,9228162514264337593543950335", dec1);
  s21_str_to_dec("0,00000000000004", dec2);
  s21_str_to_dec("-198070406285660,84398385987584", reference);
  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }
  // -0,00879 / 0,123456
  // -0.071199455676516329704510108864696734059097978227060653188180404
  // -0.0711994556765163297045101089 0711994556765163297451188647!!
  // -0.071199455676516323898717075735
  // 07119945567651632970451010886469673405
  s21_str_to_dec("-0,00879", dec1);
  s21_str_to_dec("0,123456", dec2);
  s21_str_to_dec("-0,0711994556765163297045101089", reference);
  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 7,9228162514264337593543950335 / 10 = 0,7922816251426433759354395034
  s21_str_to_dec("7,9228162514264337593543950335", dec1);
  s21_str_to_dec("10", dec2);
  s21_str_to_dec("0,7922816251426433759354395034", reference);
  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 7,9228162514264337593543950325 / 10 = 0,7922816251426433759354395032
  s21_str_to_dec("7,9228162514264337593543950325", dec1);
  s21_str_to_dec("10", dec2);
  s21_str_to_dec("0,7922816251426433759354395032", reference);
  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 1 / 3 = 0,3333333333333333333333333333
  s21_str_to_dec("1", dec1);
  s21_str_to_dec("3", dec2);
  s21_str_to_dec("0,3333333333333333333333333333", reference);
  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 / 0.00000000000001 = overflow up
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0,00000000000001", dec2);

  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooMuch);
  }

  // 79228162514264337593543950,335 / 0.00000000000001 = overflow up
  s21_str_to_dec("79228162514264337593543950,335", dec1);
  s21_str_to_dec("0,00000000000001", dec2);

  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooMuch);
  }

  // -79228162514264337593543950335 / 0.00000000000001 = overflow down
  s21_str_to_dec("-79228162514264337593543950335", dec1);
  s21_str_to_dec("0,00000000000001", dec2);

  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(returned_value, kErrTooSmall);
  }

  // 64733088 / 5 = 12946617,6
  s21_str_to_dec("64733088", dec1);
  s21_str_to_dec("5", dec2);
  s21_str_to_dec("12946617,6", reference);
  // s21_print_bin_dec(*dec1); 12946617,6
  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value == 0) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
  } else {
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 / 1 = same
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("1", dec2);
  s21_str_to_dec("79228162514264337593543950335", reference);

  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value == 0) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
  } else {
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 / 0 = error div 0
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0", dec2);

  returned_value = s21_div(*dec1, *dec2, result);
  ck_assert_int_eq(returned_value, kErrDivByZero);

  // 79228162514264337593543950335 / 2 = 39614081257132168796771975167,5
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("2", dec2);
  s21_str_to_dec("39614081257132168796771975168", reference);

  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value == 0) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
  } else {
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 / 2 * 10 ^ -1 = high overflow
  s21_str_to_dec("79228162514264337593543950335", dec1);
  s21_str_to_dec("0,2", dec2);
  // // s21_str_to_dec("39614081257132168796771975168", reference);
  // // 396140812571321687967719751675
  // // 396140812571321687967719751675 396140812571321687967719751675
  // // 34614081257132168796771975168,5

  returned_value = s21_div(*dec1, *dec2, result);
  ck_assert_int_eq(returned_value, kErrTooMuch);

  // 123456 / 0, 038 = 39614081257132168796771975167,5
  s21_str_to_dec("0,002", dec1);
  s21_str_to_dec("0,05", dec2);
  s21_str_to_dec("0,04", reference);

  returned_value = s21_div(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79228162514264337593543950335 * 0,0000000000000000000000000001 =
  // kErrTooSmall
  s21_str_to_dec("7922816251426433759354395033,5", dec1);
  s21_str_to_dec("0,0000000000000000000000000001", dec2);
  s21_str_to_dec("0,7922816251426433759354395034", reference);

  returned_value = s21_mul(*dec1, *dec2, result);
  if (returned_value != kErrMemory) {
    ck_assert_int_eq(s21_is_equal(*result, *reference), 1);
    ck_assert_int_eq(returned_value, 0);
  }

  // 79,228,162,514,264,337,593,543,950,335 * 8 * 10^-1 =
  // 63,382,530,011,411,470,074,835,160,268
  // res: 63382530011411470074835162268 63382530011411470074835160268

  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
  s21_free_dec(&result);
  s21_free_dec(&reference);
}
END_TEST

Suite *suite_arithmetics(void) {
  Suite *s = suite_create("arithmetics");
  TCase *tcase_core = tcase_create("arithmetics");
  // tcase_add_test(tcase_core, test_s21_compare);
  tcase_add_test(tcase_core, test_s21_add);

  suite_add_tcase(s, tcase_core);

  return s;
}