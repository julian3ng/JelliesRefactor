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


typedef enum tile_type {
    NO_TILE,
    FLOOR,
    WALL,
} tile_type;

typedef enum creature_state {
    NAUGHT,
    ALIVE,
    DEAD,
} creature_state;


typedef struct creature creature_t;
typedef struct movement movement_t;


typedef struct tile tile_t;
typedef tile_t ** map_t;

typedef struct collision collision_t;

#endif /* ROGUE_H */
