#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "functions.h"
#include <time.h>

// Initialize the default head
void init_head(note_t * head) {
    head -> next = NULL;
    head -> data = GARBAGE;
}

// Delete middle element
void task_delete_middle(node_t ** head) {
    if (! * head || ( * head) -> data == GARBAGE) {
        if(!*head) {
            fprintf(stderr, "List is empty! Exiting...\n");
            exit(EXIT_SUCCESS);
        }
        else if(( * head) -> data == GARBAGE) {
            free(*head);
            fprintf(stderr, "List is empty! Exiting...\n");
            exit(EXIT_SUCCESS);
        }
    } else if (!( * head) -> next) {
        free(*head);
        head = NULL;
        printf("Deleted single element in list! Exiting...\n");
        exit(EXIT_SUCCESS);
    // Two elements
    } else if ((* head)->next->next == NULL) {
        printf("Before: ");
        printList( * head);
        note_t* tmp = *head;
        * head = ( * head) -> next;
        free(tmp);
        printf("After:  ");
        printList( * head);

    // More elements: Tortoise & Hare
    } else {
        printf("Before: ");
        printList( * head);
        node_t * tortoise = * head;
        node_t * prev = NULL;
        node_t * hare = * head;
        
        while(tortoise && hare->next && hare->next->next)
        {
            prev = tortoise;
            tortoise = tortoise->next;
            hare = hare->next->next;

        }
        prev->next = prev->next->next;
        free(tortoise);
        printf("After:  ");
        printList( * head);
    }
}

// Display the linked list
void printList(node_t * head) {
    if (!head || head -> data == GARBAGE) {
        fprintf(stderr, "Error dsplaying list!\n");
        return;
    }

    while (head) {
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n");
}

// Insert value at the beginning of the list
void insertFirst(note_t **head, int value) {
    if (! *head) {
        *head = malloc(sizeof(node_t));
        init_head( * head);
    }

    note_t * start = NULL;
    start = * head;
    DIE(!start, "Couldn't insert element at the beginning!\n");
    if (start -> data == GARBAGE) {
        start -> data = value;
    } else {
        note_t * new = NULL;
        new = malloc(sizeof(note_t));
        DIE(!new, "Couldn't insert element at the beginning!\n");
        new -> data = value;
        new -> next = start;
        start = new;
        *head = start;
    }

}

// Check if the list is empty
int isEmpty(note_t *head) {
    if (head == NULL)
        return 1;
    else
        return 0;
}

// Delete the last element in the list
void deleteElement(note_t **head) {

    if (( *head) -> next == NULL) {

        *head = NULL;
        return;
    } else {
        node_t *tmp = * head;
        while (tmp -> next -> next) {
            tmp = tmp -> next;
        }
        tmp -> next = NULL;
    }
}

// Count the nodes in list recursively
int count_nodes(note_t * head) {
    if (!head)
        return 0;
    return 1 + count_nodes(head -> next);
}

// Return the node on a certain index
note_t * find_element_on_index(note_t *head, int index) {
    if (count_nodes(head) < index || index < 0) {
        return NULL;
    } else {
        for (int i = 0; i < index - 1; i++)
            head = head -> next;
        return head;
    }
}

// Delete the node at the specified index
void delete_at_index(note_t ** head, int index) {
    if (! * head)
        return;
    else if (index < 0 || index > count_nodes( * head)) {
        printf("Wrong index\n");
        return;
    } else if (index == 0) {
        ( *head) = ( * head) -> next;
    } else if (index == count_nodes( * head))
        deleteElement(head);
    else {
        note_t * start = *head;
        for (int i = 0; i < index - 2; i++)
            start = start -> next;
        start -> next = start -> next -> next;
    }
}

// Reverse the list
void reverse(struct Node ** head) {
    struct Node *prev_node = NULL;
    struct Node *current_node = * head;
    struct Node *next_node;

    while (current_node != NULL) {
        next_node = current_node -> next;
        current_node -> next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }

    *head = prev_node;
}

// Swap nodes values
void swapNodes(node_t *node1, node_t *node2) {
    int aux = node1 -> data;
    node1 -> data = node2 -> data;
    node2 -> data = aux;
}

// Sort nodes - slow method
void sortNodes(node_t *head) {
    int n = count_nodes(head);
    node_t *my_i = head;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            note_t * my_j = head;
            for (int k = 0; k < j; k++)
                my_j = my_j -> next;
            if (my_i -> data > my_j -> data)
                swapNodes(my_i, my_j);
        }
        my_i = my_i -> next;
    }
}

// Smarter sort - fast method
void smartSort(node_t * head) {
    for (node_t * curr = head; curr != NULL; curr = curr -> next) {
        for (note_t * next = curr -> next; next != NULL; next = next -> next)
            if (curr -> data > next -> data)
                swapNodes(curr, next);
    }
}

// Test the insert and print functions
void test_1(node_t * head) {
	printf("Testing insertions, deletions and display\n");
    init_head(head);
    insertFirst( & head, 5);

    while (!isEmpty(head))
        deleteElement( & head);

    insertFirst( & head, 1);
    insertFirst( & head, 2);
    insertFirst( & head, 3);
    insertFirst( & head, 4);
    printList(head);
}

// Test the sorting algorithms
void test_2(note_t * head) {
	printf("Testing insertions, random values and list sort\n");
    insertFirst( & head, 5);
    srand(time(0));
    for (int i = 0; i < 50; i++) {
        int x = rand() % 4;
        insertFirst( & head, x);
    }
    smartSort(head);
    printList(head);
}

// Test returning a node value by index
void test_3(note_t * head) {
	printf("Testing returning the value from a certain node\n");
    printf("Choose from (1-10): ");
    for (int i = 0; i < 10; i++) {
        int x = rand() % 10;
        insertFirst( & head, x);
    }
    printList(head);
    int x;
    printf("Insert node index to return value from: ");
    scanf("%d", & x);
    note_t * my_node = find_element_on_index(head, x);
    if (!my_node) {
        printf("Couldn't return item!\n");
        free(my_node);
    } else {
        printf("My_node:%d\n", my_node -> data);
    }
}

// Test the delete functions and reverse
void test_4(note_t * head) {
	printf("Testing deleting items from certain indexes in list\n");
    for (int i = 0; i < 10; i++) {
        int x = rand() % 10;
        insertFirst( & head, x);
    }
    printf("My list: ");
    printList(head);
    printf("How many to delete:");
    int x;
    scanf("%d", & x);
    int a;
    for (int i = 0; i < x; i++) {
        printf("Insert index: ");
        scanf("%d", & a);
        delete_at_index( & head, a);
        printf("Current list: ");
        printList(head);
    }

    printf("Now reversing list...\n");
    reverse( & head);
    printList(head);
}
