#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include "repl.h"
#include "eval.h"
#include "lexer.h"
#include "object.h"
#include "parser.h"

void repl(Environment *global_env) {
    printf("Tiny-Lisp REPL (Fil-C Protected)\n");
    printf("Tip: Use (define ...) to create variables.\n");
    printf("Tip: Use up/down arrows for history navigation.\n");

    char* input;

    while ((input = readline("\ntλ > ")) != NULL) {
        if (input[0] == '\0') {
            free(input);
            continue;
        }

        add_history(input);

        Lexer lexer = { .input = input, .pos = 0 };
        Object* expression = parse_expression(&lexer);

        if (expression == NULL) {
            printf("Syntax Error: unbalanced parenthesis.\n");
        }
        else {
            Object* result = eval(expression, global_env);

            print_object(result);            
            
            release(expression);
            release(result);
        }

        free(input);
    }
}