#include <stdlib.h>
#include <stdio.h>
#include "rogue.h"

int entity_create(entity **e) {
    *e = (entity *) malloc(sizeof(entity));
    if (!*e) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
    return 0;
}

void entity_update(entity *e, command c) {
    switch(c) {
    case MOVE_U:
        e->y--;
        break;
    case MOVE_D:
        e->y++;
        break;
    case MOVE_L:
        e->x--;
        break;
    case MOVE_R:
        e->x++;
        break;
    case MOVE_UL:
        e->y--;
        e->x--;
        break;
    case MOVE_UR:
        e->y--;
        e->x++;
        break;
    case MOVE_DL:
        e->y++;
        e->x--;
        break;
    case MOVE_DR:
        e->y++;
        e->x++;
        break;
    case STAY:
    default:
        break;
    }
}


int entity_destroy(entity *e) {
    free(e);
    return 0;
}
