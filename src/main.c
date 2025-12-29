#include <stdio.h>

#include "env.h"
#include "eval.h"
#include "lexer.h"
#include "object.h"
#include "parser.h"
#include "setup_env.h"

int main() {
    char input[1024];

    Environment* global_env = setup_global_env();

    printf("Welcome to T-Lisp!\n");
    printf("Press Ctrl+C to exit.\n");

    while (1) {
        printf("\n");
        printf("t-lisp> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        Lexer lexer = { .input = input, .pos = 0 };

        Object* expression = parse_expression(&lexer);
        Object* result = eval(expression, global_env);

        print_object(result);
        free_object(expression);
    }

    return 0;
}