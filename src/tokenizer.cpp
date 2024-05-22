#include "tokenizer.h"

typedef struct Scanner_ {
  const char *start;
  const char *current;
} Scanner;

Scanner scanner;

char Peek() {
  return *scanner.current;
}

char PeekNext() {
  return *scanner.current++;
}

bool IsAlpha(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool IsDigit(char ch) {
  return ch >= '0' && ch <= '9';
}

Token String() {
  if (IsAlpha(Peek())) {
    scanner.current++;
  }
  while (IsAlpha(Peek()) || IsDigit(Peek())) {
    scanner.current++;
  }
  return MakeToken(TOKEN_STRING);
}

Token Number() {
  while (IsDigit(Peek())) {
    scanner.current++;
  }
  if (Peek() == '.' && IsDigit(scanner.current[1])) {
    scanner.current++;
  }
  while (IsDigit(Peek())) {
    scanner.current++;
  }
  return MakeToken(TOKEN_NUMBER);
}

void SkipWhiteSpace() {
  char ch = Peek();
  while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    scanner.current++;
    ch = Peek();
  }
  scanner.start = scanner.current;
}

Token MakeToken(TOKEN_TYPE type) {
  Token token;
  token.type_ = type;
  token.start_ = scanner.start;
  token.length_ = (int)(scanner.current - scanner.start);
  return token;
}

Token ScanToken() {
  SkipWhiteSpace();
  scanner.start = scanner.current;
  char ch = Peek();
  if (ch == '(' || ch == ')') {
    scanner.current++;
    return MakeToken(TOKEN_PAREN);
  }
  if (IsAlpha(ch)) {
    return String();
  }
  if (IsDigit(ch)) {
    return Number();
  }
  return MakeToken(TOKEN_ERROR);
}

std::vector<Token> Tokenizer(const char *source) {
  std::vector<Token> tokens;
  scanner.current = source;
  do {
    tokens.emplace_back(ScanToken());
  } while (tokens.back().type_ != TOKEN_ERROR);
  return tokens;
}