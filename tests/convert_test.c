#include <limits.h>

#include "test.h"
START_TEST(test_s21_from_decimal_to_int_zero) {
  s21_decimal src;
  int dst;
  int result;
  src.bits[0] = 0;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_positive) {
  s21_decimal src;
  int dst;
  int result;

  src.bits[0] = 12345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 12345);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_negative) {
  s21_decimal src;
  int dst;
  int result;

  src.bits[0] = 12345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 1U << 31;
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, -12345);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_scale_sign) {
  s21_decimal src;
  int dst;
  int result;

  src.bits[0] = 12345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 1 << 16;
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 1234);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_scale_sign2) {
  s21_decimal src;
  int dst;
  int result;

  src.bits[0] = 12345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  s21_set_scale(&src, 4);
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_max_int) {
  s21_decimal src;
  int dst;
  int result;

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, INT_MAX);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_max_int_err) {
  s21_decimal src;
  int dst;
  int result;

  src.bits[0] = 0;
  src.bits[1] = 1;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, kErrConvert);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_min_int) {
  s21_decimal src;
  int dst = 0;
  int result;
  src.bits[0] = INT_MIN;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  s21_set_sign(&src);
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, INT_MIN);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_min_int_err) {
  s21_decimal src;
  int dst = 0;
  int result;
  src.bits[0] = 0;
  src.bits[1] = 1;
  src.bits[2] = 0;
  src.bits[3] = 0;
  s21_set_sign(&src);
  result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, kErrConvert);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal) {
  s21_decimal dst;
  int src;
  int result;

  // Тест на конвертацию нуля
  src = 0;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert(result == 0);
  ck_assert(dst.bits[0] == 0);
  ck_assert(dst.bits[1] == 0);
  ck_assert(dst.bits[2] == 0);
  ck_assert(dst.bits[3] == 0);

  // Тест на конвертацию положительного числа
  src = 12345;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert(result == 0);
  ck_assert(dst.bits[0] == 12345);
  ck_assert(dst.bits[1] == 0);
  ck_assert(dst.bits[2] == 0);
  ck_assert(dst.bits[3] == 0);

  // Тест на конвертацию отрицательного числа
  src = -12345;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert(result == 0);
  ck_assert(dst.bits[0] == 12345);
  ck_assert(dst.bits[1] == 0);
  ck_assert(dst.bits[2] == 0);
  ck_assert(dst.bits[3] >> 31);

  // Тест на конвертацию числа с масштабом
  src = 12345;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert(result == 0);
  ck_assert(dst.bits[0] == 12345);
  ck_assert(dst.bits[1] == 0);
  ck_assert(dst.bits[2] == 0);
  ck_assert(dst.bits[3] == 0);

  // Тест на конвертацию числа с масштабом и знаком
  src = -12345;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert(result == 0);
  ck_assert(dst.bits[0] == (unsigned int)12345);
  ck_assert(dst.bits[1] == 0);
  ck_assert(dst.bits[2] == 0);
  ck_assert(dst.bits[3] >> 31);

  // Тест на конвертацию максимального значения int
  src = INT_MAX;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], INT_MAX);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  // Без знака
  ck_assert_int_eq(dst.bits[3], 0);

  // Тест на конвертацию минимального значения int
  src = INT_MIN;
  result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  // -2147483648 в uint
  ck_assert_int_eq((unsigned int)dst.bits[0], (unsigned int)INT_MIN);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] >> 31, -1);
}
END_TEST
START_TEST(s21_from_float_to_decimal_test) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal res = {{2147489, 0, 0, 1 << 16}};
  float num_1 = 214748.9;
  s21_from_float_to_decimal(num_1, &value_1);
  ck_assert_int_eq(value_1.bits[0], res.bits[0]);
  ck_assert_int_eq(value_1.bits[1], res.bits[1]);
  ck_assert_int_eq(value_1.bits[2], res.bits[2]);
  ck_assert_int_eq(value_1.bits[3], res.bits[3]);

  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res2 = {{2147489, 0, 0, (1 << 31) | (1 << 16)}};
  float num_2 = -214748.9;
  s21_from_float_to_decimal(num_2, &value_2);
  ck_assert_int_eq(value_2.bits[0], res2.bits[0]);
  ck_assert_int_eq(value_2.bits[1], res2.bits[1]);
  ck_assert_int_eq(value_2.bits[2], res2.bits[2]);
  ck_assert_int_eq(value_2.bits[3], res2.bits[3]);

  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal res3 = {{2134530, 0, 0, 1 << 18 | 1 << 16}};
  float num_3 = 21.3453;
  s21_from_float_to_decimal(num_3, &value_3);
  ck_assert_int_eq(value_3.bits[0], res3.bits[0]);
  ck_assert_int_eq(value_3.bits[1], res3.bits[1]);
  ck_assert_int_eq(value_3.bits[2], res3.bits[2]);
  ck_assert_int_eq(value_3.bits[3], res3.bits[3]);

  s21_decimal value_4 = {{0, 0, 0, 0}};
  s21_decimal res4 = {{10000000, 0, 0, 3 << 19 | 1 << 17}};
  float num_4 = 0.0000000000000000001f;
  s21_from_float_to_decimal(num_4, &value_4);
  ck_assert_int_eq(value_4.bits[0], res4.bits[0]);
  ck_assert_int_eq(value_4.bits[1], res4.bits[1]);
  ck_assert_int_eq(value_4.bits[2], res4.bits[2]);
  ck_assert_int_eq(value_4.bits[3], res4.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_int) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  float num_1 = 21474836.7;
  ck_assert_int_eq(0, s21_from_float_to_decimal(num_1, &value_1));
}
END_TEST

