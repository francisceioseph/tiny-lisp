#ifndef PRIM_LIST_H
#define PRIM_LIST_H

#include "object.h"

Object* primitive_list(Object* args);
Object* primitive_car(Object* args);
Object* primitive_cdr(Object* args);
Object* primitive_cons(Object* args);

#endif