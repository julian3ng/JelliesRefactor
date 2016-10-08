#ifndef NODE_H
#define NODE_H


typedef struct node {
    void *value;
    struct node *next;
} node;

int node_create(node **n);
int set_val(void *item, node *n);
int set_next(node *new_next, node *n);
int node_destroy(node *n);


#endif /* NODE_H */
