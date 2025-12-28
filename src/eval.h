#ifndef EVAL_H
#define EVAL_H

#define DEFINE_SPECIAL_FORM     "define"
#define iF_SPECIAL_FORM         "if"
#define LAMBDA_SPECIAL_FORM     "lambda"
#define AND_SPECIAL_FORM        "and"
#define OR_SPECIAL_FORM         "or"
#define QUOTE_SPECIAL_FORM      "quote"
#define COND_SPECIAL_FORM       "cond"

#include "object.h"
#include "env.h"


Object* eval(Object* obj, Environment* env);
Object* eval_list(Object* obj, Environment* env);
Object* eval_define(Object* obj, Environment* env);
Object* eval_if(Object* obj, Environment* env);
Object* eval_and(Object* obj, Environment* env);
Object* eval_or(Object* obj, Environment* env);
Object* eval_quote(Object* obj, Environment* env);
Object* eval_cond(Object* obj, Environment* env);

Object* apply(Object* proc, Object* args);

#endif