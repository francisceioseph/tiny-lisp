#include "builtins.h"
#include "object.h"
#include <stdio.h>

Object* primitive_list(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    return args; 
}

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

Object* primitive_car(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;

    if (is_nil(first) || !is_list(first)) {
        printf("Error: invalid car syntax.\n");
        return nil;
    }

    return first->data.list.car;
};

Object* primitive_cdr(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;

    if (is_nil(first) || !is_list(first)) {
        printf("Error: invalid cdr syntax.\n");
        return nil;
    }

    return first->data.list.cdr;
};

Object* primitive_cons(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;
    Object* second = rest->data.list.car;

    return cons(first, second);
}
