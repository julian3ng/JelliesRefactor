#include <ncurses.h>


int view_create() {
    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);
}

int view_destroy() {
    refresh();
    getch();
    endwin();
}
