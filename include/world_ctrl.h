#ifndef WORLD_CTRL_H
#define WORLD_CTRL_H

int world_generate(void);
int world_set_all_actions(command player_input);
int world_move_creature(creature_t *c, map_t m);
int world_resolve_all_creatures(map_t m);
int world_cleanup(void);

#endif /* WORLD_CTRL_H */
