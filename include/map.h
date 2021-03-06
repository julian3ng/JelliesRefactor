#ifndef MAP_H
#define MAP_H

char tile_get_glyph(tile_t *t);
tile_type tile_get_type(tile_t *t);
creature_t *tile_get_creature(tile_t *t);
void tile_set_creature(tile_t *t, creature_t *c);
tile_t *map_tile_at(int y, int x, map_t m);
void map_update(map_t m);
map_t map_create(void);
int map_destroy(map_t m);
int map_init(map_t *m);


#endif /* MAP_H */
