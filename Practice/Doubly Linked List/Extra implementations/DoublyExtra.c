#include "DoublyExtra.h"
#include <stdio.h>
#include <stdlib.h>

// Initialise the list
list_t* init_list(int data_size)
{
	list_t* list = NULL;
	list = (list_t*) malloc(sizeof(list_t));
	DIE(!list,"Couldn't initialise list!");
	list->size = 0;
	list->data_size = data_size;
	list->next = NULL;
	return list;
}

// Print the list
void printList(list_t* list)
{
	if(!list || !list->next) {
		fprintf(stderr,"No list to print!\n");
		return;
	}

	node_t* head = NULL;
	head = list->next;
	if(!head) {
		fprintf(stderr,"No head for printing!\n");
		return;
	}

	while(head) {
		if(list->data_size == sizeof(int)) {
			if(head->next)
				printf("%d <--> ",*((int*)head->data));
			else
				printf("%d\n",*((int*)head->data));
		}
		else {
			printf("TO DO: print other data type!\n");
		}

		head = head->next;
	}
	printf("\n");
}

// Add first element
void addFirst(list_t** list, int value)
{
	if(!(*list)) {
		(*list) = init_list(sizeof(int));
		DIE(!(*list),"Error! Couldn't initialise list!\n");
		node_t* new_node = NULL;
		new_node = malloc(sizeof(node_t));
		DIE(!new_node,"Couldn't create first element in list!");
		new_node->data = malloc(sizeof((*list)->data_size));
		*((int*)new_node->data) = value;
		new_node->prev = NULL;
		new_node->next = NULL;
		(*list)->next = new_node;
		(*list)->size++;
	}

	else if(!(*list)->next) {
		node_t* new_node = NULL;
		new_node = malloc(sizeof(node_t));
		DIE(!new_node,"Couldn't create first element in list!");
		new_node->data = malloc(sizeof((*list)->data_size));
		*((int*)new_node->data) = value;
		new_node->prev = NULL;
		new_node->next = NULL;
		(*list)->next = new_node;
		(*list)->size++;
	}
	else {
		node_t* new_node = NULL;
		new_node = malloc(sizeof(node_t));
		DIE(!new_node,"Couldn't create first element in list!");
		new_node->data = malloc(sizeof((*list)->data_size));
		*((int*)new_node->data) = value;
		new_node->prev = NULL;
		new_node->next = (*list)->next;
		(*list)->next->prev = new_node;
		(*list)->next = new_node;
		(*list)->size++;
	}
}


// Sort the list values
void sortList(list_t* list)
{
	if(!list) {
		fprintf(stderr,"No list to sort!\n");
		return;
	}
	for(node_t* i = list->next;i!=NULL;i=i->next)
		for(node_t* j = i->next;j!=NULL;j=j->next)
			if(*((int*)i->data) > *((int*)j->data)) {
				int aux = *((int*)i->data);
				*((int*)i->data) = *((int*)j->data);
				*((int*)j->data) = aux;
			}
}

// Remove the duplicates from a list
void removeDuplicates(list_t* list)
{
	if(!list || !list->next) {
		fprintf(stderr,"No list to remove duplicates from!\n");
		return;
	}
	else if(!list->next->next)
		return;
	else if(!list->next->next->next) {
		
		node_t* new_node = NULL;
		new_node = list->next;
		if(*((int*)new_node->data) == *((int*)new_node->next->data)) {
				new_node->next->next = NULL;
				new_node->next->prev = NULL;
				free(new_node->next->data);
				new_node->next = NULL;
				list->size--;
		}
	}
	else {
		node_t* new_node = NULL;
		new_node = list->next;
		if(!new_node) {
					fprintf(stderr,"Error removing duplicates!\n");
					exit(EXIT_FAILURE);
				}

		while(new_node->next) {
			if(*((int*)new_node->data) == *((int*)new_node->next->data)) {
				node_t* new_node2 = NULL;
				new_node2 = new_node->next;
				if(!new_node2) {
					fprintf(stderr,"Error removing duplicates!\n");
					exit(EXIT_FAILURE);
				}
				if(new_node->next->next) {
					new_node->next = new_node->next->next;
					new_node->next->prev = new_node;
				}
				else {
					new_node->next = NULL;
				}
				new_node2->next = NULL;
				new_node2->prev = NULL;
				free(new_node2->data);
				free(new_node2);
				new_node2 = NULL;
				list->size--;
				
			}
			else
				new_node = new_node->next;

		}

	}
}

