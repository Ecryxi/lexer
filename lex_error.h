#pragma once

typedef enum LexError {
    LEX_ERR_CLOSING_QUOTE_NOT_FOUND

} LexError;

// Emits an error
void lex_error(const char* const where, LexError error_type);