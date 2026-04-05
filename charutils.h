#pragma once
#include <stdbool.h>
#include "token.h"

const TokenType CHARS[128] = {
    Null,
    
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    Whitespace,
    
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,

    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    IntegerLiteral,
    
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,
    Other,

    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    
    Other,
    Other,
    Other,
    Other,
    Identifier,
    Other,

    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,
    Identifier,

    Other,
    Other,
    Other,
    Other,
    Whitespace,
};

static inline bool is_digit(const char c) {
    return (unsigned) (c - '0') <= 9;
}

static inline bool is_alpha(const char c) {
    return (unsigned) ((c | 0x20) - 'a') <= 25;
}

static inline bool is_alnum(const char c) {
    return is_digit(c) || is_alpha(c);
}

static inline bool is_ident_start(const char c) {
    return (c == '_') || is_alpha(c);
}

static inline bool is_ident(const char c) {
    return (c == '_') || is_alpha(c) || is_digit(c);
}

static inline bool is_space(const char c) {
    return (unsigned) (c - 1) <= ' '; // Space and below, except NUL, are considered whitespaces
}
