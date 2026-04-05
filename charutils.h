#pragma once
#include <stdbool.h>

inline bool is_digit(const char c) {
    return (unsigned) (c - '0') <= '9';
}

inline bool is_alpha(const char c) {
    return (unsigned) (c | 0x20 - 'a') <= 'z';
}

inline bool is_alnum(const char c) {
    return is_digit(c) || is_alpha(c);
}

inline bool is_ident_start(const char c) {
    return (c == '_') || is_alpha(c);
}

inline bool is_ident(const char c) {
    return (c == '_') || is_alpha(c) || is_digit(c);
}
