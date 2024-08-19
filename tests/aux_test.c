#include "test.h"

START_TEST(test_s21_is_valid_str_for_convert) {
  // incorrect
  ck_assert_int_eq(s21_is_valid_str_for_convert("", 0), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("", 1), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("d", 0), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("d", 1), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-", 0), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-", 1), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2,04024040320403242,94", 0),
                   FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2,04024040320403242,94", 1),
                   FALSE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "79228162514264337593543950335123123321312312321321313213131323131",
          0),
      FALSE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "79228162514264337593543950335123123321312312321321313213131323131",
          1),
      FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("321-31", 0), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("321-31", 1), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("+-1", 0), FALSE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("+-1", 1), FALSE);

  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "7922816251426433759354395033513123321312312321321313213131323131",
          1),
      FALSE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "-7922816251426433759354395033513123321312312321321313213131323131",
          1),
      FALSE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "-792281625142643375935,4395033513123321312312321321313213131323131",
          1),
      FALSE);

  // correct
  ck_assert_int_eq(s21_is_valid_str_for_convert("+2", 0), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("+2", 1), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("+2,5", 0), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("+2,5", 1), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2,5", 0), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2,5", 1), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2", 0), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2", 1), TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert("79228162514264337593543950335", 0), TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert("79228162514264337593543950335", 1), TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert("-79228162514264337593543950335", 0), TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert("-79228162514264337593543950335", 1), TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "7922816251426433759354395033513123321312312321321313213131323131",
          0),
      TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "-7922816251426433759354395033513123321312312321321313213131323131",
          0),
      TRUE);
  ck_assert_int_eq(
      s21_is_valid_str_for_convert(
          "-792281625142643375935,4395033513123321312312321321313213131323131",
          0),
      TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2321131232131231", 0), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("-2321131232131231", 1), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("32131313123,", 0), TRUE);
  ck_assert_int_eq(s21_is_valid_str_for_convert("32131313123,", 1), TRUE);
}
END_TEST

START_TEST(test_s21_str_to_dec) {
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_dec(dec1);

  // 0
  ck_assert_int_eq(s21_str_to_dec("0", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], 0);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], 0);
  ck_assert_int_eq(dec1->bits[3], 0);

  // max 1int
  ck_assert_int_eq(s21_str_to_dec("2147483647", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], 2147483647);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], 0);
  ck_assert_int_eq(dec1->bits[3], 0);

  // min 1int
  ck_assert_int_eq(s21_str_to_dec("-2147483648", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], -2147483648);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], 0);
  ck_assert_int_eq(dec1->bits[3], 1 << 31);

  // max negative dec (was error)
  ck_assert_int_eq(s21_str_to_dec("-79228162514264337593543950335", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], ~0);
  ck_assert_int_eq(dec1->bits[1], ~0);
  ck_assert_int_eq(dec1->bits[2], ~0);
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  // max dec
  ck_assert_int_eq(s21_str_to_dec("79228162514264337593543950335", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], ~0);
  ck_assert_int_eq(dec1->bits[1], ~0);
  ck_assert_int_eq(dec1->bits[2], ~0);
  ck_assert_int_eq(dec1->bits[3], 0);
  ck_assert_int_eq(s21_get_sign(dec1), 0);

  // max dec with scale
  ck_assert_int_eq(s21_str_to_dec("7922816251426433759354395033,5", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], ~0);
  ck_assert_int_eq(dec1->bits[1], ~0);
  ck_assert_int_eq(dec1->bits[2], ~0);
  ck_assert_int_eq(s21_get_scale(dec1), 1);

  // max dec with max scale
  ck_assert_int_eq(s21_str_to_dec("7,9228162514264337593543950335", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], ~0);
  ck_assert_int_eq(dec1->bits[1], ~0);
  ck_assert_int_eq(dec1->bits[2], ~0);
  ck_assert_int_eq(s21_get_scale(dec1), 28);

  // was error
  ck_assert_int_eq(s21_str_to_dec("-1,0", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], 10);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], 0);
  ck_assert_int_eq(s21_get_scale(dec1), 1);
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  // was error
  ck_assert_int_eq(s21_str_to_dec("-1,", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], 1);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], 0);
  ck_assert_int_eq(s21_get_scale(dec1), 0);
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  // was error
  ck_assert_int_eq(s21_str_to_dec("-1", dec1), kOk);
  ck_assert_int_eq(dec1->bits[0], 1);
  ck_assert_int_eq(dec1->bits[1], 0);
  ck_assert_int_eq(dec1->bits[2], 0);
  ck_assert_int_eq(s21_get_scale(dec1), 0);
  ck_assert_int_eq(s21_get_sign(dec1), 1);

  // incorrect scale
  ck_assert_int_eq(s21_str_to_dec(",79228162514264337593543950335", dec1),
                   kErrConvert);

  s21_free_dec(&dec1);
}
END_TEST

