#ifndef __SUPPORT_H_
#define __SUPPORT_H_
#define note_t node_t
#define GARBAGE - 232435

// Node structure
typedef struct Node {
    int data;
    struct Node * next;
} node_t;

// Initialize the default head
node_t * init_head(note_t * head);

// Display the linked list
void printList(node_t * head);

// Insert value at the beginning of the list
void insertFirst(note_t ** head, int value);

// Check if the list is empty
int isEmpty(note_t * head);

// Delete the last element in the list
void deleteElement(note_t ** head);

// Count the nodes in list recursively
int count_nodes(note_t * head);

// Return the node on a certain index
note_t * find_element_on_index(note_t * head, int index);

// Delete the node at the specified index
void delete_at_index(note_t ** head, int index);

// Reverse the list
void reverse(struct Node ** head);

// Swap nodes values
void swapNodes(node_t * node1, node_t * node2);

// Sort nodes - slow method
void sortNodes(node_t * head);

// Smarter sort - fast method
void smartSort(node_t * head);

// Test the insert and print functions
void test_1(node_t * head);

// Test the sorting algorithms
void test_2(note_t * head);

// Test returning a node value by index
void test_3(note_t * head);

// Test the delete functions and reverse
void test_4(note_t * head);

#endif
