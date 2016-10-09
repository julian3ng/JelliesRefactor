#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "rogue.h"
#include "view.h"
#include "creature.h"
#include "io_ctrl.h"
#include "action.h"
#include "collision_ctrl.h"
#include "map.h"
#include "rng.h"

/*
  Initialize curses
  Create player and map
 */
int rogue_init(int seed) {
    seed_rng(seed);
    view_create();
    map = map_create();
    map_init(&map);
    
    system("rm logfile.txt");
    
    player = creature_create();
    creature_init(player, "Julian", MAP_HEIGHT/2, MAP_WIDTH/2, 10, 0, 0, '@');
    /* TEST CODE */
    jelly = creature_create();
    creature_init(jelly, "Jelly", creature_get_y(player) - 2,
                  creature_get_x(player), 10, 4, 0, 'J');

    /* END TEST CODE */


    return 0;
}

/*
  Destroy player and map
  Exit gracefully from curses
 */
int rogue_exit() {
    creature_destroy(&player);
    map_destroy(map);
    view_destroy();
    printf("Exited normally!\n");
    exit(0);
}

void cleanup(void) {
    if (creature_get_state(player) == DEAD) {
        rogue_exit();
    }

    if (creature_get_state(jelly) == DEAD) {
        tile_set_creature(map_tile_at(creature_get_y(jelly), creature_get_x(jelly),
                                      map), NULL);
        creature_destroy(&jelly);
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

    tile_t *j = map_tile_at(creature_get_y(jelly), creature_get_x(jelly), map);

    creature_resolve(player);
    creature_resolve(jelly);
    
    tile_set_creature(c, player);
    movement_destroy(player_action);

    if (creature_get_state(jelly) == ALIVE) {
        log_external("still alive: %d", creature_get_hp(jelly));
        tile_set_creature(j, jelly);
    }

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
