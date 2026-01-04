#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "object.h"

Environment* env_create(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    env->symbols = nil;
    env->values = nil;
    env->parent = parent;

    return env;
}

void env_define(Environment* env, char* symbol, Object* value){
    Object* syms = env->symbols;
    Object* vals = env->values;

    while (is_list(syms) && is_list(vals)) {
        Object* current_sym = syms->data.list.car;
        
        if(strcmp(current_sym->data.symbol, symbol) == 0) {
            vals->data.list.car = retain(value);
            return;
        }

        syms = syms->data.list.cdr;
        vals = vals->data.list.cdr;
    }

    env->symbols = cons(make_symbol(symbol), env->symbols);
    env->values = cons(value, env->values);
}

Object* env_lookup(Environment* env, char* symbol) {
    Environment* current_env = env;

    while (current_env != NULL) {
        Object* syms = current_env->symbols;
        Object* vals = current_env->values;

        while (syms->type == TYPE_LIST) {
            Object* current_sym = syms->data.list.car;

            if (current_sym->type == TYPE_SYMBOL && 
                strcmp(current_sym->data.symbol, symbol) == 0) {
                return retain(vals->data.list.car);
            }

            syms = syms->data.list.cdr;
            vals = vals->data.list.cdr;
        }

        current_env = current_env->parent;
    }

    return NULL;
}