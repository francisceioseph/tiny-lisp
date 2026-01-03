#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef struct {
    const char* input;
    size_t pos;
} Lexer;


char peek(Lexer* l);
void skip_junk(Lexer* l) ;

char* get_token(Lexer* lexer);

#endif