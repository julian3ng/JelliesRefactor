#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rogue.h"
#include "globals.h"
#include "action.h"

typedef struct creature {
    char name[80];
    movement_t *m;
    int y, x, hp, atk, def;
    char glyph;
    creature_state state;
} creature;

creature_t *creature_create(void) {
    creature *c = (creature *) malloc(sizeof(creature));
    log_external("malloc: %p (creature)", (void *) c);
    if (!c) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
    return c;
}

/*
  Set a creature's fields
*/
int creature_init(creature_t *c, char name[80], int y, int x,
                  int hp, int atk, int def, char glyph) {
    strlcpy(c->name, name, sizeof(c->name));
    if (!c) {
        log_external("creature_init: c = NULL");
        return -1;
    }
    
    c->y     = y;
    c->x     = x;
    c->hp    = hp;
    c->atk   = atk;
    c->def   = def;
    c->glyph = glyph;
    c->state = ALIVE;
    return 0;
}

creature_state creature_get_state(creature_t *c) {
    if (!c) {
        log_external("creature_get_state: c = NULL");
        return NAUGHT;
    }
    return c->state;
}

int creature_get_y(creature_t *c) {
    if (!c) {
        log_external("creature_get_y: c = NULL");
        return -1;
    }
    return c->y;
}

int creature_get_x(creature_t *c) {
    if (!c) {
        log_external("creature_get_x: c = NULL");
        return -1;
    }
    return c->x;
}

int creature_get_hp(creature_t *c) {
    if (!c) {
        log_external("creature_get_hp: c = NULL");
        return -1;
    }    
    return c->hp;
}

void creature_set_hp(creature_t *c, int hp) {
    if (!c) {
        log_external("creature_set_hp: c = NULL");
        return;
    }
    c->hp = hp;
}

int creature_get_atk(creature_t *c) {
    if (!c) {
        log_external("creature_get_atk: c = NULL");
        return -1;
    }    
    return c->atk;
}

void creature_set_atk(creature_t *c, int atk) {
    if (!c) {
        log_external("creature_set_atk: c = NULL");
        return;
    }    
    c->atk = atk;
}

int creature_get_def(creature_t *c) {
    if (!c) {
        log_external("creature_get_def: c = NULL");
        return -1;
    }        
    return c->def;
}

void creature_set_def(creature_t *c, int def) {
    if (!c) {
        log_external("creature_set_def: c = NULL");
        return;
    }        
    c->def = def;
}

void creature_set_pos(creature_t *c, int y, int x) {
    if (!c) {
        log_external("creature_set_pos: c = NULL");
        return;
    }        
    c->y = y;
    c->x = x;
}


void creature_set_movement(creature_t *c, movement_t *m) {
    if (!c) {
        log_external("creature_set_movement: c = NULL");
        return;
    }        
    c->m = m;
}

movement_t *creature_get_movement(creature_t *c) {
    if (!c) {
        log_external("creature_get_movement: c = NULL");
        return NULL;
    }            
    return c->m;
}


char creature_get_glyph(creature_t *c) {
    if (!c) {
        log_external("creature_get_glyph: c = NULL");
        return '0';
    }            
    return c->glyph;
}

/*
  Free a creature's memory 
 */
int creature_destroy(creature_t **c) {
    if (!*c) {
        log_external("creature_destroy: c = NULL");
        return -1;
    }            
    log_external("free: %p (creature)", (void *) *c);
    free(*c);
    *c = NULL;
    return 0;
}

void creature_resolve(creature_t *c) {
    if (!c) {
        log_external("creature_resovle: c = NULL");
        return;
    }            
    if (c->hp <= 0) {
        c->state = DEAD;
    }
}

