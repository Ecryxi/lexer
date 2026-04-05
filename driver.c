#include <stdio.h>
#include <stdlib.h>

#include "lexer.c"

const char* SOURCE_CODE = R"(
fn main() {
    printn("Hello, world!");
}
)";

int main() {
    lex(SOURCE_CODE);
}

// Implementation of the emit_token function, required by the lexer
// TODO: Use an array instead of `printf` - it's faster -
void emit_token(Token tok) {
    printf("Type:%d(`%.*s`)\n", tok.type, tok.length, tok.lexeme);
}

void lex_error(const char *const where, LexError error_type) {
    printf("!!  Lexer reported error (%d). Aborting.", error_type);
    printf("    Location: %d", (int) (where - SOURCE_CODE));
    abort();
}