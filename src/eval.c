#include "eval.h"
#include "env.h"
#include "object.h"
#include <stdio.h>
#include <string.h>

Object* eval(Object* obj, Environment* env) {
    if(obj == NULL) {
        printf("Eval: obj is NULL ref\n");
        return nil;
    }

    if (obj->type == TYPE_NIL) {
        printf("Eval: obj type is nil\n");
        return nil;
    }

    if(obj->type == TYPE_NUMBER) {
        return obj;
    }

    if(obj->type == TYPE_STRING) {
        return obj;
    }

    if(obj->type == TYPE_SYMBOL) {
        Object* val = env_lookup(env, obj->data.symbol);

        if(val == NULL) {
            printf("Error: Symbol '%s' undefined\n", obj->data.symbol);
            return nil;
        }

        return val;
    }

    if(obj->type == TYPE_LIST) {
        Object* first = obj->data.list.car;

        if (first->type == TYPE_SYMBOL) {
            if(strcmp(first->data.symbol, DEFINE_SPECIAL_FORM) == 0) {
                return eval_define(obj, env);
            }

            if(strcmp(first->data.symbol, iF_SPECIAL_FORM) == 0) {
                return eval_if(obj, env);
            }

            if(strcmp(first->data.symbol, LAMBDA_SPECIAL_FORM) == 0) {
                Object* args = obj->data.list.cdr;
                Object* params = args->data.list.car;
                Object* body = args->data.list.cdr;

                return make_lambda(params, body, env);
            }

            if(strcmp(first->data.symbol, AND_SPECIAL_FORM) == 0) {
                return eval_and(obj, env);
            }

            if(strcmp(first->data.symbol, OR_SPECIAL_FORM) == 0) {
                return eval_or(obj, env);
            }

            if (strcmp(first->data.symbol, QUOTE_SPECIAL_FORM) == 0) {
                return eval_quote(obj, env);
            }

            if(strcmp(first->data.symbol, COND_SPECIAL_FORM) == 0) {
                return eval_cond(obj, env);
            }
        }

        Object* proc = eval(obj->data.list.car, env);
        Object* args = eval_list(obj->data.list.cdr, env);
        Object* result = apply(proc, args);

        release(args);
        release(proc);

        return result;
    }

    return nil;
}

Object* eval_list(Object* obj, Environment* env) {
    if(is_nil(obj)) {
        return nil;
    }

    Object* first = eval(obj->data.list.car, env);
    Object* rest = eval_list(obj->data.list.cdr, env);
    
    Object* result = cons(first, rest);

    release(first);
    release(rest);

    return result;
}

Object* eval_define(Object* obj, Environment* env) {
    Object* args = obj->data.list.cdr;

    if (args->type != TYPE_LIST) {
        printf("Error: define needs arguments.\n");
        return nil;
    }

    Object* sym_obj = args->data.list.car;
    Object* val_obj = args->data.list.cdr;

    if (sym_obj->type != TYPE_SYMBOL) {
        printf("Error: define first argument must be a symbol.\n");
        return nil;
    }

    if (val_obj->type != TYPE_LIST) {
        printf("Error: define needs a value expression.\n");
        return nil;
    }

    Object* val_exp = val_obj->data.list.car;
    Object* value = eval(val_exp, env);

    env_define(env, sym_obj->data.symbol, value);
    
    return retain(value);
}

Object* eval_if(Object* obj, Environment* env) {
    Object* args = obj->data.list.cdr;

    if (args == nil || args->type == TYPE_NIL) {
        printf("Error: missing if args\n");
        return nil;
    }

    Object* condition = eval(args->data.list.car, env);
    Object* branches = args->data.list.cdr;

    if (branches == nil || branches->type == TYPE_NIL) {
        printf("Error: missing if clauses\n");
        return nil;
    }

    if (condition != nil && condition->type != TYPE_NIL) {
        Object* then_branch = branches->data.list.car;
        return eval(then_branch, env);
    }

    Object* else_branch = branches->data.list.cdr;

    if (else_branch != nil && else_branch->type != TYPE_NIL) {
        return eval(else_branch->data.list.car, env);
    }
    

    return nil;
}

Object* eval_and(Object* obj, Environment* env) {
    Object* exprs = obj->data.list.cdr;

    if (exprs == nil || exprs->type == TYPE_NIL) {
        return make_true();
    }

    Object* result = nil;

    while (exprs != nil && exprs->type == TYPE_LIST) {
        result = eval(exprs->data.list.car, env);

        if(result == nil || result->type == TYPE_NIL) {
            return nil;
        }

        exprs = exprs->data.list.cdr;
    }

    return result;
}

Object* eval_or(Object* obj, Environment* env) {
    Object* exprs = obj->data.list.cdr;

    if (exprs != nil && exprs->type == TYPE_NIL) {
        return nil;
    }

    Object* result = nil;

    while (exprs != nil && exprs->type == TYPE_LIST) {
        result = eval(exprs->data.list.car, env);

        if (result != nil && result->type != TYPE_NIL) {
            return result;
        }

        exprs = exprs->data.list.cdr;
    }

    return result;
}

Object* eval_quote(Object* obj, Environment* env) {
    Object* vals = obj->data.list.cdr;
    return vals->data.list.car;
}

Object* eval_cond(Object* obj, Environment* env) {
    Object* clauses = obj->data.list.cdr;

    while (clauses != nil && clauses->type == TYPE_LIST) {
        Object* clause = clauses->data.list.car;


        if (clause == nil || clause->type != TYPE_LIST) {
            printf("Syntax Error: cond clause must be a list");
            return nil;
        }

        Object* test_expr = clause->data.list.car;
        Object* test_val = eval(test_expr, env);

        if (test_val != nil && test_val->type != TYPE_NIL) {
            Object* body_vals = clause->data.list.cdr;

            if (body_vals == nil || body_vals->type == TYPE_NIL) {
                return test_val;
            }

            return eval( body_vals->data.list.car, env);
        }

        clauses = clauses->data.list.cdr;
    }

    return nil;
}

Object* apply(Object* obj, Object* args) {
    if (obj == NULL || obj->type == TYPE_NIL) {
        printf("Error: Function is nil\n");
        return nil;
    }
    
    if(obj->type == TYPE_PRIMITIVE) {
        return obj->data.primitive(args);
    }

    if(obj->type == TYPE_LAMBDA) {
        Environment* parent_env = obj->data.lambda.env;

        if (parent_env == NULL) {
            printf("Error: lambda env is null.\n");
            return nil;
        }

        Environment* local_env = env_create(parent_env);

        Object* params = obj->data.lambda.params;
        Object* values = args;

        while(is_list(params) && is_list(values)) {
            Object* sym = params->data.list.car;
            Object* val = values->data.list.car;

            if (sym->type == TYPE_SYMBOL) {
                env_define(local_env, sym->data.symbol, val);
            }

            params = params->data.list.cdr;
            values = values->data.list.cdr;
        }

        Object* body = obj->data.lambda.body;
        Object* result = nil;

        while(body != nil && body->type == TYPE_LIST) {
            result = eval(body->data.list.car, local_env);
            body = body->data.list.cdr;
        }

        return result;
    }

    return nil;
}