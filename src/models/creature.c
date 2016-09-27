#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rogue.h"


/*
  Create a creature (make an entity and set it to be a creature)
*/
int creature_create(creature **c) {
    *c = (creature *) malloc(sizeof(creature));
    if (!*c) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
    return 0;
}

/*
  Set a creature's fields
*/
int creature_init(creature *c, char name[80], int y, int x,
                  int hp, int atk, int def, char glyph) {
    strlcpy(c->name, name, 80);
    c->y     = y;
    c->x     = x;
    c->hp    = hp;
    c->atk   = atk;
    c->def   = def;
    c->glyph = glyph;
}

/*
  Update a creature's state
*/
void creature_update(creature *cr, command c) {
    switch(c) {
    case MOVE_U:
        cr->y--;
        break;
    case MOVE_D:
        cr->y++;
        break;
    case MOVE_L:
        cr->x--;
        break;
    case MOVE_R:
        cr->x++;
        break;
    case MOVE_UL:
        cr->y--;
        cr->x--;
        break;
    case MOVE_UR:
        cr->y--;
        cr->x++;
        break;
    case MOVE_DL:
        cr->y++;
        cr->x--;
        break;
    case MOVE_DR:
        cr->y++;
        cr->x++;
        break;
    case STAY:
    default:
        break;
    }
}

/*
  Free a creature's memory 
 */
int creature_destroy(creature *c) {
    free(c);
    return 0;
}
