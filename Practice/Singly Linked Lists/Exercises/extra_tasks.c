#include <stdio.h>

#include "extra_tasks.h"

#include <stdlib.h>

// Choose the task to be executed
void choose_task(node_t * head, node_t * second_head) {
    int value = 0;

    printf("Insert '0' to execute the default task or an number (1-6) to specify a certain task: ");
    int n;
    scanf("%i", & n);
    printf("\n");
    if (n == 0) {
        task3( & head);
        exit(EXIT_SUCCESS);
    } else if (!(n >= 0 && n <= 7)) {
        printf("Invalid digit!");
        exit(EXIT_FAILURE);
    } else {
        switch (n) {
            // 311 CAa
        case 1:
            task1(head);
            break;
            // 311 CAb
        case 2:
            sortNodes(head);
            sortNodes(second_head);
            task2(head, second_head);
            break;
            // 312 CAa
        case 3:
            task3( & head);
            break;
            // 312 CAb
        case 4:
            printf("Value to insert: ");
            scanf("%d", & value);
            task4( & head, value);
            break;
            // 313 CAa
        case 5:
            task5(head);
            break;
            // 313 Cab
        case 6:
            task6(head, second_head);
            break;
        default:
            printf("Choose a number between (1-6)!\n");
            break;
        }
    }
}

// Initialize the default head
void init_head(note_t * head) {
    head -> next = NULL;
    head -> value = GARBAGE;
}

// Insert value at the beginning of the list
void insertFirst(note_t ** head, int value) {
    if (! * head) {
        * head = malloc(sizeof(node_t));
        init_head( * head);
    }
    note_t * start = NULL;
    start = * head;
    if (!start) {
        fprintf(stderr, "Couldn't insert element at the beginning!\n");
        exit(EXIT_FAILURE);
    }

    if (start -> value == GARBAGE) {
        start -> value = value;
    } else {
        note_t * new = NULL;
        new = malloc(sizeof(note_t));
        if (!new) {
            fprintf(stderr, "Couldn't insert element at the beginning!\n");
            exit(EXIT_FAILURE);
        }
        new -> value = value;
        new -> next = start;

        * head = new;
    }
}

// Display the list
void printList(node_t * head) {
    if (!head || head -> value == GARBAGE) {
        fprintf(stderr, "Couldn't display file!\n");
        return;
    }
    while (head) {
        printf("%d ", head -> value);
        head = head -> next;
    }
    printf("\n");
}

