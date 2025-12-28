#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef struct {
    const char* input;
    size_t pos;
} Lexer;


char* get_token(Lexer* lexer);

#endif