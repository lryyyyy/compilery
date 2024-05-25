#include "ast_builder.h"
#include "mu_unit.h"
#include "tokenizer.h"
#include <string.h>
#include <string>

int tests_access = 0;
int tests_failed = 0;
int tests_summary = 0;

Token MakeTestToken(TOKEN_TYPE type, const char *str) {
  Token token;
  token.type_ = type;
  token.value_ = str;
  token.length_ = strlen(str);
  return token;
}

bool TokenEq(Token *t1, Token *t2) {
  if (t1->type_ != t2->type_) {
    printf("Type error!\n");
    return false;
  }
  if (t1->length_ != t2->length_) {
    printf("Length error %d : %d!\n", t1->length_, t2->length_);
    return false;
  }
  for (int i = 0; i < t1->length_; i++) {
    if (t1->value_[i] != t2->value_[i]) {
      printf("String error %c : %c!\n", t1->value_[i], t2->value_[i]);
      return false;
    }
  }
  return true;
}

static std::string test_token() {
  Tokens tokens = Tokenizer("(add 2 (subtract 4 2))");
  Tokens result;
  result.emplace_back(MakeTestToken(TOKEN_PAREN, "("));
  result.emplace_back(MakeTestToken(TOKEN_STRING, "add"));
  result.emplace_back(MakeTestToken(TOKEN_NUMBER, "2"));
  result.emplace_back(MakeTestToken(TOKEN_PAREN, "("));
  result.emplace_back(MakeTestToken(TOKEN_STRING, "subtract"));
  result.emplace_back(MakeTestToken(TOKEN_NUMBER, "4"));
  result.emplace_back(MakeTestToken(TOKEN_NUMBER, "2"));
  result.emplace_back(MakeTestToken(TOKEN_PAREN, ")"));
  result.emplace_back(MakeTestToken(TOKEN_PAREN, ")"));
  result.emplace_back(MakeTestToken(TOKEN_ERROR, ""));
  mu_assert("tokens size not equal", tokens.size() == result.size());
  for (int i = 0; i < tokens.size(); i++) {
    mu_assert("token value not equal", TokenEq(&tokens[i], &result[i]));
  }
  return "";
}

std::string AstPrinter(Ast ast, int tab) {
  std::string result = "";
  for (int j = 0; j < tab; j++) {
    result += "  ";
  }
  for (int i = 0; i < ast.length_; i++) {
    result += ast.value_[i];
  }
  result += "\n";
  for (auto child : ast.children_) {
    result += AstPrinter(child, tab + 1);
  }
  return result;
}

static std::string test_ast() {
  Tokens tokens = Tokenizer("(add 2 (subtract 4 2))");
  Ast ast = AstBuilder(tokens);
  std::string aststr = AstPrinter(ast, 0);
  std::string result = "expr\n  add\n    2\n    expr\n      subtract\n        4\n        2\n";
  mu_assert("ast not equal", aststr == result);
  return "";
}

static void all_tests() {
  mu_run_test(test_token);
  mu_run_test(test_ast);
}

int main(int argc, char **argv) {
  all_tests();
  printf("-------Tests access : %d\n", tests_access);
  printf("-------Tests failed : %d\n", tests_failed);
  printf("-------Tests summary: %d\n", tests_summary);
  return 0;
}