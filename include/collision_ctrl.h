#ifndef COLLISION_H
#define COLLISION_H

collision_t *get_collision(creature_t *c, tile_t *t);
int resolve_collision(collision_t *coll);

#endif /* COLLISION_H */
