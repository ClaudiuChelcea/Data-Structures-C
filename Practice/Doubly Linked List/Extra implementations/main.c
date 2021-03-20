#include <stdio.h>
#include <stdlib.h>
#include "DoublyExtra.h"
#include <time.h>

int main(void) {
    // Create the list that points to the first node
    list_t * list = NULL;
    list = init_list(sizeof(int));

    // Add elements
    srand(time(0));
    for (int i = 0; i < 6; i++)
        addFirst(&list, rand()%8);

    // Initial list
    printf("Initial list:\n");
    printList(list);

    // Sorted list
    printf("Sorted list:\n");
    sortList(list);
    printList(list);

    // Remove duplicates
    printf("Sorted list without duplicates:\n");
    removeDuplicates(list);
    printList(list);

    // Reverse the list
    printf("Reversed list:\n");
    reverseList(list);
    printList(list);

    // Add new values for new tests & create a new list
    // Return the sum of the two lists
    for (int i = 0; i < 2; i++)
        addFirst(&list, rand()%9);

    list_t * list_second = NULL;
    list_second = init_list(sizeof(int));
    for (int i = 0; i < 3; i++)
        addFirst(&list_second, rand()%7);

    printf("First list:\n");
    printList(list);
    printf("Second list:\n");
    printList(list_second);
    printf("Sum of lists:\n");
    list_t * sum_pointer = NULL;
    sum_pointer = sum_list(list, list_second);
    DIE(!sum_pointer, "Couldn't sum lists!");
    printList(sum_pointer);

    // Merge two sorted lists
    printf("First list:\n");
    sortList(list);
    printList(list);
    printf("Second list:\n");
    sortList(list_second);
    printList(list_second);
    printf("Merged list:\n");
    list_t * merged_list = NULL;
    merged_list = make_merge(list, list_second);
    DIE(!merged_list, "Couldn't merge lists!");
    printList(merged_list);

    // Recreate a new list by removing and adding new items
    printf("My list:\n");
    printList(merged_list);
    removeDuplicates(merged_list);
    for (int i = 0; i < 4; i++) {
        removeLastItem( & merged_list);
        addFirst(&merged_list, rand()%9);
    }
    printf("New list:\n");
    printList(merged_list);

    // Verify if the number formed is palindrome
    isPalindrome(merged_list);

    // Clean the list and create a new one
    makeClean(&merged_list);

    // Create a new palindrome list
    addFirst(&merged_list, 1);
    addFirst(&merged_list, 2);
    addFirst(&merged_list, 1);
    printf("\nCreated new list:\n");
    printList(merged_list);
    isPalindrome(merged_list);
    makeClean(&merged_list);

    // Create a new list for new tests
    printf("\nNew list:\n");
    for (int i = 0; i < 6; i++) {
        addFirst(&merged_list, rand()%9);
    }
    printList(merged_list);

    // Release the memory
    makeClean(&list);
    makeClean(&list_second);
    makeClean(&merged_list);
    makeClean(&sum_pointer);

    return 0;
}
