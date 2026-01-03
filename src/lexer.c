#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

static size_t pos(Lexer* l) {
    return l->pos;
}

static char peek(Lexer* l) {
    return l->input[l->pos];
}

static char advance(Lexer* l) {
    if (l->input[l->pos] == '\0') {
        return '\0';
    }

    return l->input[l->pos++];
}

static size_t len(size_t start, size_t end) {
    return end - start;
}

static void skip_junk(Lexer* l) {
    while (true) {
        if (isspace(peek(l))) {
            advance(l);
        } 
        else if (peek(l) == ';') {
            while (peek(l) != '\0' && peek(l) != '\n') {
                advance(l);
            }
        } else {
            break;
        }
    }
}

static bool is_atom_delimiter(char c) {
    return c != '\0' && !isspace(c) && c != '(' &&  c != ')' && c != ';';
}

static void consume_atom(Lexer* l) {
    while (is_atom_delimiter(peek(l))) {
        advance(l);
    }
}

static void consume_string(Lexer *l) {    
    while (peek(l) != '\0') {
        char current = advance(l);

        if (current == '\\' && peek(l) != '\0') {
            advance(l);
        } 

        else if (current == '"') {
            return;
        }
    }

    printf("Error: string without matching quotes.");
}

static char* build_token(Lexer* l, size_t start, size_t len) {
    char* token = malloc(len + 1);

    if (!token) {
        return NULL;
    }

    memcpy(token, &l->input[start], len);
    token[len] = '\0';

    return token;
}

char* get_token(Lexer* l) {
    skip_junk(l);

    size_t start = pos(l);
    char target = peek(l);

    if (target == '\0') {
        return NULL;
    }

    if (target == '(' || target == ')') {
        advance(l);
        return build_token(l, start, 1);
    }

    if(target == '"') {
        advance(l);
        consume_string(l);
        return build_token(l, start, len(start, pos(l)));
    }

    consume_atom(l);
    return build_token(l, start, len(start, pos(l)));
}