START_TEST(s21_from_float_to_decimal_error) {
  s21_decimal value_1 = {{5, 5, 5, 5}};
  float num_1 = 0.0000000000000000000000000000000000001f;
  s21_from_float_to_decimal(num_1, &value_1);
  s21_decimal error_1 = {{0, 0, 0, 0}};
  ck_assert_int_eq(value_1.bits[0], error_1.bits[0]);
  ck_assert_int_eq(value_1.bits[1], error_1.bits[1]);
  ck_assert_int_eq(value_1.bits[2], error_1.bits[2]);
  ck_assert_int_eq(value_1.bits[3], error_1.bits[3]);

  s21_decimal value_2 = {{5, 5, 5, 0}};
  float num_2 = 0.0000000000000000000000000000000000001f;
  int fun2 = s21_from_float_to_decimal(num_2, &value_2);
  int error_2 = 1;
  ck_assert_int_eq(fun2, error_2);

  s21_decimal value_3 = {{5, 5, 5, 0}};
  float num_3 = 792281625142643375935439503351234.0;
  int fun3 = s21_from_float_to_decimal(num_3, &value_3);
  int error_3 = 1;
  ck_assert_int_eq(fun3, error_3);

  s21_decimal value_4 = {{5, 5, 5, 0}};
  float num_4 = NAN;
  int fun4 = s21_from_float_to_decimal(num_4, &value_4);
  int error_4 = 1;
  ck_assert_int_eq(fun4, error_4);
}
END_TEST

