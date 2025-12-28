#ifndef PRIM_MATH_H
#define PRIM_MATH_H

#include "object.h"

Object* primitive_add(Object* args);
Object* primitive_sub(Object* args);
Object* primitive_mul(Object* args);
Object* primitive_div(Object* args);

Object* primitive_min(Object* args);
Object* primitive_max(Object* args);

#endif