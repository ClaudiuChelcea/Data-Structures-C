#include <stdio.h>
#include <stdlib.h>
#include "DoublyExtra.h"
#include <time.h>

int main(void)
{
	// Create the list that points to the first node
	list_t* list = NULL;
	list = init_list(sizeof(int));

	// Add elements
	srand(time(0));
	for(int i = 0; i < 6; i++)
		addFirst(list,rand()%8);

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
	//for(int i = 0; i < 4; i++)
		//addFirst(list,rand()%10);

	list_t* list_second = NULL;
	list_second = init_list(sizeof(int));
	for(int i = 0; i < 4; i++)
		addFirst(list_second,9);

	printf("First list:\n");
	printList(list);
	printf("Second list:\n");
	printList(list_second);
	printf("Sum of lists:\n");
	list_t* sum_pointer = NULL;
	sum_pointer = sum_list(list,list_second);
	printList(sum_pointer);



	return 0;
}