// Inverse the list
void reverseList(list_t* list)
{
	if(!list || !list->next) {
		fprintf(stderr,"No list to reverse!\n");
		return;
	}
	else if(!list->next->next) {
		return;
	}
	else {
		node_t* new_node = NULL;
		new_node = list->next;
		if(!new_node) {
			fprintf(stderr,"Couldn't inverse list!\n");
			exit(EXIT_FAILURE);
		}
		
		node_t* tmp = NULL;
		tmp = new_node->prev;
	
		while(new_node) {
			new_node->prev = new_node->next;
			new_node->next = tmp;
			tmp = new_node;
			if(new_node->prev == NULL) {
				break;
			}
			else
				new_node = new_node->prev;
			
		}
		list->next = new_node;
	}
}

// Return the sum of the two lists
list_t* sum_list(list_t* list1, list_t* list2)
{
	if(!list1 || !list2) {
		printf("Couldn't receive the lists for the sum!\n");
		return NULL;
	}
	
	list_t* sum_pointer = NULL;
	sum_pointer = init_list(list1->data_size);
	DIE(!sum_pointer,"Couldn't execute sum!\n");
	node_t* copy = NULL;

	node_t* l1_node = NULL;
	node_t* l2_node = NULL;
	l1_node = list1->next;
	l2_node = list2->next;
	DIE(!l1_node,"Couldn't execute sum!\n");
	DIE(!l2_node,"Couldn't execute sum!\n");
	int i = 0;
	while(l1_node && l2_node) {
		addFirst(&sum_pointer,*((int*)l1_node->data) + *((int*)l2_node->data));
		if(i==0) {
			copy = sum_pointer->next;
			DIE(!copy," Couldn't execute sum!\n");
		}
		i++;
		if(l1_node->next && l2_node->next) {
			l1_node= l1_node->next;
			l2_node = l2_node->next;
		}
		else break;
	}

	while(l1_node->next) {
		addFirst(&sum_pointer,*((int*)l1_node->next->data));
		l1_node = l1_node ->next;
		
	}
	while(l2_node->next) {
		addFirst(&sum_pointer,*((int*)l2_node->next->data));
		l2_node = l2_node ->next;
	}

	// Reiterate the new list and move values bigger than 10
	reverseList(sum_pointer);
	int memory_add = 0;
	while(copy) {
		*((int*)copy->data) += memory_add;
		memory_add = 0;
		while((*(int*)copy->data) >= 10) {
			*((int*)copy->data) -=10;
			memory_add++;
		}
		copy = copy->next;
	}

	if(memory_add!=0) {
		reverseList(sum_pointer);
		addFirst(&sum_pointer,memory_add);
		memory_add = 0;
		reverseList(sum_pointer);
	}

	return sum_pointer;
}

