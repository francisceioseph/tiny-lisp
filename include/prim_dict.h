#ifndef PRIM_DICT_H
#define PRIM_DICT_H

#include "object.h"

Object* primitive_dict_make(Object* args);
Object* primitive_dict_set(Object* args);
Object* primitive_dict_get(Object* args);
Object* primitive_dict_remove(Object* args);

#endif