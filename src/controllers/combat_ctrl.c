#include "rogue.h"
#include "creature.h"
#include <stdio.h>

void fight(creature_t *attacker, creature_t *defender) {
    if (!attacker) {
        fprintf(stderr, "NO ATTACKER\n");
        return;
    }
    if (!defender) {
        fprintf(stderr, "NO DEFENDER\n");
        return;
    }

    creature_set_hp(defender, creature_get_hp(defender) - creature_get_atk(attacker));
    if (creature_get_hp(defender) <= 0) {
        return;
    }
    
    creature_set_hp(attacker, creature_get_hp(attacker) - creature_get_atk(defender));
}
