#pragma once
#include <stdint.h>

typedef enum TokenType : uint8_t {
    Null,
    Whitespace,
    Identifier,


} TokenType;

typedef struct Token {
    TokenType type;
    const char* lexeme;
    int length;
} Token;