START_TEST(s21_from_float_to_decimal_new) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal res1 = {{7922816, 0, 0, 6 << 16}};
  float num_1 = 7.922816e+00;
  int fun1 = s21_from_float_to_decimal(num_1, &value_1);
  int error_1 = 0;
  ck_assert_int_eq(value_1.bits[0], res1.bits[0]);
  ck_assert_int_eq(value_1.bits[1], res1.bits[1]);
  ck_assert_int_eq(value_1.bits[2], res1.bits[2]);
  ck_assert_int_eq(value_1.bits[3], res1.bits[3]);
  ck_assert_int_eq(fun1, error_1);

  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res2 = {{536870912U, 3012735514U, 4294967159U, 0}};
  float num_2 = 7.922816e+28;
  int fun2 = s21_from_float_to_decimal(num_2, &value_2);
  // s21_print_dec_fm(value_2);
  int error_2 = 0;
  ck_assert_int_eq(value_2.bits[0], res2.bits[0]);
  ck_assert_int_eq(value_2.bits[1], res2.bits[1]);
  ck_assert_int_eq(value_2.bits[2], res2.bits[2]);
  ck_assert_int_eq(value_2.bits[3], res2.bits[3]);
  ck_assert_int_eq(fun2, error_2);

  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal res3 = {{3141593, 0, 0, 6 << 16}};
  float num_3 = 3.141593e+00;
  int fun3 = s21_from_float_to_decimal(num_3, &value_3);
  // s21_print_dec_fm(value_3);
  int error_3 = 0;
  ck_assert_int_eq(value_3.bits[0], res3.bits[0]);
  ck_assert_int_eq(value_3.bits[1], res3.bits[1]);
  ck_assert_int_eq(value_3.bits[2], res3.bits[2]);
  ck_assert_int_eq(value_3.bits[3], res3.bits[3]);
  ck_assert_int_eq(fun3, error_3);

  s21_decimal value_4 = {{0, 0, 0, 0}};
  s21_decimal res4 = {{2718282, 0, 0, 1 << 31 | 6 << 16}};
  float num_4 = -2.718282e+00;
  int fun4 = s21_from_float_to_decimal(num_4, &value_4);
  // s21_print_dec_fm(value_4);
  int error_4 = 0;
  ck_assert_int_eq(value_4.bits[0], res4.bits[0]);
  ck_assert_int_eq(value_4.bits[1], res4.bits[1]);
  ck_assert_int_eq(value_4.bits[2], res4.bits[2]);
  ck_assert_int_eq(value_4.bits[3], res4.bits[3]);
  ck_assert_int_eq(fun4, error_4);

  s21_decimal value_5 = {{0, 0, 0, 0}};
  s21_decimal res5 = {{12346, 0, 0, 1 << 31 | 28 << 16}};
  float num_5 = -1.234568e-24;
  int fun5 = s21_from_float_to_decimal(num_5, &value_5);
  int error_5 = 0;
  ck_assert_int_eq(value_5.bits[0], res5.bits[0]);
  ck_assert_int_eq(value_5.bits[1], res5.bits[1]);
  ck_assert_int_eq(value_5.bits[2], res5.bits[2]);
  ck_assert_int_eq(value_5.bits[3], res5.bits[3]);
  ck_assert_int_eq(fun5, error_5);

  s21_decimal value_6 = {{5, 5, 5, 5}};
  s21_decimal res6 = {{0, 0, 0, 0}};
  float num_6 = 0.000000e+00;
  int fun6 = s21_from_float_to_decimal(num_6, &value_6);
  int error_6 = 0;
  ck_assert_int_eq(value_6.bits[0], res6.bits[0]);
  ck_assert_int_eq(value_6.bits[1], res6.bits[1]);
  ck_assert_int_eq(value_6.bits[2], res6.bits[2]);
  ck_assert_int_eq(value_6.bits[3], res6.bits[3]);
  ck_assert_int_eq(fun6, error_6);

  s21_decimal value_7 = {{0, 0, 0, 0}};
  float num_7 = 7.932819e+28;
  int fun7 = s21_from_float_to_decimal(num_7, &value_7);
  // s21_print_dec_fm(value_6);
  int error_7 = 1;
  ck_assert_int_eq(fun7, error_7);

  s21_decimal value_8 = {{5, 5, 5, 5}};
  s21_decimal res8 = {{0, 0, 0, 0}};
  float num_8 = 1.234568e-29;
  int fun8 = s21_from_float_to_decimal(num_8, &value_8);
  int error_8 = 1;
  ck_assert_int_eq(value_8.bits[0], res8.bits[0]);
  ck_assert_int_eq(value_8.bits[1], res8.bits[1]);
  ck_assert_int_eq(value_8.bits[2], res8.bits[2]);
  ck_assert_int_eq(value_8.bits[3], res8.bits[3]);
  ck_assert_int_eq(fun8, error_8);

  s21_decimal value_9 = {{0, 0, 0, 0}};
  s21_decimal res9 = {{0, 0, 0, 0}};
  float num_9 = 9.000000e-29;
  int fun9 = s21_from_float_to_decimal(num_9, &value_9);
  int error_9 = 1;
  ck_assert_int_eq(value_9.bits[0], res9.bits[0]);
  ck_assert_int_eq(value_9.bits[1], res9.bits[1]);
  ck_assert_int_eq(value_9.bits[2], res9.bits[2]);
  ck_assert_int_eq(value_9.bits[3], res9.bits[3]);
  ck_assert_int_eq(fun9, error_9);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test) {
  s21_decimal value_1 = {{2147489, 0, 0, 1 << 16}};
  float res = 214748.9;
  float num_1 = 0;
  s21_from_decimal_to_float(value_1, &num_1);
  ck_assert_float_eq(res, num_1);

  s21_decimal value_2 = {{2147489, 0, 0, 1 << 31}};
  float res2 = -2147489.0;
  float num_2 = 0;
  s21_from_decimal_to_float(value_2, &num_2);
  ck_assert_float_eq(res2, num_2);

  s21_decimal value_4 = {{2147489, 0, 0, (1 << 31) | (1 << 16)}};
  float res4 = -214748.9;
  float num_4 = 0;
  s21_from_decimal_to_float(value_4, &num_4);
  ck_assert_float_eq(res4, num_4);

  s21_decimal value_3 = {{213453, 0, 0, 1 << 18}};
  float res3 = 21.3453;
  float num_3 = 0;
  s21_from_decimal_to_float(value_3, &num_3);
  ck_assert_float_eq(res3, num_3);
}
END_TEST

