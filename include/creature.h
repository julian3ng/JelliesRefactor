#ifndef CREATURE_H
#define CREATURE_H

int creature_create(creature **c);
int creature_init(creature *c, char name[80], int y, int x,
                  int hp, int atk, int def, char glyph);
void creature_update(creature *c, command parsed_input);
int creature_destroy(creature *c);

#endif /* CREATURE_H */
