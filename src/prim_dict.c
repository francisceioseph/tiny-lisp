#include "prim_dict.h"
#include "object.h"
#include <stdio.h>

Object* primitive_dict_make(Object *args) {
    return make_empty_dict();
}

Object* primitive_dict_get(Object* args) {
    if (!is_list(args)) {
        printf("Error: incorrect dict-get syntax");
        return nil;
    }

    Object* dict = args->data.list.car;
    Object* rest = args->data.list.cdr;

    if (!is_list(rest)) {
        printf("Error: incorrect dict-get syntax");
        return nil;
    }

    Object* key = rest->data.list.car;
    return dict_get(dict, key);
}

Object* primitive_dict_set(Object *args) {
    if (!is_list(args)) {
        printf("Error: incorrect dict-set syntax");
        return nil;
    }

    Object* dict = args->data.list.car;
    Object* params = args->data.list.cdr;

    if (!is_list(params)) {
        printf("Error: incorrect dict-set syntax");
        return nil;
    }

    Object* key = params->data.list.car;
    Object* values = params->data.list.cdr;

    if (!is_list(values)) {
        printf("Error: incorrect dict-set syntax");
        return nil;
    }

    Object* value = values->data.list.car;
    Object* result = dict_set(dict, key, value);

    return result;
}