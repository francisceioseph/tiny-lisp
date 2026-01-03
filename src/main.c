#include "repl.h"
#include "runner.h"
#include "setup_env.h"

int main(int argc, char** argv) {
    Environment* global_env = setup_global_env();

    if (argc > 1) {
        run_file(argv[1], global_env);
    }
    else {
        repl(global_env);
    }


    return 0;
}