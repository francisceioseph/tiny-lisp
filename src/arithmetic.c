#include "object.h"
#include <stdio.h>
#include "arithmetic.h"

Object* fold_list(ArithmeticFn fn, Object* args, float initial) {
    float result = initial;
    Object* current = args;

    while(is_list(current)) {
        Object* target = current->data.list.car;

        if (is_number(target) == false) {
            printf("Error: operation arguments must be numbers");
            return nil;
        }

        result = fn(result, target->data.number);
        current = current->data.list.cdr;
    }

    return make_number(result);
}

float operation_add(float a, float b) {
    return a + b;
}

float operation_sub(float a, float b) {
    return a - b;
}

float operation_mul(float a, float b) {
    return a * b;
}

float operation_div(float a, float b) {
    return a / b;
}