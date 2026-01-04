#include "env.h"
#include "string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "object.h"

static Object nil_object = {
    .type = TYPE_NIL,
    .ref_count = 0
};

Object* nil = &nil_object;

bool is_type(Object* obj, ObjectType type) {
    return obj != NULL && obj != nil && obj->type == type;
}

bool is_number(Object* obj) {
    return is_type(obj, TYPE_NUMBER);
}

bool is_symbol(Object* obj) {
    return is_type(obj, TYPE_SYMBOL);
}

bool is_list(Object* obj) {
    return is_type(obj, TYPE_LIST);
}

bool is_string(Object* obj) {
    return is_type(obj, TYPE_STRING);
}

bool is_nil(Object* obj) {
    return obj == NULL || obj == nil || obj->type == TYPE_NIL;
}

Object* make_number(float value) {
    Object* obj = malloc(sizeof(Object));

    obj->type = TYPE_NUMBER;
    obj->ref_count = 0;
    obj->data.number = value;

    return obj;
}

Object* make_true() {
    return make_number(1);
}

Object* make_symbol(const char* value) {
    Object* obj = malloc(sizeof(Object));

    obj->type = TYPE_SYMBOL;
    obj->ref_count = 0;
    obj->data.symbol = strdup(value);

    return obj;
}

Object* make_string(const char* value) {
    Object* obj = malloc(sizeof(Object));

    obj->type = TYPE_STRING;
    obj->ref_count = 0;
    obj->data.string = strdup(value);

    return obj;
}

Object* make_primitive(PrimitiveFunc func) {
    Object* obj = malloc(sizeof(Object));
    
    obj->type = TYPE_PRIMITIVE;
    obj->ref_count = 0;
    obj->data.primitive = func;

    return obj;
}

Object* make_lambda(Object* params, Object* body, Environment* env){
    Object* obj = malloc(sizeof(Object));

    obj->type = TYPE_LAMBDA;
    obj->ref_count = 0;
    obj->data.lambda.body = retain(body);
    obj->data.lambda.params = retain(params);
    obj->data.lambda.env = env;

    return obj;
}

Object* cons(Object* car, Object* cdr) {
    Object* obj = malloc(sizeof(Object));

    obj->type = TYPE_LIST;
    obj->ref_count = 0;
    obj->data.list.car = retain(car);
    obj->data.list.cdr = retain(cdr);

    return obj;
}

Object* retain(Object* obj) {
    if (is_nil(obj)) {
        return nil;
    }

    obj->ref_count++;
    return obj;
}

void release(Object* obj) {
    if (is_nil(obj)) {
        return;
    }

    obj->ref_count--;

    if (obj->ref_count <= 0) {
        free_object(obj);
        obj = NULL;
    }
}

void print_object(Object* obj) {
    if(obj == NULL) {
        printf("NULL pointer object \n");
        printf("nil \n");
        return;
    }

    switch (obj->type) {
        case TYPE_NIL:
            printf("nil \n");
            break;
        case TYPE_NUMBER: 
            printf("%g", obj->data.number);
            break;
        case TYPE_SYMBOL:
            printf("%s", obj->data.symbol);
            break;
        case TYPE_PRIMITIVE:
            printf("#<primitive>");
            break;
        case TYPE_LAMBDA:
            printf("#<lambda ");
            print_object(obj->data.lambda.params);
            printf(" ");
            print_object(obj->data.lambda.body);
            printf(">");
            break;
        case TYPE_LIST:
            printf("(");
            Object *current = obj;

            while (current->type == TYPE_LIST) {
                print_object(current->data.list.car);
                current = current->data.list.cdr;

                if (current->type != TYPE_NIL) {
                    printf(" ");
                }

                if (current->type != TYPE_LIST && current->type != TYPE_NIL) {
                    printf(". ");
                    print_object(current);
                    break;
                }
            }
            
            printf(")");
            break;
        case TYPE_STRING:
            printf("\"%s\"", obj->data.string);
            break;
        default:
            printf("#<UNKNOWN OBJECT> %d", obj->type);
            break;
    }
}

void free_object(Object* obj) {
    Object* current = obj;

    while (!is_nil(current)) {
        Object* next = NULL;

        switch (current->type) {
            case TYPE_SYMBOL: 
                free(current->data.symbol);
                break;

            case TYPE_STRING:
                free(current->data.string);

            case TYPE_LIST: {
                Object* car = obj->data.list.car;
                Object* cdr = obj->data.list.cdr;

                release(car);

                if (!is_nil(cdr) && cdr->ref_count <= 0) {
                    next = cdr;
                } else {
                    release(cdr);
                }

                break;
            }

            default:
                break;
        }

        Object* temp = current;
        current = next;

        free(temp);
    }
}

Object* copy_object(Object* obj) {
    if(obj == NULL || obj->type == TYPE_NIL) {
        return nil;
    }

    Object* copy = malloc(sizeof(Object));
    copy->type = obj->type;

    switch (obj->type) {
        case TYPE_NUMBER:
            copy->data.number = obj->data.number;
            break;

        case TYPE_SYMBOL:
            copy->data.symbol = strdup(obj->data.symbol);
            break;

        case TYPE_LIST:
            copy->data.list.car = copy_object(obj->data.list.car);
            copy->data.list.cdr = copy_object(obj->data.list.cdr);
            break;

        case TYPE_PRIMITIVE:
            copy->data.primitive = obj->data.primitive;
            break;

        case TYPE_LAMBDA:
            copy->data.lambda.body = copy_object(obj->data.lambda.body);
            copy->data.lambda.params = copy_object(obj->data.lambda.params);
            copy->data.lambda.env = obj->data.lambda.env;
            break;

        case TYPE_STRING:
            copy->data.string = strdup(obj->data.string);
            break;

        default:
            printf("Copy Error: cannot copy object. Returning nil");
            free(copy);
            return nil;
    }

    return copy;
}