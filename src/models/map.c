#include "rogue.h"
#include <stdlib.h>

int map_create(tile ***m) {
    *m = (tile **) malloc(sizeof(tile *) * MAP_HEIGHT);

    for (int i=0; i<MAP_HEIGHT; i++) {
        (*m)[i] = (tile *) malloc(sizeof(tile) * MAP_WIDTH);
    }

    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            (*m)[i][j] = (tile) {FLOOR, UNFLAGGED, '.', NULL};
        }
    }
    return 0;
}

int map_init(tile ***m) {
}

int map_destroy(tile **m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        free(m[i]);
    }
    free(m);
}
