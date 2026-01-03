#include <stdio.h>
#include <stdlib.h>

#include "runner.h"
#include "env.h"
#include "eval.h"
#include "io.h"
#include "lexer.h"
#include "object.h"
#include "parser.h"

void run_file(char* filename, Environment* env) {
    char* source = read_file(filename);
    
    printf("Tiny-Lisp Runner (Fil-C Protected)\n\n");

    if (!source) {
        printf("Error: source not found or empty.\n");
        free(source);
        return;
    }

    Lexer lexer = { .input = source, .pos = 0 };
    Lexer* lex = &lexer;

    while (peek(lex) != '\0') {
        skip_junk(lex);

        Object* expression = parse_expression(lex);

        if (peek(lex) == '\0') {
            break;
        }

        Object* result = eval(expression, env);

        free_object(expression);
    }

    free(source);
}