#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rogue.h"
#include "creature.h"

creature_t *jelly;
creature_t *player;
creature_t **creatures;

map_t map;


void log_external(const char *fmt, ...) {
    va_list arg;
    char msg[80];
    va_start(arg, fmt);
    vsnprintf(msg, 80, fmt, arg);
    va_end(arg);

    char log_command[80] = "echo '";
    strncat(log_command, msg, 80);
    strncat(log_command, "' >> logfile.txt", 80);
    system(log_command);
}
    
    
