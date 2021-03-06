#include <stdlib.h>
#include "rogue.h"
#include "globals.h"
#include "map.h"
#include "creature.h"
#include "action.h"
#include "io_ctrl.h"
#include "rng.h"
#include "collision_ctrl.h"
#include "ai_ctrl.h"


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
    level = 0;
    player = creature_create();
    creature_init(player, "Julian", 0, MAP_HEIGHT/2, MAP_WIDTH/2, 10, 5, 0, '@');
    spawn_creature(player, map);

    creatures = (creature_t **) malloc(sizeof(creature_t *) * MAX_MONSTERS);
    for (int i=0; i<MAX_MONSTERS; i++) {
        creatures[i] = creature_create();
        creature_init(creatures[i], "", creature_get_z(player), MAP_HEIGHT/2, MAP_WIDTH/2, 10, 0, 0, 'a' + i);
        spawn_creature(creatures[i], map);
    }
}


int world_cleanup(void) {
    if (creature_get_state(player) == DEAD) {
        return 0;
    }

    static int num_dead = 0;
    for (int i=0; i<MAX_MONSTERS; i++) {
        if (creature_get_state(creatures[i]) == DEAD) {
            int cy = creature_get_y(creatures[i]);
            int cx = creature_get_x(creatures[i]);
            num_dead++;
            tile_set_creature(map_tile_at(cy, cx, map), NULL);
            creature_destroy(&creatures[i]);
        }
    }
    
    if (num_dead == MAX_MONSTERS) {
        return 1;
    }

    return -1;
}


int world_set_all_actions(command player_input) {
    static int ci = 0;

    if (player_input == DEBUG) {
        /*creature_t *tmp = player;
        player = creatures[ci];
        creatures[ci] = tmp;*/
    }
    
    command_creature(player, player_input);//player_input);
    for (int i=0; i<MAX_MONSTERS; i++) {
        command_creature(creatures[i], jelly_ai());
    }
}


int world_move_creature(creature_t *c, map_t m) {
    // Save old tile
    tile_t *t1 = map_tile_at(creature_get_y(c), creature_get_x(c), m);
    tile_set_creature(t1, NULL);

    // Get creature's action and execute it
    movement_t *creature_action = creature_get_movement(c);
    movement_execute(creature_action);

    tile_t *t2 = map_tile_at(creature_get_y(c), creature_get_x(c), m);
    collision_t *collision_data = get_collision(c, t2);
    resolve_collision(collision_data);

    

    movement_destroy(creature_action);
}


int world_resolve_creature(creature_t *c, map_t m) {
    creature_resolve(c);
    if (creature_get_state(c) == ALIVE) {
        int cy = creature_get_y(c);
        int cx = creature_get_x(c);
        tile_set_creature(map_tile_at(cy, cx , map), c);
    }

}




