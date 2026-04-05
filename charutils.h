#pragma once

#include <stdint.h>

inline bool is_digit(const uint8_t uc) {
    return (uc - '0') <= '9';
}

inline bool is_alpha(const uint8_t uc) {
    return (uc | 0x20 - 'a') <= 'z';
}

inline bool is_alnum(const uint8_t uc) {
    return is_digit(uc) || is_alpha(uc);
}
