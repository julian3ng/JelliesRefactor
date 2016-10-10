#include <stdlib.h>
#include "rogue.h"
#include "globals.h"
#include "map.h"
#include "creature.h"
#include "rng.h"
#include "collision_ctrl.h"

int spawn_creature(creature_t *c, map_t m) {
    collision_t *maybe_collision = get_collision(c, map_tile_at(creature_get_y(c), creature_get_x(c), map));
    while (check_collision(maybe_collision)) {
        creature_set_pos(c, gen_rand(MAP_HEIGHT), gen_rand(MAP_WIDTH));
        maybe_collision = get_collision(c, map_tile_at(creature_get_y(c), creature_get_x(c), map));
    }

    tile_set_creature(map_tile_at(creature_get_y(c), creature_get_x(c), map) , c);
}

int world_generate(void) {
    map = map_create();
    map_init(&map);
    player = creature_create();
    creature_init(player, "Julian", MAP_HEIGHT/2, MAP_WIDTH/2, 10, 5, 0, '@');
    spawn_creature(player, map);

    creatures = (creature_t **) malloc(sizeof(creature_t *) * MAX_MONSTERS);
    for (int i=0; i<MAX_MONSTERS; i++) {
        creatures[i] = creature_create();
        creature_init(creatures[i], "", MAP_HEIGHT/2, MAP_WIDTH/2, 10, 0, 0, 'a' + i);
        spawn_creature(creatures[i], map);
    }

    

    
}
