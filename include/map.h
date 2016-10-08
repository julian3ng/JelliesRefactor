#ifndef MAP_H
#define MAP_H

char tile_glyph(tile_t *t);
tile_type tile_get_type(tile_t *t);
tile_t *map_tile_at(int y, int x, map_t m);
map_t map_create(void);
int map_destroy(map_t m);
int map_init(map_t *m);


#endif /* MAP_H */
