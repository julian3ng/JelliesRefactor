#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int node_create(node **n) {
    *n = (node *) malloc(sizeof(node));
    if (!(*n)) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    return 0;
}

int set_val(void *item, node *n) {
    n->value = item;
    return 0;
}

int set_next(node *new_next, node *n) {
    n->next = new_next;
    return 0;
}

int node_destroy(node *n) {
    free(n);
}
