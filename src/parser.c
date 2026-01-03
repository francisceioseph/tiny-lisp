#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "object.h"
#include "lexer.h"

Object* parse_token(Lexer* l, char* token);

Object* parse_list(Lexer* l) {
    char* token = get_token(l);
    
    if (token == NULL) {
        return nil;
    }

    if (strcmp(token, ")") == 0) {
        free(token);
        return nil;
    }

    Object* first = parse_token(l, token);
    Object* rest = parse_list(l);
    
    return cons(first, rest);
}

Object* parse_token(Lexer* l, char* token) {
    // 1. Handle nested lists
    if (strcmp(token, "(") == 0) {
        free(token);
        return parse_list(l);
    }

    // 2. Handle Numbers
    char* endptr;
    float val = strtof(token, &endptr);
    if (*endptr == '\0') {
        free(token);
        return make_number(val);
    }

    // 3. Handle Strings
    if (token[0] == '"') {
        size_t len = strlen(token);

        char* content = malloc((len - 1) * sizeof(char));
        char* start_ptr = token + 1;

        strncpy(content, start_ptr, len - 2);
        content[len - 2] = '\0';

        Object* obj = make_string(content);
        free(content);
        free(token);
        
        return obj;
    }

    // 4. Handle Symbols
    Object* obj = make_symbol(token);
    free(token);
    return obj;
}

Object* parse_expression(Lexer* lexer) {
    char* token = get_token(lexer);
    if (!token) return nil;
    return parse_token(lexer, token);
}