// Merge two sorted lists
list_t* make_merge(list_t* list1, list_t* list2)
{
	if(!list1 || !list2) {
		printf("Couldn't receive the lists for the sum!\n");
		return NULL;
	}
	
	list_t* merged_list = NULL;
	merged_list = init_list(list1->data_size);
	DIE(!merged_list,"Couldn't execute sum!\n");
	node_t* l1_node = NULL;
	node_t* l2_node = NULL;
	l1_node = list1->next;
	l2_node = list2->next;
	DIE(!l1_node,"Couldn't execute sum!\n");
	DIE(!l2_node,"Couldn't execute sum!\n");

	while(l1_node && l2_node) {
		if(*((int*)l1_node->data) < *((int*)l2_node->data)) {
			addFirst(&merged_list,*((int*)l1_node->data));
			if(l1_node->next)
				l1_node = l1_node->next;
			else
				l1_node = NULL;
		}
			
		else if(*((int*)l1_node->data) >= *((int*)l2_node->data)) {
			addFirst(&merged_list,*((int*)l2_node->data));
			if(l2_node->next)
				l2_node = l2_node->next;
			else
				l2_node = NULL;
		}
	}

	while(l1_node) {
		addFirst(&merged_list,*((int*)l1_node->data));
		if(l1_node->next)
				l1_node = l1_node->next;
			else
				break;
	}
	while(l2_node) {
		addFirst(&merged_list,*((int*)l2_node->data));
		if(l2_node->next)
				l2_node = l2_node->next;
			else
				break;
			printf("Added from 2\n");
	}
	reverseList(merged_list);
	return merged_list;
}	

// Remove last item
void removeLastItem(list_t** list1)
{
	if(!*list1 || !(*list1)->next) {
		fprintf(stderr,"Couldn't remove last item! List is empty!\n");
		return;
	}
	else if(!(*list1)->next->next) {
		free((*list1)->next->data);
		(*list1)->next->next = NULL;
		(*list1)->next->prev = NULL;
		free((*list1)->next);
		free((*list1));
		*list1 = NULL;
	}
	else {
		node_t* start = NULL;
		start = (*list1)->next;
		DIE(!start,"Couldn't execute remove!\n");
		while(start->next->next)
			start = start->next;
		free(start->next->data);
		start->next->prev = NULL;
		free(start->next);
		start->next = NULL;
	}
}

// Check if the number formed is a palindrome
void isPalindrome(list_t* list)
{
	if(!list || !list->next) {
		fprintf(stderr,"Can't verify a palindrome if the list is empty!\n");
		return;
	}
	else if(!list->next->next) {
		printf("The lists forms a palindrome\n");
		return;
	}
	else {
		node_t* start = NULL;
		start = list->next;
		DIE(!start,"Couldn't verify if the list is a palindrome!\n");
		node_t* second_start = NULL;
		second_start = list->next;
		DIE(!second_start,"Couldn't verify if the list is a palindrome!\n");

		while(start->next) {
			start = start->next;
		}
		int palindrome = 1;
		while(second_start->next) {
			if(*((int*)second_start->data) != *((int*)start->data)) {
				palindrome = 0;
				break;
			}
			second_start = second_start->next;
			start = start->prev;
		}
		if(palindrome)
			printf("List forms a palindrome!\n");
		else
			printf("List doesn't form a palindrome!\n");
	}
}

// Release the whole list
void makeClean(list_t** list)
{
	if(!*list) {
		fprintf(stderr,"List is already empty!\n");
		return;
	}
	else if(!(*list)->next) {
		free(*list);
	}
	else if(!(*list)->next->next) {
		free((*list)->next->data);
		(*list)->next->next = NULL;
		(*list)->next->prev = NULL;
		free((*list)->next);
		free((*list));
	}
	else {
		node_t* current = NULL;
		node_t* prev = NULL;
		current = (*list)->next;
		DIE(!current,"Couldn't clean the memory!\n");
		while(current->next) {
			prev = current;
			current = current->next;
			free(prev->data);
			prev->next = NULL;
			prev->prev = NULL;
			free(prev);
			prev = NULL;
			
		}
		free(current->data);
		current->prev = NULL;
		current->next = NULL;
		free(current);
		current = NULL;
		(*list)->next = NULL;
		free((*list));
		*list = NULL;
	}
	printf("Cleaned list!\n");
}