START_TEST(test_s21_str_to_bcd_usual) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // 0
  ck_assert_int_eq(s21_str_to_bcd("0", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], 0ULL);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // 1
  ck_assert_int_eq(s21_str_to_bcd("1", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], 1ULL);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // max decimal
  ck_assert_int_eq(s21_str_to_bcd("79228162514264337593543950335", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], MAX_DEC_IN_BCD_UINT0);
  ck_assert_uint_eq(bcd1->number[1], MAX_DEC_IN_BCD_UINT1);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // max bcd
  ck_assert_int_eq(
      s21_str_to_bcd(
          "9999999999999999999999999999999999999999999999999999999999999999",
          bcd1),
      kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[1], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[2], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[3], MAX_BCD_UINT);

  // random
  ck_assert_int_eq(s21_str_to_bcd("45973495395729572975927592759761467", bcd1),
                   kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], 6424201419006809191ULL);
  ck_assert_uint_eq(bcd1->number[1], 8307262888999219863ULL);
  ck_assert_uint_eq(bcd1->number[2], 1113ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_str_to_bcd_signed) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // -0
  ck_assert_int_eq(s21_str_to_bcd("-0", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], 0ULL);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // -1
  ck_assert_int_eq(s21_str_to_bcd("-1", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], 1ULL);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // - max decimal
  ck_assert_int_eq(s21_str_to_bcd("-79228162514264337593543950335", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], MAX_DEC_IN_BCD_UINT0);
  ck_assert_uint_eq(bcd1->number[1], MAX_DEC_IN_BCD_UINT1);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // - max bcd
  ck_assert_int_eq(
      s21_str_to_bcd(
          "-9999999999999999999999999999999999999999999999999999999999999999",
          bcd1),
      kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[1], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[2], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[3], MAX_BCD_UINT);

  // random
  ck_assert_int_eq(s21_str_to_bcd("-45973495395729572975927592759761467", bcd1),
                   kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], 6424201419006809191ULL);
  ck_assert_uint_eq(bcd1->number[1], 8307262888999219863ULL);
  ck_assert_uint_eq(bcd1->number[2], 1113ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_str_to_bcd_wit_fract) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // -0 0
  ck_assert_int_eq(s21_str_to_bcd("-0,0", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 1);
  ck_assert_uint_eq(bcd1->number[0], 0ULL);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  ck_assert_int_eq(s21_str_to_bcd("0,0", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 1);
  ck_assert_uint_eq(bcd1->number[0], 0ULL);
  ck_assert_uint_eq(bcd1->number[1], 0ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // random
  ck_assert_int_eq(s21_str_to_bcd("-1,3213213123432424", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 16);
  ck_assert_uint_eq(bcd1->number[0], 3608264221382616100ULL);
  ck_assert_uint_eq(bcd1->number[1], 1ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  ck_assert_int_eq(s21_str_to_bcd("9786689763213213123432,424", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 3);
  ck_assert_uint_eq(bcd1->number[0], 3608264221382616100ULL);
  ck_assert_uint_eq(bcd1->number[1], 40674691446ULL);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // - max mant decimal left comma
  ck_assert_int_eq(s21_str_to_bcd("7,9228162514264337593543950335", bcd1), kOk);
  ck_assert_int_eq(bcd1->sign, 0);
  ck_assert_int_eq(bcd1->scale, 28);
  ck_assert_uint_eq(bcd1->number[0], MAX_DEC_IN_BCD_UINT0);
  ck_assert_uint_eq(bcd1->number[1], MAX_DEC_IN_BCD_UINT1);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // - max mant decimal right comma
  ck_assert_int_eq(s21_str_to_bcd("-79228162514264337593543950335,", bcd1),
                   kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 0);
  ck_assert_uint_eq(bcd1->number[0], MAX_DEC_IN_BCD_UINT0);
  ck_assert_uint_eq(bcd1->number[1], MAX_DEC_IN_BCD_UINT1);
  ck_assert_uint_eq(bcd1->number[2], 0ULL);
  ck_assert_uint_eq(bcd1->number[3], 0ULL);

  // - max bcd random scale
  ck_assert_int_eq(
      s21_str_to_bcd(
          "-99999999999999999999999999,99999999999999999999999999999999999999",
          bcd1),
      kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 38);
  ck_assert_uint_eq(bcd1->number[0], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[1], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[2], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[3], MAX_BCD_UINT);

  // - max bcd max scale
  ck_assert_int_eq(
      s21_str_to_bcd(
          "-9,999999999999999999999999999999999999999999999999999999999999999",
          bcd1),
      kOk);
  ck_assert_int_eq(bcd1->sign, 1);
  ck_assert_int_eq(bcd1->scale, 63);
  ck_assert_uint_eq(bcd1->number[0], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[1], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[2], MAX_BCD_UINT);
  ck_assert_uint_eq(bcd1->number[3], MAX_BCD_UINT);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_str_to_bcd_incorrect) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  // several commas
  ck_assert_int_eq(s21_str_to_bcd(",321313131432,", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("3213,13131,432", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("3213,,13131432", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd(",,", bcd1), kErrConvert);

  // only commas
  ck_assert_int_eq(s21_str_to_bcd(",", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd(",,", bcd1), kErrConvert);

  // empty string
  ck_assert_int_eq(s21_str_to_bcd("", bcd1), kErrConvert);

  // errors with signs
  ck_assert_int_eq(s21_str_to_bcd("7-922816251426450335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("7922816251426450335-", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("-7922816251426450335+", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("+-7922816251426450335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("79228162-514375-950335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("+79228162+514260335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("7962+5143375+9354335", bcd1), kErrConvert);

  // not allowed chars
  ck_assert_int_eq(s21_str_to_bcd("792281625.1426450335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("7922816251437g5950335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd(" 79228162514260335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("796251433759354335 ", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("796251433/759354335", bcd1), kErrConvert);
  ck_assert_int_eq(s21_str_to_bcd("796251433759354:335", bcd1), kErrConvert);

  // overflow
  ck_assert_int_eq(
      s21_str_to_bcd(
          "99999999999999999999999999999999999999999999999999999999999999999",
          bcd1),
      kErrConvert);

  // overflow scale
  ck_assert_int_eq(
      s21_str_to_bcd(
          ",9999999999999999999999999999999999999999999999999999999999999999",
          bcd1),
      kErrConvert);

  s21_free_bcd(&bcd1);
}
END_TEST

START_TEST(test_s21_bcd_to_str_usual) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);
  // 12 0001 0010
  bcd1->number[0] = 18;

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "12");

  s21_free_bcd(&bcd1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_bcd_to_str_scale) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->scale = 2;
  // 12345 00010010001101000101
  bcd1->number[0] = 74565;

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "123,45");

  s21_free_bcd(&bcd1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_bcd_to_str_negative) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->sign = 1;
  bcd1->scale = 2;
  // 12345 00010010001101000101
  bcd1->number[0] = 74565;

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-123,45");

  s21_free_bcd(&bcd1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_bcd_to_str_zero) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->scale = 2;
  // 12300 00010010001100000000
  bcd1->number[0] = 74496;

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "123,00");

  s21_free_bcd(&bcd1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_bcd_to_str_less0) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_clean_bcd(bcd1);

  bcd1->scale = 6;
  // 12300 00010010001100000000
  bcd1->number[0] = 74496;

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "0,012300");

  s21_free_bcd(&bcd1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_dec_to_bcd_usual) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);

  s21_dec_to_bcd(*dec1, bcd1);

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "0");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);

  dec1->bits[0] = 4;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "4");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);

  dec1->bits[0] = 8;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "8");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);

  dec1->bits[0] = ~0;
  dec1->bits[1] = ~0;
  dec1->bits[2] = ~0;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "79228162514264337593543950335");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);

  dec1->bits[0] = 15;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "15");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);

  dec1->bits[0] = 31232321;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "31232321");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  // 4
  // 8589934592
  // 39614081257132168796771975168
  dec1->bits[0] = 4;
  dec1->bits[1] = 2;
  dec1->bits[2] = 1 << 31;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "39614081257132168805361909764");

  s21_free_bcd(&bcd1);
  s21_free_dec(&dec1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_dec_to_bcd_negative) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 1;
  s21_dec_to_bcd(*dec1, bcd1);

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-1");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 9999999;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-9999999");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 455454545;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-455454545");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 1111111111;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-1111111111");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = ~0;
  dec1->bits[1] = ~0;
  dec1->bits[2] = ~0;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-79228162514264337593543950335");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 15;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-15");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 31232321;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-31232321");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);
  // 4
  // 8589934592
  // 39614081257132168796771975168
  dec1->bits[0] = 4;
  dec1->bits[1] = 2;
  dec1->bits[2] = 1 << 31;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-39614081257132168805361909764");

  s21_free_bcd(&bcd1);
  s21_free_dec(&dec1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_dec_to_bcd_scale) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);

  dec1->bits[0] = 1;
  s21_set_scale(dec1, 2);
  s21_dec_to_bcd(*dec1, bcd1);

  char *str = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-0,01");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 4);

  dec1->bits[0] = 9999999;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-999,9999");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_scale(dec1, 28);

  dec1->bits[0] = 455454545;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "0,0000000000000000000455454545");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 1);

  dec1->bits[0] = 1111111111;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-111111111,1");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 28);

  dec1->bits[0] = ~0;
  dec1->bits[1] = ~0;
  dec1->bits[2] = ~0;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-7,9228162514264337593543950335");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_scale(dec1, 15);

  dec1->bits[0] = 15;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "0,000000000000015");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 3);

  dec1->bits[0] = 31232321;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-31232,321");

  s21_clean_bcd(bcd1);
  s21_clean_dec(dec1);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 27);
  // 4
  // 8589934592
  // 39614081257132168796771975168
  dec1->bits[0] = 4;
  dec1->bits[1] = 2;
  dec1->bits[2] = 1 << 31;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_str(bcd1, str);
  ck_assert_str_eq(str, "-39,614081257132168805361909764");

  s21_free_bcd(&bcd1);
  s21_free_dec(&dec1);
  s21_free_str(&str);
}
END_TEST

