#ifndef CURSOR_H
#define CURSOR_H

int cursor_create(cursor **e);
void cursor_update(cursor *e, command c);
int cursor_destroy(cursor *e);

#endif /* CURSOR_H */
