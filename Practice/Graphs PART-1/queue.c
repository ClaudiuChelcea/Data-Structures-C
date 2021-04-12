#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "utils.h"

queue_t * q_create(unsigned int data_size, unsigned int max_size) {
        queue_t * new_queue = NULL;
        new_queue = (queue_t * ) malloc(sizeof(queue_t));
        DIE(!new_queue, "Couldn't create queue!\n");
        new_queue -> max_size = max_size;
        new_queue -> size = 0;
        new_queue -> data_size = data_size;
        new_queue -> read_idx = 0;
        new_queue -> write_idx = 0;
        // Allocate buffer's head
        new_queue -> buff = malloc(sizeof(List_t * ));
        *(new_queue -> buff) = malloc(sizeof(List_t));
        ((List_t * ) * (new_queue -> buff)) -> head = NULL;
        ((List_t * ) * (new_queue -> buff)) -> data_size = data_size;
        ((List_t * ) * (new_queue -> buff)) -> size = 0;

        return new_queue;
    }

unsigned int
q_get_size(queue_t * q) {
    return q -> size;
}

/*
 *Return 1 if the list is empty or 0 if not
 */
unsigned int
q_is_empty(queue_t * q) {
    if (q -> size == 0)
        return 1;
    return 0;
}

void * q_front(queue_t * q) {
        return ((List_t * )(q -> buff)[q -> write_idx]) -> head -> data;
    }

/* Dequeue an element */
bool q_dequeue(queue_t * q) {
    if (!q || q -> size == 0)
        return false;
    ll_remove_nth_node_q(((List_t * ) * (q -> buff)), 0);
    --q -> size;
    return true;
}

/* Enqueue an element */
bool q_enqueue(queue_t * q, void * new_data) {
    if (!q || !new_data)
        return false;
    if (q -> max_size == q -> size)
        return false;

    ll_add_nth_node(((List_t * ) * (q -> buff)), q -> read_idx++, new_data);
    q -> size++;

    return true;
}

void q_clear(queue_t * q) {
    while (!q_is_empty(q)) {
        q_dequeue(q);
    }
}

void q_free(queue_t * q) {
    q_clear(q);
    free( * (q -> buff));
    free(q -> buff);
    free(q);
    q = NULL;
}
