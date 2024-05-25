#include "ast_builder.h"
#include <stdio.h>

Ast MakeNode(Token *token) {
  Ast node;
  if (token->type_ == TOKEN_NUMBER) {
    node.type_ = AST_NUMBER_LITERAL;
    node.value_ = token->value_;
    node.length_ = token->length_;
  } else if (token->type_ == TOKEN_STRING) {
    node.type_ = AST_STRING_LITERAL;
    node.value_ = token->value_;
    node.length_ = token->length_;
    node.children_.emplace_back(MakeNode(++token));
    node.children_.emplace_back(MakeNode(++token));
  } else if (token->type_ == TOKEN_PAREN) {
    if (*token->value_ == '(') {
      node.type_ = AST_EXPRESSION;
      node.value_ = "expr";
      node.length_ = 4;
      node.children_.emplace_back(MakeNode(++token));
    } else {
        ++token;
    }
  }
  return node;
}

Ast AstBuilder(Tokens tokens) {
  Ast root;
  root = MakeNode(&tokens[0]);
  return root;
}
