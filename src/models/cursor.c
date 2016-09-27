#include <stdlib.h>
#include <stdio.h>
#include "rogue.h"
#include "globals.h"

int cursor_create(cursor **cu) {
    *cu = (cursor *) malloc(sizeof(cursor));
    if (!*cu) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
    return 0;
}

void cursor_update(cursor *cu, command c) {
    if (player) {
        cu->y = player->y;
        cu->x = player->x;
    } else {
        switch(c) {
        case MOVE_U:
            cu->y--;
            break;
        case MOVE_D:
            cu->y++;
            break;
        case MOVE_L:
            cu->x--;
            break;
        case MOVE_R:
            cu->x++;
            break;
        case MOVE_UL:
            cu->y--;
            cu->x--;
            break;
        case MOVE_UR:
            cu->y--;
            cu->x++;
            break;
        case MOVE_DL:
            cu->y++;
            cu->x--;
            break;
        case MOVE_DR:
            cu->y++;
            cu->x++;
            break;
        case STAY:
        default:
            break;
        }
    }
}


int cursor_destroy(cursor *c) {
    free(c);
    return 0;
}
