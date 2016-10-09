#include "rogue.h"
#include "globals.h"
#include <stdlib.h>



typedef enum tile_flags {
    UNFLAGGED = LSHIFT(0),
    FUTURE_WALL = LSHIFT(1),
    FUTURE_FLOOR = LSHIFT(2),
} tile_flags;

typedef struct tile {
    tile_type type;
    tile_flags flags;
    char glyph;
    creature_t *c;
} tile;


tile_type tile_get_type(tile_t *t) {
    return t->type;
}

char tile_get_glyph(tile_t *t) {
    return t->glyph;
}

creature_t *tile_get_creature(tile_t *t) {
    return t->c;
}

void tile_set_creature(tile_t *t, creature_t *c) {
    t->c = c;
}


map_t map_create() {
    tile **m = (tile **) malloc(sizeof(tile *) * MAP_HEIGHT);
    log_external("malloc: %p (tile **)", (void *) m);
    for (int i=0; i<MAP_HEIGHT; i++) {
        m[i] = (tile *) malloc(sizeof(tile) * MAP_WIDTH);
        log_external("malloc: %p (tile *)", (void *) m[i]);
    }

    return m;
}

int map_init(map_t *m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            if ((i == 0) || (i == MAP_HEIGHT-1) || (j == 0) || (j == MAP_WIDTH-1)) {
                (*m)[i][j] = (tile) {WALL, UNFLAGGED, '#', NULL};
            } else {
                (*m)[i][j] = (tile) {FLOOR, UNFLAGGED, '.', NULL};
            }
        }
    }

    return 0;
}

tile_t *map_tile_at(int y, int x, map_t m) {
    if ((y < 0) || (y >= MAP_HEIGHT) || (x < 0) || (x >= MAP_WIDTH)) {
        return NULL;
    }
    return &m[y][x];
}

int map_destroy(map_t m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        log_external("free: %p (map row)", (void *) m[i]);
        free(m[i]);
    }
    log_external("free: %p (map)", (void *) m);
    free(m);
}
