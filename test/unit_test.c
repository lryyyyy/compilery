#include "mu_unit.h"
#include <stdio.h>

#include "tokenizer.h"

int tests_access = 0;
int tests_failed = 0;
int tests_summary = 0;

static char *test_paren() {
  TOKEN token = Tokenizer("(");
  mu_assert("type: 'paren',  value: '('", token == TOKEN_PAREN);
  token = Tokenizer(")");
  mu_assert("type: 'paren',  value: ')'", token == TOKEN_PAREN);
  return 0;
}

static char *test_string() {
  TOKEN token = Tokenizer("abc1_");
  mu_assert("type: 'string',  value: 'abc1_'", token == TOKEN_STRING);
  token = Tokenizer("abc1.");
  mu_assert("type: 'string',  value: 'abc1.'", token == TOKEN_STRING);
  return 0;
}

static char *test_number() {
  TOKEN token = Tokenizer("123");
  mu_assert("type: 'number',  value: '123'", token == TOKEN_NUMBER);
  token = Tokenizer("12a");
  mu_assert("type: 'number',  value: '12a'", token == TOKEN_NUMBER);
  return 0;
}


static char *lexical_analysis_tests() {
  mu_run_test(test_paren);
  mu_run_test(test_string);
  mu_run_test(test_number);
  return 0;
}

static char *all_tests() {
  mu_run_test(lexical_analysis_tests);
  return 0;
}

int main(int argc, char **argv) {
  all_tests();
  printf("-------Tests access : %d\n", tests_access);
  printf("-------Tests failed : %d\n", tests_failed);
  printf("-------Tests summary: %d\n", tests_summary);
  return 0;
}