START_TEST(test_s21_bcd_to_dec_usual) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  bcd *bcd2 = (bcd *)malloc(sizeof(bcd));
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  char *str1 = (char *)malloc(sizeof(char) * 67);
  char *str2 = (char *)malloc(sizeof(char) * 67);
  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 4;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 8;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = ~0;
  dec1->bits[1] = ~0;
  dec1->bits[2] = ~0;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  // 79228162514264337593543950335
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 15;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  dec1->bits[0] = 31232321;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  // 4
  // 8589934592
  // 39614081257132168796771975168
  dec1->bits[0] = 4;
  dec1->bits[1] = 2;
  dec1->bits[2] = 1 << 31;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_free_bcd(&bcd1);
  s21_free_bcd(&bcd2);
  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
  s21_free_str(&str1);
  s21_free_str(&str2);
}
END_TEST

START_TEST(test_s21_bcd_to_dec_negative) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  bcd *bcd2 = (bcd *)malloc(sizeof(bcd));
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  char *str1 = (char *)malloc(sizeof(char) * 67);
  char *str2 = (char *)malloc(sizeof(char) * 67);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec1->bits[0] = 4;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec1->bits[0] = 8;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec1->bits[0] = ~0;
  dec1->bits[1] = ~0;
  dec1->bits[2] = ~0;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  // -79228162514264337593543950335
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec1->bits[0] = 15;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);

  dec1->bits[0] = 31232321;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  // 4
  // 8589934592
  // 39614081257132168796771975168
  dec1->bits[0] = 4;
  dec1->bits[1] = 2;
  dec1->bits[2] = 1 << 31;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_free_bcd(&bcd1);
  s21_free_bcd(&bcd2);
  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
  s21_free_str(&str1);
  s21_free_str(&str2);
}
END_TEST

