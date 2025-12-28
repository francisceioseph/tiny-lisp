#ifndef PRIM_LOGIC_H
#define PRIM_LOGIC_H

#include "object.h"

Object* primitive_equals(Object* args);
Object* primitive_less_than(Object* args);
Object* primitive_less_than_equal(Object* args);
Object* primitive_greater_than(Object* args);
Object* primitive_greater_than_equal(Object* args);
Object* primitive_not(Object* args);

#endif