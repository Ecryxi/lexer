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

void lex(const char* src) {
    for (;;) {
        if (!*src) return;
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
    
    for (;; src += 64, tok.length += 64) {
        const __mmask64 digits = ({
            const __m512i chunk = _mm512_loadu_epi8(src);
            const __m512i numchunk = _mm512_sub_epi8(chunk, ASCII0);
            _mm512_cmpgt_epu8_mask(numchunk, NUMBER9);
        });
        
        if (__builtin_expect(!digits, 0)) continue;
        
        tok.length += _tzcnt_u64(digits);
        return tok;
    }
    __builtin_unreachable();
}

Token lex_ident(const char* src) {
    const __m512i TO_UPPER   = _mm512_set1_epi8(~32);
    const __m512i UNDERSCORE = _mm512_set1_epi8('_');
    
    const __m512i ASCII_A    = _mm512_set1_epi8('A');
    const __m512i POSITION_Z = _mm512_set1_epi8(25); // 25th letter in the alphabet
    Token tok = { .type = Identifier, .lexeme = src, .length = 0 };

    for (;; src += 64, tok.length += 64) {
        const __mmask64 idents = ({
            const __m512i chunk = _mm512_loadu_epi8(src);
            const __m512i upper = _mm512_and_si512(chunk, TO_UPPER);
            const __m512i letterpos = _mm512_sub_epi8(upper, ASCII_A);
            const __mmask64 letters = _mm512_cmpgt_epu8_mask(letterpos, POSITION_Z);

            letters & _mm512_cmpneq_epu8_mask(chunk, UNDERSCORE);
        });

        if (__builtin_expect(!idents, 0)) continue;

        tok.length += _tzcnt_u64(idents);
        return tok;
    }

    __builtin_unreachable();
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
