#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "object.h"

typedef float (*ArithmeticFn)(float, float);

float operation_add(float a, float b);
float operation_sub(float a, float b);
float operation_mul(float a, float b);
float operation_div(float a, float b);

Object* fold_list(ArithmeticFn fn, Object* args, float initial);

#endif