START_TEST(test_s21_bcd_to_dec_scale) {
  bcd *bcd1 = (bcd *)malloc(sizeof(bcd));
  bcd *bcd2 = (bcd *)malloc(sizeof(bcd));
  s21_decimal *dec1 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_decimal *dec2 = (s21_decimal *)malloc(sizeof(s21_decimal));
  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);

  s21_set_sign(dec1);
  s21_set_scale(dec1, 0);

  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  char *str1 = (char *)malloc(sizeof(char) * 67);
  char *str2 = (char *)malloc(sizeof(char) * 67);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);

  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);
  ck_assert_str_eq(str1, str2);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 2);

  dec1->bits[0] = 4;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 15);

  dec1->bits[0] = 8;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 28);

  dec1->bits[0] = ~0;
  dec1->bits[1] = ~0;
  dec1->bits[2] = ~0;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  // -79228162514264337593543950335
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 28);

  dec1->bits[0] = 15;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 1);

  dec1->bits[0] = 31232321;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_clean_bcd(bcd1);
  s21_clean_bcd(bcd2);
  s21_clean_dec(dec1);
  s21_clean_dec(dec2);
  s21_set_sign(dec1);
  s21_set_scale(dec1, 21);
  // 4
  // 8589934592
  // 39614081257132168796771975168
  dec1->bits[0] = 4;
  dec1->bits[1] = 2;
  dec1->bits[2] = 1 << 31;
  s21_dec_to_bcd(*dec1, bcd1);
  s21_bcd_to_dec(*bcd1, dec2);
  s21_dec_to_bcd(*dec2, bcd2);

  s21_bcd_to_str(bcd1, str1);
  s21_bcd_to_str(bcd2, str2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_is_equal(*dec1, *dec2), TRUE);
  ck_assert_int_eq(s21_bcd_compare(*bcd1, *bcd2), FALSE);

  s21_free_bcd(&bcd1);
  s21_free_bcd(&bcd2);
  s21_free_dec(&dec1);
  s21_free_dec(&dec2);
  s21_free_str(&str1);
  s21_free_str(&str2);
}
END_TEST

