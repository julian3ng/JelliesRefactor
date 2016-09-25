#ifndef ROGUE_H
#define ROGUE_H

#define DEFAULT_SEED 3501


typedef enum entity_type {
    NONE = 0,
    CREATURE,
    ITEM,
} entity_type;

typedef struct creature_data {
    char name[80];
    int hp, atk, def;
    char glyph;
} creature_data;

typedef struct item_data {
    int id;
    char glyph;
} item_data;

typedef union entity_data {
    creature_data cr;
    item_data     it;
} entity_data;

typedef struct entity {
    int y, x;
    entity_type t;
    entity_data data;
} entity;
   

#endif /* ROGUE_H */