START_TEST(s21_from_decimal_to_float_int) {
  s21_decimal value_1 = {{213453, 0, 0, 1 << 18}};
  float num_1 = 0;
  s21_from_decimal_to_float(value_1, &num_1);
  ck_assert_int_eq(21.3453, num_1);
}
END_TEST

START_TEST(get_scale) {
  int err = 0;
  s21_decimal *dec1 = s21_init_dec(&err);
  dec1->bits[DEC_INTS - 1] = 4;
  dec1->bits[DEC_INTS - 1] <<= 16;
  int testgs = 4;
  ck_assert_uint_eq(s21_get_scale(dec1), testgs);
  s21_free_dec(&dec1);

  s21_decimal *dec2 = s21_init_dec(&err);
  dec2->bits[DEC_INTS - 1] = 4;
  dec2->bits[DEC_INTS - 1] <<= 16;
  int testgs2 = 4;
  ck_assert_uint_eq(s21_get_scale(dec2), testgs2);
  s21_free_dec(&dec2);

  s21_decimal *dec3 = s21_init_dec(&err);
  dec3->bits[DEC_INTS - 1] = 4;
  dec3->bits[DEC_INTS - 1] <<= 16;
  int testgs3 = 4;
  ck_assert_uint_eq(s21_get_scale(dec3), testgs3);
  s21_free_dec(&dec3);
}
END_TEST

START_TEST(setscale) {
  int err = 0;
  s21_decimal *dec1 = s21_init_dec(&err);
  s21_set_scale(dec1, 28);
  int tests = 28;
  ck_assert_uint_eq(s21_get_scale(dec1), tests);
  s21_free_dec(&dec1);

  s21_decimal *dec2 = s21_init_dec(&err);
  s21_set_scale(dec2, 5);
  int test2 = 5;
  ck_assert_uint_eq(s21_get_scale(dec2), test2);
  s21_free_dec(&dec2);

  s21_decimal *dec3 = s21_init_dec(&err);
  s21_set_scale(dec3, 0);
  int test3 = 0;
  ck_assert_uint_eq(s21_get_scale(dec3), test3);
  s21_free_dec(&dec3);
}
END_TEST

Suite *suite_convert(void) {
  Suite *s = suite_create("convert");
  TCase *tc1_1 = tcase_create("convert");

  tcase_add_test(tc1_1, s21_from_float_to_decimal_new);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_test);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_int);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_error);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_test);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_int);
  tcase_add_test(tc1_1, get_scale);
  tcase_add_test(tc1_1, setscale);

  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_min_int);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_min_int_err);
  tcase_add_test(tc1_1, test_s21_from_int_to_decimal);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_zero);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_positive);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_negative);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_scale_sign);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_scale_sign2);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_max_int);
  tcase_add_test(tc1_1, test_s21_from_decimal_to_int_max_int_err);

  suite_add_tcase(s, tc1_1);

  return s;
}