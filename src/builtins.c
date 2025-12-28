#include "builtins.h"
#include "object.h"
#include <stdio.h>
#include <string.h>

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

Object* primitive_equals(Object* args) {
    if (!is_list(args)) {
        return make_true();
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while(is_list(rest)) {
        Object* target = rest->data.list.car;

        if(first->type == target->type && first->type == TYPE_NIL) {
            // do nothing at all
        } else if (is_number(first) && is_number(target)) {
            float num1 = first->data.number;
            float num2 = target->data.number;

            if (num1 != num2) {
                return nil;
            }
        }
        else if (is_symbol(first) && is_symbol(target)) {
            char* sym1 = first->data.symbol;
            char* sym2 = target->data.symbol;

            if (strcmp(sym1, sym2) != 0) {
                return nil;
            }
        }
        else if (is_string(first) && is_string(target)) {
            char* str1 = first->data.string;
            char* str2 = target->data.string;

            if (strcmp(str1, str2) != 0) {
                return nil;
            }
        } else {
            return nil;
        }

        first = target;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_less_than(Object* args) {
    if (!is_list(args)) {
        return make_true();
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while(is_list(rest)) {
        Object* target = rest->data.list.car;

        if (is_number(first) && is_number(target)) {
            float num1 = first->data.number;
            float num2 = target->data.number;

            if (num1 >= num2) {
                return nil;
            }
        } else {
            return nil;
        }

        first = target;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_less_than_equal(Object* args) {
    if (!is_list(args)) {
        return make_true();
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while (is_list(rest)) {
        Object* target = rest->data.list.car;

        if (is_number(first) && is_number(target)) {
            float num1 = first->data.number;
            float num2 = target->data.number;

            if (num1 > num2) {
                return nil;
            }
        } else {
            return nil;
        }

        first = rest;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_greater_than(Object* args) {
    if (!is_list(args)) {
        return make_true();
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while(is_list(rest)) {
        Object* target = rest->data.list.car;

        if (is_number(first) && is_number(target)) {
            float num1 = first->data.number;
            float num2 = target->data.number;

            if (num1 <= num2) {
                return nil;
            }
        } else {
            return nil;
        }

        first = target;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_greater_than_equal(Object* args) {
    if (!is_list(args)) {
        make_true();
    }

    Object* first = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while (is_list(rest)) {
        Object* target = rest->data.list.car;

        if (is_number(first) && is_number(target)) {
            float num1 = first->data.number;
            float num2 = target->data.number;

            if (num1 < num2) {
                return nil;
            }
        } else {
            return nil;
        }
    }

    return make_true();
}

Object* primitive_not(Object* args) {
     if (is_list(args)) {
        return make_true();
    }

    Object* first = args->data.list.car;

    if (is_nil(first)) {
        return make_true();
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
