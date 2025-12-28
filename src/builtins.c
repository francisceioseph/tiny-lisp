#include "builtins.h"
#include "object.h"
#include <stdio.h>
#include <string.h>

Object* primitive_add(Object* args) {
    if (args == nil || args->type != TYPE_LIST) {
        return make_number(0);
    }

    Object* val1 = args->data.list.car;

    if (val1 == nil || val1->type != TYPE_NUMBER) {
        printf("[primitive_add] Error: all params must be numbers.\n");
        return nil;
    }

    float result = val1->data.number;

    Object* current = args->data.list.cdr;
    while(current != nil && current->type == TYPE_LIST) {
        Object* val2 = current->data.list.car;

        if (val2 == nil || val2->type != TYPE_NUMBER) {
            printf("[primitive_add] Error: all params must be numbers. \n");
            return nil;
        }

        result += val2->data.number;
        current = current->data.list.cdr;
    }

    return make_number(result);
}

Object* primitive_sub(Object* args) {
    if (args == nil || args->type != TYPE_LIST) {
        return make_number(0);
    }

    Object* val1 = args->data.list.car;
    
    if (val1->type != TYPE_NUMBER) {
        printf("[primitive_sub] Error: argument is not a number! \n");
        return nil;    
    }

    float result = val1->data.number;
    Object* current = args->data.list.cdr;

    if (current == nil || current->type == TYPE_NIL) {
        return make_number(-result);
    }

    while (current != nil && current->type == TYPE_LIST) {
        Object* val2 = current->data.list.car;

        if (val2 == nil || val2->type != TYPE_NUMBER) {
            printf("[primitive_sub] Error: argument is not a number! \n");
            return nil;
        }

        result -= val2->data.number;
        current = current->data.list.cdr;
    }

    return make_number(result);
}

Object* primitive_mul(Object* args) {
    if (args == nil || args->type != TYPE_LIST) {
        return make_number(1);
    }

    Object* val1 = args->data.list.car;

    if (val1 == nil || val1->type != TYPE_NUMBER) {
        printf("[primitive_mul] Error: all params must be numbers.\n");
        return nil;
    }

    float result = val1->data.number;

    Object* current = args->data.list.cdr;
    while(current != nil && current->type == TYPE_LIST) {
        Object* val2 = current->data.list.car;

        if (val2 == nil || val2->type != TYPE_NUMBER) {
            printf("[primitive_mul] Error: all params must be numbers. \n");
            return nil;
        }

        result *= val2->data.number;
        current = current->data.list.cdr;
    }

    return make_number(result);
}

Object* primitive_div(Object* args) {
    if (args == nil || args->type != TYPE_LIST) {
        return nil;
    }

    Object* val1 = args->data.list.car;
    if(val1->type != TYPE_NUMBER) {
        printf("[primitive_div] Error: all params must be numbers.\n");
        return nil;
    }

    float result = val1->data.number;

    Object* current = args->data.list.cdr;
    if(current->type == TYPE_NIL) {
        if (result == 0) {
            printf("[primitive_div] Error: cannot divide by zero.\n");
            return nil;
        }

        return make_number(1.0 / result);
    }

    while (current->type == TYPE_LIST) {
        Object* val2 = current->data.list.car;

        if(val2 == nil || val2->type != TYPE_NUMBER) {
            printf("[primitive_div] Error: all params must be numbers.\n");
            return nil;
        }

        if (val2->data.number == 0) {
            printf("[primitive_div] Error: cannot divide by zero.\n");
            return nil;
        }

        result /= val2->data.number;
        current = current->data.list.cdr;
    }

    return make_number(result);
}

Object* primitive_list(Object* args) {
    // In Lisp, (list 1 2 3) passes (1 2 3) as the 'args'
    // So we just return the args exactly as they are.
    return args; 
}

Object* primitive_print(Object* args) {
    if (args->type == TYPE_LIST) {
        Object* val = args->data.list.car;

        if (val->type == TYPE_STRING) {
            printf("%s\n", val->data.string);
        } else {
            print_object(val);
            printf("\n");
        }
    }

    return nil;
}

