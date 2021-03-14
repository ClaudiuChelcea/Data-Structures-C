#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_
#define STRING_SIZE 64

// Nodes
typedef struct Node {
    struct Node * next;
    struct Node * prev;
    void * data;
}
node_t;

// The head of the list
typedef struct List {
    unsigned int data_size;
    unsigned int size;
    struct Node * head;
}
list_t;

// Initialize the list
list_t * init_head(int data_size);

// Add first element
void add_First(list_t * list, void * new_data);

// Display the list
void printList(list_t * list);

// Release the memory
void releaseMemory(list_t ** list);

// Remove duplicates from list
void removeDuplicates(list_t * list);

// Reverse the list
void reverseList(list_t * list);

// Sum of two lists
list_t * sum_list_funct(list_t * A, list_t * B);

// Swap to integers
void swapIntegers(int * a, int * b);

// Sort a list by bubble sort
void sortList(list_t ** list);

// Merge two sorted lists
list_t * merge_lists_funct(list_t * A, list_t * B);

// T-H delete for the element in the middle of the list
void Tortoise_and_Hare_delete(list_t ** list);

#endif
