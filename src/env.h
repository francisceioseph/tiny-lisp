#ifndef ENV_H
#define ENV_H

struct Object;

typedef struct Object Object;
typedef struct Environment Environment;

struct Environment {
    Object* symbols;
    Object* values;
    struct Environment* parent;
};

Environment* env_create(Environment* parent);

void env_define(Environment* env, char* symbol, Object* value);

Object* env_lookup(Environment* env, char* symbol);

#endif