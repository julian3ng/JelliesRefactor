#include <ncurses.h>
#include "globals.h"
#include "rogue.h"
#include "view.h"

WINDOW *map_view;

int view_create() {
    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);
    map_view = newwin(MAP_VIEW_HEIGHT, MAP_VIEW_WIDTH, 0, 0);
    return 0;
}

int draw_creature(creature *c, WINDOW *w) {
    mvwaddch(w, c->y, c->x, c->glyph);
    return 0;
}


int draw_tile(tile *t, int y, int x, WINDOW *w) {
    mvwaddch(w, y, x, t->glyph);
    return 0;
}
    

int draw_map(tile **m, WINDOW *w) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            draw_tile(&m[i][j], i+1, j+1, w);
        }
    }
    return 0;
}

int draw() {
    // Clear the view in preparation for update
    wclear(map_view);
    clear();

    // update!
    draw_map(map, map_view);
    draw_creature(player, map_view);

    box(map_view, 0, 0);
    // actually draw
    wnoutrefresh(stdscr);
    wnoutrefresh(map_view);
    doupdate();

    return 0;
}

int view_destroy() {
    refresh();
    endwin();
    return 0;
}
