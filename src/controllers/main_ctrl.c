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


/*
  Update game state
 */
void update(command parsed_input) {

    world_set_all_actions(parsed_input);

    // Save old tile
    world_move_creature(player, map);
    world_resolve_creature(player, map);
    for (int i=0; i<MAX_MONSTERS; i++) {
        world_move_creature(creatures[i], map);
        world_resolve_creature(creatures[i], map);
    }
    
    int cleanup_status = world_cleanup();
    if (cleanup_status != -1) {
        rogue_exit(cleanup_status);
    }
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
