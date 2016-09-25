#include "rogue.h"
#include "view.h"


int rogue_init(int seed) {
    view_create();
    return 0;
}

int rogue_exit() {
    view_destroy();
    return 0;
}



int rogue_main() {
    return 0;
}
