#include "rogue.h"
#include "globals.h"
#include "creature.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct movement {
    creature_t *c;
    int y, x, prev_y, prev_x;
    int (*execute)(struct movement *);
    int (*undo)(struct movement *);
} movement;


int movement_execute(movement_t *m) {
    if (!m) {
        log_external("movement_execute: m = NULL");
        return -1;
    }
    m->prev_y = creature_get_y(m->c);
    m->prev_x = creature_get_x(m->c);
    creature_set_pos(m->c, m->y, m->x);
    return 0;
}


int movement_undo(movement_t *m) {
    if (!m) {
        log_external("movement_undo: m = NULL");
        return -1;
    }
    creature_set_pos(m->c, m->prev_y, m->prev_x);
    return 0;
}



movement_t *movement_create(creature_t *c, int y, int x) {
    movement_t *m = (movement_t *) malloc(sizeof(movement_t));
    log_external("malloc: %p (movement)", (void *) m);
    m->c = c;
    m->y = y;
    m->x = x;
    m->prev_y = 0;
    m->prev_x = 0;
    return m;
}

movement_t *movement_create_dir(creature_t *c, command comm) {
    int next_y = creature_get_y(c), next_x = creature_get_x(c);
    
    switch (comm) {
    case MOVE_U:
        next_y--;
        break;
    case MOVE_D:
        next_y++;
        break;
    case MOVE_L:
        next_x--;
        break;
    case MOVE_R:
        next_x++;
        break;
    case MOVE_UL:
        next_y--;
        next_x--;
        break;
    case MOVE_UR:
        next_y--;
        next_x++;
        break;
    case MOVE_DL:
        next_y++;
        next_x--;
        break;
    case MOVE_DR:
        next_y++;
        next_x++;
        break;
    case STAY:
        break;
    default:
        break;
    }
    movement *m = movement_create(c, next_y, next_x);
    return m;
}
  
void movement_destroy(movement_t *m) {
    if (!m) {
        log_external("movement_destroy: m = NULL");
        return;
    }
    log_external("free: %p (movement)", (void *) m);
    free(m);
}
