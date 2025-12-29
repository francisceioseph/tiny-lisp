#include "repl.h"
#include "setup_env.h"

int main() {
    Environment* global_env = setup_global_env();
    repl(global_env);

    return 0;
}