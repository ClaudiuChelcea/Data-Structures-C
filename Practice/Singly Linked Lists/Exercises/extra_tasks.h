#ifndef __EXTRA_H__
#define __EXTRA_H__
#define note_t node_t
#define GARBAGE - 21512

typedef struct Node {
    int value;
    struct Node * next;
}
node_t;

// Choose the task to be executed
void choose_task(node_t * head, node_t * second_head);

// Initialize the default head
void init_head(note_t * head);

// Insert value at the beginning of the list
void insertFirst(note_t ** head, int value);

// Display the list
void printList(node_t * head);

// Reverse the list
void reverseList(node_t ** head);

// Count the nodes in list recursively
int count_nodes(note_t * head);

// Get the first value and move the node
int getFirstValue(node_t ** head);

// Swap nodes values
void swapNodes(node_t * node1, node_t * node2);

// Sort the nodes
void sortNodes(node_t * head);

// Reverse & display the list
void task1(node_t * head);

// Concatenate two sorted lists
void task2(node_t * head, node_t * second_head);

// Delete middle element
void task3(node_t ** head);

// Insert in the middle
void task4(node_t ** head, int value);

// Print elements on even and odd positions
void task5(node_t * head);

// Merge print from two lists
void task6(node_t * head, node_t * second_head);

#endif