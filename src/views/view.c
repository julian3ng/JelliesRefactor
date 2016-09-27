#include <ncurses.h>
#include "globals.h"
#include "rogue.h"
#include "view.h"

#define WINDOW_BOUNDARY 1

WINDOW *map_view;
WINDOW *log_view;

int view_create() {
    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);
    map_view = newwin(MAP_VIEW_HEIGHT, MAP_VIEW_WIDTH, 0, 0);
    log_view = newwin(MAP_VIEW_HEIGHT, MAP_VIEW_WIDTH, MAP_VIEW_HEIGHT, 0);
    return 0;
}

int draw_creature(creature *c, WINDOW *w) {
    if (c == player) {
        mvwaddch(w, MAP_VIEW_HEIGHT/2, MAP_VIEW_WIDTH/2, c->glyph);
    }
    //mvwaddch(w, c->y, c->x, c->glyph);
    return 0;
}

int draw_cursor(cursor *c, WINDOW *w) {
    mvwaddch(w, c->y + WINDOW_BOUNDARY, c->x + WINDOW_BOUNDARY, 'x');
    return 0;
}

int draw_tile(tile *t, int y, int x, WINDOW *w) {
    mvwaddch(w, y, x, t->glyph);
    return 0;
}

int draw_outside_map(int y, int x, WINDOW *w) {
    mvwaddch(w, y, x, ' ');
    return 0;
}

int draw_map(tile **m, WINDOW *w) {
    int startx = player->x - MAP_VIEW_WIDTH/2;
    int starty = player->y - MAP_VIEW_HEIGHT/2;
    int endx = player->x + MAP_VIEW_WIDTH/2;
    int endy = player->y + MAP_VIEW_HEIGHT/2;
    for (int i=starty; i<endy; i++) {
        for (int j=startx; j<endx; j++) {
            if (i < 0 || i >= MAP_HEIGHT || j < 0 || j >= MAP_WIDTH) {
                draw_outside_map(i-starty, j-startx, w);
            } else {
                draw_tile(&m[i][j], i-starty, j-startx, w);
            }
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
    draw_cursor(main_cursor, map_view);

    box(map_view, 0, 0);
    box(log_view, 0, 0);
    // actually draw
    wnoutrefresh(stdscr);
    wnoutrefresh(map_view);
    wnoutrefresh(log_view);
    doupdate();

    return 0;
}

int view_destroy() {
    refresh();
    endwin();
    return 0;
}