Object* primitive_equals(Object* args) {
    if (args == nil || args->type != TYPE_LIST) {
        return make_true();
    }

    Object* current = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while(rest != nil && rest->type == TYPE_LIST) {
        Object* target = rest->data.list.car;

        if(current->type == target->type && current->type == TYPE_NIL) {
            // do nothing at all
        } else if (current->type == TYPE_NUMBER && target->type == TYPE_NUMBER) {
            float num1 = current->data.number;
            float num2 = target->data.number;

            if (num1 != num2) {
                return nil;
            }
        }
        else if ((current->type == TYPE_SYMBOL) && target->type == TYPE_SYMBOL) {
            char* sym1 = current->data.symbol;
            char* sym2 = target->data.symbol;

            if (strcmp(sym1, sym2) != 0) {
                return nil;
            }
        }
        else if ((current->type == TYPE_STRING) && target->type == TYPE_STRING) {
            char* str1 = current->data.string;
            char* str2 = target->data.string;

            if (strcmp(str1, str2) != 0) {
                return nil;
            }
        } else {
            return nil;
        }

        current = target;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_less_than(Object* args) {
    if (args == nil || args->type == TYPE_NIL) {
        return make_true();
    }

    Object* current = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while(rest != nil && rest->type == TYPE_LIST) {
        Object* target = rest->data.list.car;

        if (current->type == TYPE_NUMBER && target->type == TYPE_NUMBER) {
            float num1 = current->data.number;
            float num2 = target->data.number;

            if (num1 >= num2) {
                return nil;
            }
        } else {
            return nil;
        }

        current = target;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_less_than_equal(Object* args) {
    if (args == nil || args->type == TYPE_NIL) {
        return make_true();
    }

    Object* current = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while (rest != nil && rest->type == TYPE_LIST) {
        Object* target = rest->data.list.car;

        if (current->type == TYPE_NUMBER && target->type == TYPE_NUMBER) {
            float num1 = current->data.number;
            float num2 = target->data.number;

            if (num1 > num2) {
                return nil;
            }
        } else {
            return nil;
        }

        current = rest;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_greater_than(Object* args) {
    if (args == nil || args->type == TYPE_NIL) {
        return make_true();
    }

    Object* current = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while(rest != nil && rest->type == TYPE_LIST) {
        Object* target = rest->data.list.car;

        if (current->type == TYPE_NUMBER && target->type == TYPE_NUMBER) {
            float num1 = current->data.number;
            float num2 = target->data.number;

            if (num1 <= num2) {
                return nil;
            }
        } else {
            return nil;
        }

        current = target;
        rest = rest->data.list.cdr;
    }

    return make_true();
}

Object* primitive_greater_than_equal(Object* args) {
    if (args == nil || args->type != TYPE_LIST) {
        make_true();
    }

    Object* current = args->data.list.car;
    Object* rest = args->data.list.cdr;

    while (rest != nil || rest->type == TYPE_LIST) {
        Object* target = rest->data.list.car;

        if (current->type == TYPE_NUMBER && target->type == TYPE_NUMBER) {
            float num1 = current->data.number;
            float num2 = target->data.number;

            if (num1 < num2) {
                return nil;
            }
        } else {
            return nil;
        }
    }

    return make_true();
}

Object* primitive_min(Object* args) {
    if (args == nil || args->type == TYPE_NIL) {
        return nil;
    }

    Object* first = args->data.list.car;
    
    if (first->type != TYPE_NUMBER) {
        return nil;
    }
    
    float min_val = first->data.number;
    Object* current = args->data.list.cdr;

    while (current != nil && current->type == TYPE_LIST) {
        Object* target = current->data.list.car;

        if (target->type != TYPE_NUMBER) {
            return nil;
        }

        if (target->data.number < min_val) {
            min_val = target->data.number;
        }

        current = current->data.list.cdr;
    }

    return make_number(min_val);
}

Object* primitive_max(Object* args) {
    if (args == nil || args->type == TYPE_NIL) {
        return nil;
    }

    Object* first = args->data.list.car;
    
    if (first->type != TYPE_NUMBER) {
        return nil;
    }
    
    float max_val = first->data.number;
    Object* current = args->data.list.cdr;

    while (current != nil && current->type == TYPE_LIST) {
        Object* target = current->data.list.car;

        if (target->type != TYPE_NUMBER) {
            return nil;
        }

        if (target->data.number > max_val) {
            max_val = target->data.number;
        }

        current = current->data.list.cdr;
    }

    return make_number(max_val);
}

Object* primitive_not(Object* args) {
     if (args == nil || args->type == TYPE_NIL) {
        return make_true();
    }

    Object* val = args->data.list.car;

    if (val == nil || val->type == TYPE_NIL) {
        return make_true();
    }

    return nil;
}

Object* primitive_car(Object* args) {
    Object* target = args->data.list.car;

    if (target == nil || target-> type != TYPE_LIST) {
        printf("Error: invalid car syntax.\n");
        return nil;
    }

    return target->data.list.car;
};

Object* primitive_cdr(Object* args) {
    Object* target = args->data.list.car;

    if(target == nil || target->type != TYPE_LIST) {
        printf("Error: invalid cdr syntax.\n");
        return nil;
    }

    return target->data.list.cdr;
};

Object* primitive_cons(Object* args) {
    Object* first = args->data.list.car;
    Object* second = args->data.list.cdr->data.list.car;
    return cons(first, second);
}
