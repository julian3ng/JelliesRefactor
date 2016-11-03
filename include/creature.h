#ifndef CREATURE_H
#define CREATURE_H

creature_t *creature_create(void);
int creature_init(creature_t *c, char name[80], int z, int y, int x,
                  int hp, int atk, int def, char glyph);
int creature_get_x(creature_t *c);
int creature_get_y(creature_t *c);
int creature_get_z(creature_t *c);
void creature_set_z(creature_t *c, int z);
void creature_set_pos(creature_t *c, int y, int x);
int creature_get_hp(creature_t *c);
void creature_set_hp(creature_t *c, int hp);
int creature_get_atk(creature_t *c);
void creature_set_atk(creature_t *c, int atk);
int creature_get_def(creature_t *c);
void creature_set_def(creature_t *c, int def);
void creature_set_movement(creature_t *c, movement_t *m);
movement_t *creature_get_movement(creature_t *c);
char creature_get_glyph(creature_t *c);
creature_state creature_get_state(creature_t *c);
void creature_resolve(creature_t *c);
int creature_destroy(creature_t **c);

#endif /* CREATURE_H */
