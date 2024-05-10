#include "tokenizer.h"
#include <stdbool.h>
#include <stdio.h>

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

TOKEN String() {
  if (IsAlpha(Peek())) {
    scanner.current++;
  }
  while (IsAlpha(Peek()) || IsDigit(Peek())) {
    scanner.current++;
  }
  scanner.current--;
  scanner.current = "\0";
  printf("String Token : %s\n", scanner.start);
  return TOKEN_STRING;
}

TOKEN Number() {
  while (IsDigit(Peek())) {
    scanner.current++;
  }
  if (Peek() == '.' && IsDigit(scanner.current[1])) {
    scanner.current++;
  }
  while (IsDigit(Peek())) {
    scanner.current++;
  }
  scanner.current--;
  scanner.current = "\0";
  printf("Number Token : %s\n", scanner.start);
  return TOKEN_NUMBER;
}

void SkipWhiteSpace() {
  char ch = Peek();
  while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    scanner.current++;
  }
}

TOKEN Tokenizer(const char *source) {
  scanner.start = source;
  scanner.current = source;
  char ch = Peek();
  if (ch == '(' || ch == ')') {
    return TOKEN_PAREN;
  }
  if (IsAlpha(ch)) {
    return String();
  }
  if (IsDigit(ch)) {
    return Number();
  }
  return TOKEN_ERROR;
}