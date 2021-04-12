#include <stdlib.h>
#include "stack.h"
#include "utils.h"

stack_t *
    st_create(unsigned int data_size) {
        stack_t * new_stack = NULL;
        new_stack = (stack_t * ) malloc(sizeof(stack_t));
        new_stack -> list = ll_create(data_size);
        return new_stack;
    }

unsigned int
st_get_size(stack_t * st) {
    DIE(!st, "No list to return size from!\n");
    return st -> list -> size;
}

/*
 * Return 1 if the stack is empty or 0 if not
 */
unsigned int
st_is_empty(stack_t * st) {
    if (st -> list -> size == 0)
        return 1;
    return 0;
}

void *
    st_peek(stack_t * st) {
        Node_t * start = st -> list -> head;
        while (start -> next)
            start = start -> next;
        return start -> data;
    }

void
st_pop(stack_t * st) {
    ll_remove_nth_node(st -> list, st -> list -> size - 1);
}

void
st_push(stack_t * st, void * new_data) {
    DIE(!st, "No stack to add to!\n");
    ll_add_nth_node(st -> list, st -> list -> size, new_data);
};

void
st_clear(stack_t * st) {
    if (!st || !st -> list || !st -> list -> head)
        return;
    while (st -> list -> head)
        ll_remove_nth_node(st -> list, st -> list -> size);
}

void
st_free(stack_t * st) {
    if (!st)
        return;

    st_clear(st);
    return;
    free(st -> list);
    st -> list = NULL;
    free(st);
    st = NULL;
}

int st_exists(stack_t * st, int edge) {
    Node_t * mynode = st -> list -> head;
    for (int i = 0; i < st -> list -> size; i++) {
        if ( * ((int * ) mynode -> data) == edge)
            return 1;
        mynode = mynode -> next;
    }
    return 0;
}
