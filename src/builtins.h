#ifndef BUILTINS_H
#define BUILTINS_H

#include "object.h"

Object* primitive_list(Object* args);
Object* primitive_print(Object* args);

Object* primitive_equals(Object* args);
Object* primitive_less_than(Object* args);
Object* primitive_less_than_equal(Object* args);
Object* primitive_greater_than(Object* args);
Object* primitive_greater_than_equal(Object* args);
Object* primitive_min(Object* args);
Object* primitive_max(Object* args);
Object* primitive_not(Object* args);

Object* primitive_car(Object* args);
Object* primitive_cdr(Object* args);
Object* primitive_cons(Object* args);

#endif