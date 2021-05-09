#include <stdio.h>
#include <stdlib.h>

typedef enum bool
{
    FALSE = 0,
    TRUE = 1
}
bool;

// Store queue values in nodes
typedef struct Queue_Node
{
    struct Queue_Node * next;
    int value;
}
queue_node_t;

// Queue list
typedef struct Queue
{
    struct Queue_Node * head;
    struct Queue_Node * tail;
}
queue_t;

// Initialise queue
struct Queue * init_queue()
{
    struct Queue * new_queue = NULL;
    new_queue = (queue_t * ) malloc(sizeof(queue_t));
    if (!new_queue) {
        fprintf(stderr, "Couldn't create queue!\n");
        exit(EXIT_FAILURE);
    }
    new_queue -> head = NULL;
    new_queue -> tail = NULL;
    return new_queue;
}

// Add item to the queue
void enqueue(struct Queue ** my_queue, const int value)
{
    if (!*my_queue)
        *my_queue = init_queue();
        
    struct Queue_Node * new_node = NULL;
    new_node = (struct Queue_Node * ) malloc(sizeof(struct Queue_Node));
    if (!new_node) {
        fprintf(stderr, "Couldn't create new node!\n");
        exit(EXIT_FAILURE);
    }
    new_node -> value = value;
    new_node -> next = NULL;
    if (!( * my_queue) -> head)
        ( * my_queue) -> head = new_node;

    if (!( * my_queue) -> tail)
        ( * my_queue) -> tail = new_node;
    else {
        ( * my_queue) -> tail -> next = new_node;
        ( * my_queue) -> tail = new_node;
    }
}

// Dequeue first item
void dequeue(struct Queue * my_queue)
{
    if (!my_queue || !my_queue -> head) {
        fprintf(stderr, "No queue!\n");
        return;
    }
    struct Queue_Node * prev = NULL;
    prev = my_queue -> head;
    my_queue -> head = my_queue -> head -> next;
    prev -> next = NULL;
    free(prev);
    prev = NULL;

}

// Return the first item
struct Queue_Node * front(struct Queue * my_queue)
{
    // Returns head or NULL
    return my_queue -> head;
}

// Check if the queue is empty
bool is_empty(struct Queue * my_queue)
{
    if (my_queue -> head)
        return FALSE;
    return TRUE;
}

// Release the memory
void clear_queue(struct Queue ** new_queue)
{
    if (! * new_queue)
        return;
    else {
        struct Queue_Node * start = NULL;
        struct Queue_Node * prev = NULL;
        start = ( * new_queue) -> head;
        while (start) {
            prev = start;
            start = start -> next;
            prev -> next = NULL;
            free(prev);
        }
        free( * new_queue);
        * new_queue = NULL;
    }
}

// Print the Queue
void print_queue(struct Queue * my_queue)
{
    printf("Queue: ");
    if (!my_queue) {
        printf("No queue to print!");
        return;
    }

    struct Queue_Node * start = NULL;
    start = my_queue -> head;
    while (start) {
        printf("%d ", start -> value);
        start = start -> next;
    }
    printf("\n");
}

int main(void)
{
    // Create Queue
    queue_t * new_queue = NULL;
    new_queue = init_queue();

    // Add items to the queue
    enqueue( & new_queue, 5);
    enqueue( & new_queue, 6);
    print_queue(new_queue);

    // Clear the queue and recreate it with other values
    clear_queue( & new_queue);
    for (int i = 0; i < 3; i++)
        enqueue( & new_queue, i);
    printf("Does queue exist:");
    if (is_empty(new_queue))
        printf(" FALSE");
    else
        printf(" TRUE");
    if (!(is_empty(new_queue))) {
        printf("\n");
        print_queue(new_queue);
    } else {
        printf("Queue is empty!\n");
    }

    // Show the first item
    struct Queue_Node * new = NULL;
    new = front(new_queue);
    if (!new) {
        fprintf(stderr, "Couldn't get first node!\n");
    } else
        printf("First node value: %d\n", new -> value);

    // Release the memory
    clear_queue( & new_queue);
}
