#include <math.h>

#include "setup_env.h"
#include "object.h"
#include "prim_io.h"
#include "prim_list.h"
#include "prim_logic.h"
#include "prim_math.h"

Environment* setup_global_env() {
    Environment* global_env = env_create(NULL);

    env_define(global_env, "+", make_primitive(primitive_add));
    env_define(global_env, "-", make_primitive(primitive_sub));
    env_define(global_env, "*", make_primitive(primitive_mul));
    env_define(global_env, "/", make_primitive(primitive_div));

    env_define(global_env, "pi", make_number(M_PI));
    env_define(global_env, "nil", nil);
    env_define(global_env, "t", make_true());
    
    env_define(global_env, "print", make_primitive(primitive_print));

    env_define(global_env, "list", make_primitive(primitive_list));
    env_define(global_env, "car", make_primitive(primitive_car));
    env_define(global_env, "cdr", make_primitive(primitive_cdr));
    env_define(global_env, "cons", make_primitive(primitive_cons));

    env_define(global_env, "=", make_primitive(primitive_equals));
    env_define(global_env, "<", make_primitive(primitive_less_than));
    env_define(global_env, ">", make_primitive(primitive_greater_than));
    env_define(global_env, "<=", make_primitive(primitive_less_than_equal));
    env_define(global_env, ">=", make_primitive(primitive_greater_than_equal));
    env_define(global_env, "min", make_primitive(primitive_min));
    env_define(global_env, "max", make_primitive(primitive_max));

    env_define(global_env, "not", make_primitive(primitive_not));

    return global_env;
}