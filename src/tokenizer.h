#include <vector>

typedef enum TOKEN_TYPE_ {
  TOKEN_PAREN,
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_ERROR,
} TOKEN_TYPE;

typedef struct Token_ {
  TOKEN_TYPE type_;
  const char *start_;
  int length_;
} Token;

Token MakeToken(TOKEN_TYPE type);

std::vector<Token> Tokenizer(const char *source);