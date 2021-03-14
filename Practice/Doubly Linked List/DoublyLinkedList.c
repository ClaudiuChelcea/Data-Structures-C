#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <time.h>

int main(void)
{
    // Initialise main list
    list_t * list = NULL;
    list = init_head(sizeof(int));
    if (!list) {
        fprintf(stderr, "Couldn't execute program!\n");
        exit(EXIT_FAILURE);
    }

    // Initialise secondary list (for specific operations with two lists)
    list_t * second_list = NULL;
    second_list = init_head(sizeof(int));
    if (!second_list) {
        fprintf(stderr, "Couldn't execute program!\n");
        exit(EXIT_FAILURE);
    }

    // Initialise values & get the number of elements in the first list
    srand(time(0));
    char command = 0;
    int list_elements = 0;
    printf("Number of list_1 elements: ");
    scanf("%d", &list_elements);

    // Create the first list based on user's input
    for (int i = 1; i <= list_elements; i++) {
        int my_value = 0;
        printf("\nInput '1' to insert a value and '0' to put a random value!\n");
        scanf(" %c", &command);
        if (command == '1') {
            printf("Insert value: ");
            scanf("%d", & my_value);
            printf("Elements to add: %d\n", list_elements - i);
        } else if (command == '0') {
            my_value = rand() % 10;
            printf("Added %d. Elements to add: %d\n", my_value, list_elements - i);
        } else {
            printf("\nInvalid input! Try again!\n");
            i--;
        }
        add_First(list, & my_value);
	}

    // Create the second list with random values
    printf("\nNumber of list_2 elements: ");
    int list2_elements;
    scanf("%d", & list2_elements);
    for (int i = 0; i < list2_elements; i++) {
        int my_value = rand() % 10;
        add_First(second_list, & my_value);
    }

    // Execute operations on the lists:
    if (list -> size <= 0) {
        printf("List is empty! Executed nothing!\n");
        return 0;
    }

    // Display the lists
    printf("\nFirst list:\n");
    printList(list);
    printf("Second list (generated with random values between 0 - 9):\n");
    printList(second_list);

    // Reverse the first list
    printf("Reversed first list: \n");
    reverseList(list);
    printList(list);

    // Reverse it to the original form
    reverseList(list);

    // Create a sum list from the two lists
    list_t * sum_list = NULL;
    sum_list = init_head(sizeof(int));
    if (!sum_list) {
        fprintf(stderr, "Couldn't execute program!\n");
        exit(EXIT_FAILURE);
    }
    sum_list = sum_list_funct(list, second_list);
    printf("The list created by the sum of the other two lists:\n");
    reverseList(sum_list);
    printList(sum_list);

    // Print sorted lists
    sortList( & list);
    sortList( & second_list);
    printf("First list sorted:\n");
    printList(list);
    printf("Second list sorted:\n");
    printList(second_list);
    printf("Merged list:\n");
    list_t * merged_list = NULL;
    merged_list = init_head(sizeof(int));
    if (!merged_list) {
        fprintf(stderr, "Couldn't execute program!\n");
        exit(EXIT_FAILURE);
    }
    merged_list = merge_lists_funct(list, second_list);
    printList(merged_list);

    // Remove duplicates from the first list
    printf("Merged list without adjacent duplicates: \n");
    removeDuplicates(merged_list);
    printList(merged_list);

    // Delete middle element from the first list
    Tortoise_and_Hare_delete( & list);
    printf("Sorted first list after deleting middle element:\n");
    printList(list);

    // Free the memory occupied by the lists
    releaseMemory( & list);
    releaseMemory( & second_list);
    releaseMemory( & merged_list);
}
