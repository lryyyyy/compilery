#include "mu_unit.h"
#include <stdio.h>

int tests_access = 0;
int tests_failed = 0;
int tests_summary = 0;

static char *test_foo() {
  int foo = 7;
  mu_assert("error, foo == 7", foo == 7);
  return 0;
}

static void all_tests() { mu_run_test(test_foo); }

int main(int argc, char **argv) {
  all_tests();
  printf("-------Tests access : %d\n", tests_access);
  printf("-------Tests failed : %d\n", tests_failed);
  printf("-------Tests summary: %d\n", tests_summary);
  return 0;
}