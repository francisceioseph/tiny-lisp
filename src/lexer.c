#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

static void skip_whitespace(Lexer* l) {
    while(l->input[l->pos] && isspace(l->input[l->pos])) {
        l->pos++;
    }
}

static void consume_atom(Lexer* l) {
    while (l->input[l->pos] != '\0' && !isspace(l->input[l->pos]) && 
           l->input[l->pos] != '(' &&  l->input[l->pos] != ')') {
        l->pos++;
    }
}

static void consume_string(Lexer *l) {
    l->pos++;

    while (l->input[l->pos] != '\0' && l->input[l->pos] != '"') {
        if (l->input[l->pos] == '\\' && l->input[l->pos + 1] == '"') {
            l->pos += 2;
        } else {
            l->pos++;
        }
    }

    if (l->input[l->pos] == '"') {
        l->pos++;
    }
}

static char peek(Lexer* l) {
    skip_whitespace(l);
    return l->input[l->pos];
}

static char advance(Lexer* l) {
    skip_whitespace(l);
    return l->input[l->pos++];
}

static char* build_char_token(char c) {
    char* token = malloc(2 * sizeof(char));
    token[0] = c;
    token[1] = '\0';

    return token;
}

static char* build_lexer_token(Lexer* l, size_t start, size_t len) {
    char* token = malloc(len + 1);

    memcpy(token, &l->input[start], len);
    token[len] = '\0';

    return token;
}

char* get_token(Lexer* l) {
    char c = peek(l);

    if (c == '\0') {
        return NULL;
    }

    if (c == '(' || c == ')') {
        advance(l);
        return build_char_token(c);
    }

    if(c == '"') {
        size_t start = l->pos;
        consume_string(l);
        
        size_t len = l->pos - start;
        return build_lexer_token(l, start, len);
    }

    size_t start = l->pos;
    consume_atom(l);

    size_t len = l->pos - start;
    return build_lexer_token(l, start, len);
}