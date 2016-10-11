#include <stdlib.h>
#include "rogue.h"
#include "main_ctrl.h"


int main(int argc, char **argv) {
    int seed = DEFAULT_SEED;
    if (argc > 1) {
        seed = atoi(argv[1]);
    }

    rogue_init(seed);
    rogue_main();
    rogue_exit(-1);
        
}
