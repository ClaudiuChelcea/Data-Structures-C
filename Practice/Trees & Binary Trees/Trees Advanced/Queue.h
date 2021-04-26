#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdbool.h>

typedef struct queue_t queue_t;
struct queue_t {
    /* Max queue size */
    unsigned int max_size;
    /* Queue size */
    unsigned int size;
    /* Size of element */
    unsigned int data_size;
    /* Front and dequeue index */
    unsigned int read_idx;
    /* Enqueue index */
    unsigned int write_idx;
    /* Items */
    void ** buff;
};

queue_t * q_create(unsigned int data_size, unsigned int max_size);

unsigned int q_get_size(queue_t * q);

unsigned int q_is_empty(queue_t * q);

void * q_front(queue_t * q);

bool q_dequeue(queue_t * q);

bool q_enqueue(queue_t * q, void * new_data);

void q_clear(queue_t * q);

void q_free(queue_t * q);

#endif /* QUEUE_H_ */