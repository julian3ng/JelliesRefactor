#include <ncurses.h>
#include "globals.h"
#include "rogue.h"
#include "map.h"
#include "creature.h"
#include "view.h"

#include <stdarg.h>

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
    log_view = newwin(LOG_VIEW_HEIGHT, LOG_VIEW_WIDTH, MAP_VIEW_HEIGHT, 0);
    return 0;
}


int draw_creature(creature_t *c, WINDOW *w) {
    if (c == player) {
        mvwaddch(w, MAP_VIEW_HEIGHT/2, MAP_VIEW_WIDTH/2, creature_get_glyph(c));
    }
    return 0;
}




int draw_tile(tile_t *t, int y, int x, WINDOW *w) {
    mvwaddch(w, y, x, tile_glyph(t));
    return 0;
}


int draw_outside_map(int y, int x, WINDOW *w) {
    mvwaddch(w, y, x, ' ');
    return 0;
}


int draw_map(map_t m, WINDOW *w) {
    int startx = creature_get_x(player) - MAP_VIEW_WIDTH/2;
    int starty = creature_get_y(player) - MAP_VIEW_HEIGHT/2;
    int endx = creature_get_x(player) + MAP_VIEW_WIDTH/2;
    int endy = creature_get_y(player) + MAP_VIEW_HEIGHT/2;
    for (int i=starty; i<endy; i++) {
        for (int j=startx; j<endx; j++) {
            if (i < 0 || i >= MAP_HEIGHT || j < 0 || j >= MAP_WIDTH) {
                draw_outside_map(i-starty, j-startx, w);
            } else {
                draw_tile(map_tile_at(i, j, m), i-starty, j-startx, w);
            }
        }
    }
    return 0;
}

void log_msg(const char *fmt, ...) {
    va_list arg;
    char msg[LOG_VIEW_WIDTH];
    va_start(arg, fmt);
    vsprintf(msg, fmt, arg);
    va_end(arg);
    mvwprintw(log_view, 1, 1, "%s", msg);
}


int draw() {
    // Clear the view in preparation for update
    wclear(map_view);
    clear();

    // update!
    draw_map(map, map_view);
    draw_creature(player, map_view);
    log_msg("%2d %2d", creature_get_x(player), creature_get_y(player));

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

