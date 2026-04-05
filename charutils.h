#pragma once
#include <stdbool.h>

static inline bool is_digit(const char c) {
    return (unsigned) (c - '0') <= 9;
}

static inline bool is_alpha(const char c) {
    return (unsigned) ((c | 0x20) - 'a') <= 25;
}

static inline bool is_alnum(const char c) {
    return is_digit(c) || is_alpha(c);
}

inline bool is_ident_start(const uint8_t uc) {
    return (uc == '_') || is_alpha(uc);
}

inline bool is_ident(const uint8_t uc) {
    return (uc == '_') || is_alpha(uc) || is_digit(uc);
}