Suite *suite_aux(void) {
  Suite *s = suite_create("aux");
  TCase *tcase_core = tcase_create("aux");
  tcase_add_test(tcase_core, test_s21_is_valid_str_for_convert);
  tcase_add_test(tcase_core, test_s21_str_to_dec);
  tcase_add_test(tcase_core, test_s21_str_to_bcd_usual);
  tcase_add_test(tcase_core, test_s21_str_to_bcd_incorrect);
  tcase_add_test(tcase_core, test_s21_str_to_bcd_wit_fract);
  tcase_add_test(tcase_core, test_s21_str_to_bcd_signed);

  tcase_add_test(tcase_core, test_s21_bcd_to_str_usual);
  tcase_add_test(tcase_core, test_s21_bcd_to_str_scale);
  tcase_add_test(tcase_core, test_s21_bcd_to_str_negative);
  tcase_add_test(tcase_core, test_s21_bcd_to_str_zero);
  tcase_add_test(tcase_core, test_s21_bcd_to_str_less0);

  tcase_add_test(tcase_core, test_s21_dec_to_bcd_usual);
  tcase_add_test(tcase_core, test_s21_dec_to_bcd_negative);
  tcase_add_test(tcase_core, test_s21_dec_to_bcd_scale);

  tcase_add_test(tcase_core, test_s21_bcd_to_dec_usual);
  tcase_add_test(tcase_core, test_s21_bcd_to_dec_negative);
  tcase_add_test(tcase_core, test_s21_bcd_to_dec_scale);

  suite_add_tcase(s, tcase_core);

  return s;
}