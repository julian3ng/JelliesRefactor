#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rogue.h"


typedef struct creature {
    char name[80];
    int y, x, hp, atk, def;
    char glyph;
} creature;


/*
  Create a creature (make an entity and set it to be a creature)
*/
creature_t *creature_create(void) {
    creature *c = (creature *) malloc(sizeof(creature));
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
    strlcpy(c->name, name, 80);
    c->y     = y;
    c->x     = x;
    c->hp    = hp;
    c->atk   = atk;
    c->def   = def;
    c->glyph = glyph;
}

int creature_get_y(creature_t *c) {
    return c->y;
}

int creature_get_x(creature_t *c) {
    return c->x;
}

void creature_set_pos(creature_t *c, int y, int x) {
    c->y = y;
    c->x = x;
}

void creature_update(creature *cr, command c) {
    switch(c) {
    case MOVE_U:
    case MOVE_D:
    case MOVE_L:
    case MOVE_R:
    case MOVE_UL:
    case MOVE_UR:
    case MOVE_DL:
    case MOVE_DR:
    case STAY:
    default:
        break;
    }
}

char creature_get_glyph(creature_t *c) {
    return c->glyph;
}

/*
  Free a creature's memory 
 */
int creature_destroy(creature_t *c) {
    free(c);
    return 0;
}

