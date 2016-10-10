#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "rogue.h"
#include "view.h"
#include "creature.h"
#include "io_ctrl.h"
#include "action.h"
#include "collision_ctrl.h"
#include "world_ctrl.h"
#include "map.h"
#include "rng.h"

/*
  Initialize curses
  Create player and map
 */
int rogue_init(int seed) {
    seed_rng(seed);
    view_create();
    world_generate();    
    system("rm logfile.txt");
    return 0;
}

/*
  Destroy player and map
  Exit gracefully from curses
 */
int rogue_exit(int status) {
    creature_destroy(&player);
    for (int i=0; i<MAX_MONSTERS; i++) {
        if (creatures[i]) {
            creature_destroy(&creatures[i]);
        }
    }
    free(creatures);
    map_destroy(map);
    view_destroy();
    if (status == 1) {
        printf("YOU WIN\n");
    } else if (status == 0) {
        printf("YOU LOSE\n");
    }
    printf("Exited normally!\n");
    exit(0);
}

void cleanup(void) {
    if (creature_get_state(player) == DEAD) {
        rogue_exit(0);
    }

    static int num_dead = 0;
    for (int i=0; i<MAX_MONSTERS; i++) {
        if (creature_get_state(creatures[i]) == DEAD) {
            num_dead++;
            int cy = creature_get_y(creatures[i]);
            int cx = creature_get_x(creatures[i]);
            tile_set_creature(map_tile_at(cy, cx, map), NULL);
            creature_destroy(&creatures[i]);
        }
    }
    
    if (num_dead == MAX_MONSTERS) {
        rogue_exit(1);
    }
}


/*
  Update game state
 */
void update(command parsed_input) {

    // Given input, set action for player
    parse_command(parsed_input);

    // Save old tile
    tile_t *a = map_tile_at(creature_get_y(player), creature_get_x(player), map);
    tile_set_creature(a, NULL);
    
    // Get player's action
    movement_t *player_action = creature_get_movement(player);

    // Do player's action
    movement_execute(player_action);

    // Get player's current position
    tile_t *b = map_tile_at(creature_get_y(player), creature_get_x(player), map);

    // Check collisions at that position
    collision_t *collision_check = get_collision(player, b);

    // resolve collisions
    resolve_collision(collision_check);

    tile_t *c = map_tile_at(creature_get_y(player), creature_get_x(player), map);


    creature_resolve(player);
    for (int i=0; i<MAX_MONSTERS; i++) {
        creature_resolve(creatures[i]);
    }
    
    tile_set_creature(c, player);
    movement_destroy(player_action);

    cleanup();
}

/*
  Execute game loop:
    Read and parse player input
    Update game state
    Draw
 */
int rogue_main() {
    int input = 0;
    command parsed_input = STAY;
    while (parsed_input != QUIT) {
        update(parsed_input);
        draw();
        parsed_input = parse_input(getchar());
    }
    return 0;
}
