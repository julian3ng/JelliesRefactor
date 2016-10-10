#include "rogue.h"
#include "globals.h"
#include "creature.h"
#include "action.h"
#include "map.h"
#include "combat_ctrl.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum collision_type {
    CREATURE_WALL,
    CREATURE_CREATURE
} collision_type;

typedef struct collision {
    collision_type *coll_type;
    creature_t *c;
    tile_t *t;
} collision;

/* Check if there's a collision */
collision_t *get_collision(creature_t *c, tile_t *t) {
    collision *coll = (collision *) malloc(sizeof(collision));
    log_external("malloc: %p (collision)", (void *) coll);
    coll->c = c;
    coll->t = t;
    return coll;
}

/* Resolve a collision */
int resolve_collision(collision_t *coll) {
    if (!coll->t) {
        movement_undo(creature_get_movement(coll->c));
        log_external("free: %p (collision)", (void *) coll);
        free(coll);
        return 0;
    }
    
    creature_t *tile_creature = tile_get_creature(coll->t);
    if (tile_creature) {
        fight(coll->c, tile_creature);
        movement_undo(creature_get_movement(coll->c));
    }

    if (tile_get_type(coll->t) == WALL) {
        movement_undo(creature_get_movement(coll->c));
    }

    log_external("free: %p (collision)", (void *) coll);
    free(coll);
    return 0;
}

int check_collision(collision_t *coll) {
    if (!coll->t) {
        free(coll);
        return 0;
    }
    creature_t *tile_creature = tile_get_creature(coll->t);
    if (tile_creature) {
        free(coll);
        return 1;
    }

    if (tile_get_type(coll->t) == WALL) {
        free(coll);
        return 1;
    }
    free(coll);
    return 0;
}

int destroy_collision(collision_t *coll) {
    if (!coll) {
        log_external("destroy_collision: coll = NULL");
        return -1;
    }
    free(coll);
}

