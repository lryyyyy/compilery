#pragma once

#include "tokenizer.h"
#include <vector>

typedef enum AST_TYPE_ {
  AST_EXPRESSION,
  AST_STRING_LITERAL,
  AST_NUMBER_LITERAL,
} AST_TYPE;

typedef struct Ast_ {
  AST_TYPE type_;
  const char *value_;
  int length_;
  std::vector<struct Ast_> children_;
} Ast;

Ast MakeNode();

Ast AstBuilder(Tokens tokens);