#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "rogue.h"
#include "view.h"
#include "creature.h"
#include "io_ctrl.h"
#include "action.h"
#include "map.h"

/*
  Initialize curses
  Create player and map
 */
int rogue_init(int seed) {
    view_create();
    player = creature_create();
    creature_init(player, "Julian", MAP_HEIGHT/2, MAP_WIDTH/2, 10, 0, 0, '@');
    map = map_create();
    map_init(&map);
    return 0;
}

/*
  Destroy player and map
  Exit gracefully from curses
 */
int rogue_exit() {
    creature_destroy(player);
    map_destroy(map);
    view_destroy();
    printf("Exited normally!\n");
    return 0;
}

/*
  Update game state
 */
void update(command parsed_input) {
    parse_command(parsed_input);
    movement_t *player_action = creature_get_movement(player);
    movement_execute(player_action);
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
