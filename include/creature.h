#ifndef CREATURE_H
#define CREATURE_H

creature_t *creature_create(void);
int creature_init(creature_t *c, char name[80], int y, int x,
                  int hp, int atk, int def, char glyph);
int creature_get_x(creature_t *c);
int creature_get_y(creature_t *c);
movement_t *creature_get_movement(creature_t *c);
void creature_set_pos(creature_t *c, int y, int x);
void creature_set_movement(creature_t *c, movement_t *m);
char creature_get_glyph(creature_t *c);
int creature_destroy(creature_t *c);

#endif /* CREATURE_H */
