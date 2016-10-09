#include "rogue.h"
#include "globals.h"
#include "rng.h"
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

// MAP GENERATION FUNCTIONS
void gen_blank(map_t m);
void gen_cell_auto(map_t m);

tile_type tile_get_type(tile_t *t) {
    if (!t) {
        log_external("tile_get_type: t = NULL");
        return NO_TILE;
    }
    return t->type;
}

char tile_get_glyph(tile_t *t) {
    if (!t) {
        log_external("tile_get_type: t = NULL");
        return '0';
    }
    return t->glyph;
}

creature_t *tile_get_creature(tile_t *t) {
    if (!t) {
        log_external("tile_get_type: t = NULL");
        return NULL;
    }
    return t->c;
}

void tile_set_creature(tile_t *t, creature_t *c) {
    if (!t) {
        log_external("tile_set_creature: t = NULL");
        return;
    }
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
    if (!m) {
        log_external("map_init: m = NULL");
        return -1;
    }
    //gen_blank(*m);
    gen_cell_auto(*m);
    return 0;
}

tile_t *map_tile_at(int y, int x, map_t m) {
    if (!m) {
        log_external("map_tile_at: m = NULL");
        return NULL;
    }
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

/* MAP GENERATION */

int num_neighbor_walls(int y, int x, map_t m) {
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if ((m)[(i + MAP_HEIGHT) % MAP_HEIGHT][(j + MAP_WIDTH) % MAP_WIDTH].type == WALL) {
                count++;
            }
        }
    }
    return count;
}


void gen_blank(map_t m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            if ((i == 0) || (i == MAP_HEIGHT-1) || (j == 0) || (j == MAP_WIDTH-1)) {
                (m)[i][j] = (tile) {WALL, UNFLAGGED, '#', NULL};
            } else {
                (m)[i][j] = (tile) {FLOOR, UNFLAGGED, '.', NULL};
            }
        }
    }
}


void gen_cell_auto(map_t m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            if ((gen_rand() % 100) <= 45) {
                (m)[i][j] = (tile) {WALL, UNFLAGGED, '#', NULL};
            } else {
                (m)[i][j] = (tile) {FLOOR, UNFLAGGED, '.', NULL};
            }
        }
    }

    for (int iters = 0; iters < 2; iters++) {
        for (int i=0; i<MAP_HEIGHT; i++) {
            for (int j=0; j<MAP_WIDTH; j++) {
                if (num_neighbor_walls(i, j, m) >= 5) {
                    (m)[i][j] = (tile) {(m)[i][j].type, FUTURE_WALL, (m)[i][j].glyph, NULL};
                } else {
                    (m)[i][j] = (tile) {(m)[i][j].type, FUTURE_FLOOR, (m)[i][j].glyph, NULL};             
                
                }
            }
        }

        for (int i=0; i<MAP_HEIGHT; i++) {
            for (int j=0; j<MAP_WIDTH; j++) {
                if ((m)[i][j].flags == FUTURE_WALL) {
                    (m)[i][j] = (tile) {WALL, UNFLAGGED, '#', NULL};
                } else if ((m)[i][j].flags == FUTURE_FLOOR) {
                    (m)[i][j] = (tile) {FLOOR, UNFLAGGED, '.', NULL};
                }
            }
        }
    }
}
