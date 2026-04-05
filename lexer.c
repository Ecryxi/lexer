#include <immintrin.h>
#include <x86intrin.h>
#include <string.h>

#include "token.h"
#include "lex_error.h"
#include "charutils.h"

// Adds a new token
void emit_token(Token tok);

// Helpers
Token lex_number(const char* src);
Token lex_ident(const char* src);
Token lex_string(const char* src);

// Really basic lexer, unoptimized
void lex(const char* src) {
    while (*src) {
        if (is_space(*src)) {
            src++;
            continue;
        }

        Token tok;
        if (is_ident_start(*src)) {
            tok = lex_ident(src);
            goto add_token;
        }

        if (is_digit(*src)) {
            tok = lex_number(src);
            goto add_token;
        }
        
        if (*src == '"') {
            tok = lex_string(src);
            goto add_token;   
        }

        tok.type = Other;
        tok.lexeme = src;
        tok.length = 1;

    add_token:
        src += tok.length;
        emit_token(tok);
    }

}

Token lex_number(const char* src) {
    const __m512i ASCII0 = _mm512_set1_epi8('0');
    const __m512i NUMBER9 = _mm512_set1_epi8(9);
    Token tok = { .type = IntegerLiteral, .lexeme = src, .length = 0 };
    
    for (;; src += 64) {
        const __mmask64 digits = ({
            const __m512i chunk = _mm512_loadu_epi8(src);
            const __m512i numchunk = _mm512_sub_epi8(chunk, ASCII0);
            _mm512_cmpgt_epu8_mask(numchunk, NUMBER9);
        });
        
        if (__builtin_expect(!digits, 0)) continue;
        
        tok.length += _tzcnt_u64(digits);
        return tok;
    }
}

Token lex_ident(const char* src) {
    const char* ptr = src;
    for (; is_ident(*ptr); ptr++);

    return (Token) {
        .type = Identifier,
        .lexeme = src,
        .length = ptr - src
    };
}

Token lex_string(const char* src) {
    const char* next_quote = strchr(src + 1, '"');

    if (!next_quote)
        lex_error(src, LEX_ERR_CLOSING_QUOTE_NOT_FOUND);
    
    return (Token) {
        .type = StringLiteral,
        .lexeme = src,
        .length = 1 + next_quote - src
    };
}
