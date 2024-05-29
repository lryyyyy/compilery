#include "ast_builder.h"
#include <stdio.h>

int current = 0;

Ast MakeNode(Tokens tokens) {
  Ast node;
  Token *token = &tokens[current];
  if (token->type_ == TOKEN_NUMBER) {
    node.type_ = AST_NUMBER_LITERAL;
    node.value_ = token->value_;
    node.length_ = token->length_;
  } else if (token->type_ == TOKEN_STRING) {
    node.type_ = AST_STRING_LITERAL;
    node.value_ = token->value_;
    node.length_ = token->length_;
    current++;
    node.children_.emplace_back(MakeNode(tokens));
    current++;
    node.children_.emplace_back(MakeNode(tokens));
  } else if (token->type_ == TOKEN_PAREN) {
    if (*token->value_ == '(') {
      node.type_ = AST_EXPRESSION;
      node.value_ = "expr";
      node.length_ = 4;
      current++;
      node.children_.emplace_back(MakeNode(tokens));
      current++;
      MakeNode(tokens);
    } else {
      node.type_ = AST_EXPRESSION;
      node.value_ = "rpxe";
      node.length_ = 4;
    }
  }
  return node;
}

Ast AstBuilder(Tokens tokens) {
  Ast root;
  current = 0;
  root = MakeNode(tokens);
  return root;
}

Ast AstOptimizer(Ast ast) {
  if (ast.type_ == AST_EXPRESSION && ast.children_.size() == 1) {
    ast = ast.children_[0];
  }
  for (auto &child : ast.children_) {
    child = AstOptimizer(child);
  }
  return ast;
}