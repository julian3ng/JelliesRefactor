#ifndef ACTION_H
#define ACTION_H

int movement_execute(movement_t *m);
int movement_undo(movement_t *m);
movement_t *movement_create(creature_t *c, int y, int x);
movement_t *movement_create_dir(creature_t *c, command comm);
void movement_destroy(movement_t *m);
    

#endif /* ACTION_H */
