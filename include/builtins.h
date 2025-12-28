#ifndef BUILTINS_H
#define BUILTINS_H

#include "object.h"

Object* primitive_list(Object* args);
Object* primitive_print(Object* args);


Object* primitive_car(Object* args);
Object* primitive_cdr(Object* args);
Object* primitive_cons(Object* args);

#endif