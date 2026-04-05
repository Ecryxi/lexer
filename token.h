#pragma once
#include <stdint.h>

typedef enum TokenType : uint8_t {
    Null,
    Whitespace,
    Identifier,
    Other

} TokenType;

typedef struct Token {
    TokenType type;
    const char* lexeme;
    int length;
} Token;
