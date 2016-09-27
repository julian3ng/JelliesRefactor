#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "rogue.h"
#include "view.h"
#include "creature.h"
#include "cursor.h"
#include "io_ctrl.h"
#include "map.h"

/*
  Initialize curses
  Create player and map
 */
int rogue_init(int seed) {
    view_create();
    cursor_create(&main_cursor);
    creature_create(&player);
    creature_init(player, "Julian", MAP_HEIGHT/2, MAP_WIDTH/2, 10, 0, 0, '@');
    map_create(&map);

    return 0;
}

/*
  Destroy player and map
  Exit gracefully from curses
 */
int rogue_exit() {
    cursor_destroy(main_cursor);
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
    creature_update(player, parsed_input);
    cursor_update(main_cursor, parsed_input);
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
