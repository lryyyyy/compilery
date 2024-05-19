#include "mu_unit.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"

int tests_access = 0;
int tests_failed = 0;
int tests_summary = 0;

Token MakeTokenStr(TOKEN_TYPE type, const char *str) {
  Token token;
  token.type_ = type;
  token.start_ = str;
  token.length_ = strlen(str);
  return token;
}

bool TokenEq(Token *t1, Token *t2) {
  if (t1->type_ != t2->type_) {
    printf("Type error!\n");
    return false;
  }
  if (t1->start_ != t2->start_) {
    printf("Start error!\n");
    return false;
  }
  if (t1->length_ != t2->length_) {
    printf("Length error %d : %d!\n", t1->length_, t2->length_);
    return false;
  }
  return true;
}

static char *test_paren() {
  Token token = Tokenizer("(");
  Token result = MakeTokenStr(TOKEN_PAREN, "(");
  mu_assert("type: 'paren',  value: '('", TokenEq(&token, &result));
  token = Tokenizer(")");
  result = MakeTokenStr(TOKEN_PAREN, ")");
  mu_assert("type: 'paren',  value: ')'", TokenEq(&token, &result));
  return 0;
}

static char *test_string() {
  Token token = Tokenizer("abc1_");
  Token result = MakeTokenStr(TOKEN_STRING, "abc1_");
  mu_assert("type: 'string',  value: 'abc1_'", TokenEq(&token, &result));
  token = Tokenizer("abc1.");
  result = MakeTokenStr(TOKEN_STRING, "abc1.");
  mu_assert("type: 'string',  value: 'abc1.'", TokenEq(&token, &result));
  return 0;
}

static char *test_number() {
  Token token = Tokenizer("123");
  Token result = MakeTokenStr(TOKEN_NUMBER, "123");
  mu_assert("type: 'number',  value: '123'", TokenEq(&token, &result));
  token = Tokenizer("12a");
  result = MakeTokenStr(TOKEN_NUMBER, "12a");
  mu_assert("type: 'number',  value: '12a'", TokenEq(&token, &result));
  return 0;
}

static char *test_token() {
  Token token = Tokenizer("(add 2 (subtract 4 2))");
  Token result = MakeTokenStr(TOKEN_PAREN, "(");
  mu_assert("type: 'paren',  value: '('", TokenEq(&token, &result));
  return 0;
}

static char *lexical_analysis_tests() {
  mu_run_test(test_paren);
  mu_run_test(test_string);
  mu_run_test(test_number);
  mu_run_test(test_token);
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