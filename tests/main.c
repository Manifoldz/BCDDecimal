#include "test.h"

#define NUMBER_SUITES 7

int main(void) {
  int nf = 0;

  // srand(time(NULL)); // ATTENTION! USE ONLY FOR LEAK TESTING!

  Suite *arrSuites[NUMBER_SUITES] = {
      suite_arithmetics(), suite_bits_manipulation(), suite_aux(),
      suite_core(),        suite_compares(),          suite_rounds(),
      suite_convert()};
  for (int i = 0; i < NUMBER_SUITES; i++) {
    SRunner *sr = srunner_create(arrSuites[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    nf += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  return nf == 0 ? 0 : 1;
}

void s21_free_str(char **str_in) {
  if (str_in) {
    free(*str_in);
    *str_in = NULL;
  }
}
