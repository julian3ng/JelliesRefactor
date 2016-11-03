#ifndef GLOBALS_H
#define GLOBALS_H
#include "rogue.h"

extern creature_t *jelly;
extern creature_t *player;
extern creature_t **creatures;

extern map_t map;
extern int level;

void log_external(const char *fmt, ...);
#endif /* GLOBALS_H */
