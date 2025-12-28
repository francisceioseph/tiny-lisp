#include <stdio.h>

#include "arithmetic.h"
#include "object.h"
#include "prim_math.h"

Object* primitive_add(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    if (!is_number(first)) {
        printf("Error: all arguments must be numbers.\n");
        return nil;
    }

    return fold_list(operation_add, rest, first->data.number);
}

Object* primitive_sub(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;
    
    if (!is_number(first)) {
        printf("Error: all arguments mus be numbers. \n");
        return nil;    
    }
    
    float initial = first->data.number;
    Object* rest = args->data.list.cdr;

    if (is_nil(rest)) {
        return make_number(-initial);
    }

   return fold_list(operation_sub, rest, initial);
}

Object* primitive_mul(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    if (!is_number(first)) {
        printf("Error: all params must be numbers.\n");
        return nil;
    }

    return fold_list(operation_mul, rest, first->data.number);
}

Object* primitive_div(Object* args) {
    if (!is_list(args)) {
        return nil;
    }

    Object* first = args->data.list.car;

    if(!is_number(first)) {
        printf("Error: all params must be numbers.\n");
        return nil;
    }

    float initial_val = first->data.number;
    Object* rest = args->data.list.cdr;

    if(is_nil(rest)) {
        if (initial_val == 0) {
            printf("Error: cannot divide by zero.\n");
            return nil;
        }

        return make_number(1.0 / initial_val);
    }

    return fold_list(operation_div, rest, initial_val);
}