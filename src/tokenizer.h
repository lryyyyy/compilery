typedef enum TOKEN_ {
    TOKEN_PAREN,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_ERROR,
} TOKEN;

TOKEN Tokenizer(const char *source);