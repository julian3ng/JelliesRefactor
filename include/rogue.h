#ifndef ROGUE_H
#define ROGUE_H

#define MAP_HEIGHT 22
#define MAP_WIDTH 78
#define DEFAULT_SEED 3501
#define LSHIFT(N) (1 << (N))

// Controls

typedef enum command {
    STAY = 0,
    MOVE_U,
    MOVE_D,
    MOVE_L,
    MOVE_R,
    MOVE_UL,
    MOVE_UR,
    MOVE_DL,
    MOVE_DR,
    QUIT,
} command;

typedef struct cursor {
    int y, x;
} cursor;

typedef struct creature {
    char name[80];
    int y, x, hp, atk, def;
    char glyph;
} creature;

typedef struct item {
    int id;
} item;

typedef enum tile_type {
    FLOOR,
    WALL,
} tile_type;

typedef enum tile_flags {
    UNFLAGGED = LSHIFT(0),
    FUTURE_WALL = LSHIFT(1),
    FUTURE_FLOOR = LSHIFT(2),
} tile_flags;

typedef struct tile {
    tile_type type;
    tile_flags flags;
    char glyph;
    creature *c;
} tile;
   

#endif /* ROGUE_H */