// Reverse the list
void reverseList(node_t ** head) {
    node_t * prev = NULL;
    node_t * curr = * head;
    node_t * next = NULL;
    while (curr) {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    * head = prev;
}

// Reverse & display the list
void task1(node_t * head) {
    printf("My list:\n");
    printList(head);
    printf("Reversing list...\n");
    reverseList( & head);
    printList(head);
}

// Count the nodes in list recursively
int count_nodes(note_t * head) {
    if (!head)
        return 0;
    return 1 + count_nodes(head -> next);
}

// Get the first value and move the node
int getFirstValue(node_t ** head) {
    if (!head)
        return GARBAGE;

    note_t * start = * head;
    * head = ( * head) -> next;
    if (start)
        return start -> value;

}

// Swap nodes values
void swapNodes(node_t * node1, node_t * node2) {
    int aux = node1 -> value;
    node1 -> value = node2 -> value;
    node2 -> value = aux;
}

// Sort the nodes
void sortNodes(node_t * head) {
    for (node_t * curr = head; curr != NULL; curr = curr -> next) {
        for (note_t * next = curr -> next; next != NULL; next = next -> next)
            if (curr -> value > next -> value)
                swapNodes(curr, next);
    }
}

// Concatenate two sorted lists
void task2(node_t * head, node_t * second_head) {
    printf("My first list:\n");
    printList(head);
    printf("My second list\n");
    printList(second_head);
    printf("Concatenating lists...\n");

    while (second_head) {
        insertFirst( & head, second_head -> value);
        second_head = second_head -> next;
    }

    sortNodes(head);
    printList(head);

}

// Delete middle element
void task3(node_t ** head) {
    if (! * head || ( * head) -> value == GARBAGE) {
        fprintf(stderr, "List is empty! Exiting...\n");
        exit(EXIT_SUCCESS);
    } else if (!( * head) -> next) {
        head = NULL;
        printf("Deleted single element in list! Exiting...\n");
        exit(EXIT_SUCCESS);
    } else if (count_nodes( * head) == 2) {
        printf("Before: ");
        printList( * head);
        * head = ( * head) -> next;
        printf("After:  ");
        printList( * head);
    } else if (count_nodes( * head) % 2 == 1) {
        printf("Before: ");
        printList( * head);
        node_t * start = * head;
        int el_to_delete = count_nodes( * head) / 2;
        for (int i = 0; i < el_to_delete - 1; i++)
            start = start -> next;
        start -> next = start -> next -> next;
        printf("After:  ");
        printList( * head);

    } else if (count_nodes( * head) % 2 == 0) {
        printf("Before: ");
        printList( * head);
        node_t * start = * head;
        int el_to_delete = count_nodes( * head) / 2 - 1;
        for (int i = 0; i < el_to_delete - 1; i++)
            start = start -> next;
        start -> next = start -> next -> next;
        printf("After:  ");
        printList( * head);
    }
}

// Insert in the middle
void task4(node_t ** head, int value) {

    if (! * head || ( * head) -> value == GARBAGE) {
        if (!( * head)) {
            ( * head) = malloc(sizeof(node_t));
            init_head( * head);
        } else if (( * head) -> value == GARBAGE)
            ( * head) -> value = value;

        printf("After:  ");
        printList( * head);
        exit(EXIT_SUCCESS);
    } else if (count_nodes( * head) == 2) {
        printf("Before: ");
        printList( * head);
        node_t * start = malloc(sizeof(node_t));
        start = * head;
        node_t * new_node = malloc(sizeof(node_t));
        new_node -> value = value;
        new_node -> next = start -> next;
        start -> next = new_node;
        printf("After:  ");
        printList( * head);
    } else if (count_nodes( * head) % 2 == 1) {
        printf("Before: ");

        printList( * head);
        node_t * start = * head;
        int el_to_add = count_nodes( * head) / 2;
        for (int i = 0; i < el_to_add - 1; i++)
            start = start -> next;
        node_t * new_node = malloc(sizeof(node_t));
        new_node -> value = value;
        new_node -> next = start -> next;
        start -> next = new_node;
        printf("After:  ");
        printList( * head);

    } else if (count_nodes( * head) % 2 == 0) {
        printf("Before: ");
        printList( * head);
        node_t * start = * head;
        int el_to_add = count_nodes( * head) / 2;
        for (int i = 0; i < el_to_add - 1; i++)
            start = start -> next;
        node_t * new_node = malloc(sizeof(node_t));
        new_node -> value = value;
        new_node -> next = start -> next;
        start -> next = new_node;
        printf("After:  ");
        printList( * head);
    }
}

// Print elements on even and odd positions
void task5(node_t * head) {
    printf("My list: ");
    printList(head);
    printf("Even positions: ");
    node_t * start = head;
    int i = 0;
    while (head) {
        if (i % 2 == 0)
            printf("%d ", head -> value);
        i++;
        head = head -> next;
    }
    i = 0;
    head = start;
    printf("\nOdd positions: ");
    while (head) {
        if (i % 2 == 1)
            printf("%d ", head -> value);
        i++;
        head = head -> next;
    }
    printf("\n");
}

// Merge print from two lists
void task6(node_t * head, node_t * second_head) {
    printf("First list: ");
    printList(head);
    printf("Secondt list: ");
    printList(second_head);
    printf("Merged list: ");

    if (count_nodes(head) > count_nodes(second_head)) {
        while (second_head) {
            printf("%d %d ", head -> value, second_head -> value);
            head = head -> next;
            second_head = second_head -> next;
        }
        while (head) {
            printf("%d ", head -> value);
            head = head -> next;

        }
    } else {
        while (head) {
            printf("%d %d ", second_head -> value, head -> value);
            head = head -> next;
            second_head = second_head -> next;
        }
        while (second_head) {
            printf("%d ", second_head -> value);
            second_head = second_head -> next;

        }
    }
    printf("\n");
}
