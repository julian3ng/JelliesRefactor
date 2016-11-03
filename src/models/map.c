#include "rogue.h"
#include "globals.h"
#include "rng.h"
#include <stdlib.h>

typedef enum tile_flags {
    UNFLAGGED = LSHIFT(0),
    FUTURE_WALL = LSHIFT(1),
    FUTURE_FLOOR = LSHIFT(2),
    VISITED = LSHIFT(3),
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
void gen_random_walk(map_t m);
void gen_border(map_t m);
void gen_down_stair(map_t m);

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
    gen_random_walk(*m);
    gen_cell_auto(*m);
    gen_border(*m);
    gen_down_stair(*m);
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

void fill_wall_percent(map_t m, int wall_percentage) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            if (gen_rand(100) <= wall_percentage) {
                m[i][j] = (tile) {WALL, UNFLAGGED, '#', NULL};
            } else {
                m[i][j] = (tile) {FLOOR, UNFLAGGED, '.', NULL};
            }
        }
    }
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

void gen_border(map_t m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            if ((i == 0) || (i == MAP_HEIGHT-1) || (j == 0) || (j == MAP_WIDTH-1)) {
                (m)[i][j] = (tile) {WALL, UNFLAGGED, '#', NULL};
            } 
        }
    }
}

void gen_cell_auto(map_t m) {
    // Fill map randomly with 
    fill_wall_percent(m, 45);

    // Automata step
    for (int iters = 0; iters < 2; iters++) {
        // Mark everything with 5+ walls to become a wall, otherwise a floor
        for (int i=0; i<MAP_HEIGHT; i++) {
            for (int j=0; j<MAP_WIDTH; j++) {
                if (num_neighbor_walls(i, j, m) >= 5) {
                    (m)[i][j] = (tile) {(m)[i][j].type, FUTURE_WALL, (m)[i][j].glyph, NULL};
                } else {
                    (m)[i][j] = (tile) {(m)[i][j].type, FUTURE_FLOOR, (m)[i][j].glyph, NULL};             
                }
            }
        }

        // Change all marked tiles to their flagged value
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


void gen_random_walk(map_t m) {
    fill_wall_percent(m, 100);
    int y = gen_rand(MAP_HEIGHT);
    int x = gen_rand(MAP_WIDTH);
    (m)[y][x] = (tile) {FLOOR, VISITED, '.', NULL};
    for (int i=0; i<3000; i++) {
        int dy = gen_rand(3) - 1;
        int dx = 0;
        if (dy == 0) {
            if (gen_rand(2) > 0) {
                dx++;
            } else {
                dx--;
            }
        }
        y = (y + dy + MAP_HEIGHT) % MAP_HEIGHT;
        x = (x + dx + MAP_WIDTH) % MAP_WIDTH;
        if (map_tile_at(y, x, m)->flags != VISITED) {
            (m)[y][x] = (tile) {FLOOR, VISITED, '.', NULL};
        } 
    }
}

void gen_down_stair(map_t m) {
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            if (((m)[i][j].type == FLOOR) && (gen_rand(1000) < 3)) {
                (m)[i][j] = (tile) {DOWN_STAIR, UNFLAGGED, '>', NULL};
            }
        }
    }
}
