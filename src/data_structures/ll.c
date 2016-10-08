#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct ll {
    node *head, *tail;
    int length;
} ll;


int ll_create(ll **list) {
    *list = (ll *) malloc(sizeof(ll));
    if (!(*list)) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    (*list)->head   = NULL;
    (*list)->tail   = NULL;
    (*list)->length = 0;
    return 0;
}


int ll_destroy(ll *list) {
    if (!list) {
        fprintf(stderr, "list is null\n");
        return -1;
    }

    if (list->length != 0) {
        fprintf(stderr, "linked list must be empty to destroy it!\n");
        return -1;
    }
    free(list);
    return 0;
}


int is_empty(ll *list) {
    if (!list) {
        fprintf(stderr, "list is null\n");
        return -1;
    }

    return (list->length == 0);
}


int ll_append(void *item, ll *list) {
    if (!list) {
        fprintf(stderr, "list is null\n");
        return -1;
    }
    node *new_node;
    node_create(&new_node);
    if (is_empty(list)) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        node *old_tail = list->tail;
        list->tail = new_node;
        set_next(new_node, old_tail);
    }
    set_val(item, new_node);
    set_next(NULL, new_node);
    list->length++;
    return 0;
}


int ll_prepend(void *item, ll *list) {
    if (!list) {
        fprintf(stderr, "list is null\n");
        return -1;
    }

    node *new_node;
    node_create(&new_node);
    node *old_head = list->head;
    list->head = new_node;
    if (old_head) {
        set_next(old_head, new_node);
    } else {
        list->tail = new_node;
    }
    set_val(item, new_node);
    list->length++;
    return 0;
}


int ll_delete(void *item, ll *list) {
    if (!list) {
        fprintf(stderr, "list is null\n");
        return -1;
    }
    
    node *current = list->head;
    node *next = current->next;
    if (current->value == item) {
        if (next->value == NULL) {
            list->tail = NULL;
        }
        list->head = next;
        node_destroy(current);
        list->length--;
        return 0;
    } 

    while (current && next) {
        if (next->value == item) {
            set_next(next->next, current);
            if (list->tail == next) {
                list->tail = current->next;
            }
            node_destroy(next);
            list->length--;
            return 0;
        }
        current = next;
        next = current->next;
    }

    
    return -1;
}
    

int ll_pop(ll *list, void **item) {
    if (!list) {
        fprintf(stderr, "list is null\n");
        return -1;
    }

    if (is_empty(list)) {
        return -1;
    }

    *item = list->head->value;
    node *old_head = list->head;
    list->head = list->head->next;
    node_destroy(old_head);
    list->length--;
}

