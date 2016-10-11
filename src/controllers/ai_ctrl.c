#include "rogue.h"
#include "rng.h"

command jelly_ai(void) {
    return (command) gen_rand(MAX_COMMANDS);
}
