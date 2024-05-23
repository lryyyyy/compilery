#pragma once

#include <vector>

typedef enum TOKEN_TYPE_ {
  TOKEN_PAREN,
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_ERROR,
} TOKEN_TYPE;

typedef struct Token_ {
  TOKEN_TYPE type_;
  const char *value_;
  int length_;
} Token;

using Tokens = std::vector<Token>;

Token MakeToken(TOKEN_TYPE type);

Tokens Tokenizer(const char *source);