#include <time.h>
#include <stdlib.h>

void seed_rng(unsigned int seed) {
    srand(seed);
}

int gen_rand(int range) {
    if (range) {
        return rand() % range;
    } else {
        return rand();
    }
}
