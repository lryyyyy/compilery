#include "code_generator.h"

Tokens CodeGenerator(Ast ast) {
  Tokens result;
  if (ast.type_ == AST_STRING_LITERAL) {
    {
      Token token;
      token.type_ = TOKEN_STRING;
      token.value_ = ast.value_;
      token.length_ = ast.length_;
      result.emplace_back(token);
    }
    {
      Token token;
      token.type_ = TOKEN_PAREN;
      token.value_ = "(";
      token.length_ = 1;
      result.emplace_back(token);
    }
    for (auto child : ast.children_) {
      for (auto token : CodeGenerator(child)) {
        result.emplace_back(token);
      }
      {
        Token token;
        token.type_ = TOKEN_DOT;
        token.value_ = ", ";
        token.length_ = 2;
        result.emplace_back(token);
      }
    }
    result.pop_back();
    {
      Token token;
      token.type_ = TOKEN_PAREN;
      token.value_ = ")";
      token.length_ = 1;
      result.emplace_back(token);
    }
  } else if (ast.type_ == AST_NUMBER_LITERAL) {
    for (int i = 0; i < ast.length_; i++) {
      Token token;
      token.type_ = TOKEN_NUMBER;
      token.value_ = ast.value_;
      token.length_ = ast.length_;
      result.emplace_back(token);
    }
  }
  return result;
}