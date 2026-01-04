#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include <stddef.h>
#include "env.h"

struct Environment;

typedef struct Object Object;
typedef struct Environment Environment;

typedef Object* (*PrimitiveFunc)(Object* args);

typedef enum {
    TYPE_NUMBER,
    TYPE_SYMBOL,
    TYPE_LIST,
    TYPE_PRIMITIVE,
    TYPE_LAMBDA,
    TYPE_STRING,
    TYPE_NIL
} ObjectType ;

struct Object {
    ObjectType type;
    int ref_count;
    union {
        float number;
        char* symbol;
        char* string;
        struct {
            struct Object* car;
            struct Object* cdr;
        } list;
        struct {
            struct Object* params;
            struct Object* body;
            struct Environment* env;
        } lambda;
        PrimitiveFunc primitive;
    } data;
};

bool is_number(Object* obj);
bool is_symbol(Object* obj);
bool is_list(Object* obj);
bool is_string(Object* obj);
bool is_nil(Object* obj);

Object* make_number(float value);
Object* make_symbol(const char* value);
Object* make_primitive(PrimitiveFunc func);
Object* make_lambda(Object* params, Object* body, Environment* env);
Object* make_string(const char* value);
Object* make_true();

Object* cons(Object* car, Object* cdr);

Object* retain(Object* obj);
void release(Object* obj);

void print_object(Object* obj);
void free_object(Object* obj);
Object* copy_object(Object* obj);

extern Object* nil;

#endif