#ifndef __HEADER_H_
#define __HEADER_H_

#include <errno.h>

#define DIE(suppose, error_message)									\
if (suppose) {														\
    fprintf(stderr, "At line %d in file %s!", __LINE__, __FILE__);	\
    fprintf(stderr, "Errno value: %d with message", errno);			\
    perror(error_message);											\
    exit(errno);													\
}

typedef struct Node {
    void * data;
    struct Node * next;
    struct Node * prev;
}
node_t;

typedef struct List {
    int size;
    int data_size;
    struct Node * next;
}
list_t;

// Initialise the list
list_t * init_list(int data_size);

// Print the list
void printList(list_t * list);

// Add first element
void addFirst(list_t ** list, int value);

// Sort the list values
void sortList(list_t * list);

// Remove the duplicates from a list
void removeDuplicates(list_t * list);

// Inverse the list
void reverseList(list_t * list);

// Return the sum of the two lists
list_t * sum_list(list_t * list1, list_t * list2);

// Merge two sorted lists
list_t * make_merge(list_t * list1, list_t * list2);

// Remove last item
void removeLastItem(list_t ** list1);

// Check if the number formed is a palindrome
void isPalindrome(list_t * list);

// Release the whole list
void makeClean(list_t ** list);

#endif
