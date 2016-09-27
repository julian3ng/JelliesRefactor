#ifndef ENTITY_H
#define ENTITY_H

int entity_create(entity **e);
void entity_update(entity *e, command c);
int entity_destroy(entity *e);

#endif /* ENTITY_H */
