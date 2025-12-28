#include <stdio.h>
#include "prim_io.h"

Object* primitive_print(Object* args) {
    if (is_list(args)) {
        Object* first = args->data.list.car;

        if (is_string(first)) {
            printf("%s\n", first->data.string);
        } else {
            print_object(first);
            printf("\n");
        }
    }

    return nil;
}