#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <ctype.h>

// Initialise list
void init_list(struct LinkedList * list) {
    if (!list) {
        fprintf(stderr, "Couldn't initialise list!\n");
        exit(EXIT_FAILURE);
    } else {
        list -> next = NULL;
        list -> data = malloc(sizeof(int));
        *((int * ) list -> data) = GARBAGE;
        if (!list -> data) {
            free(list -> data);
            fprintf(stderr, "Couldn't initialise list!\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Initialise node
void init_list_node(struct Node * list) {
    if (!list) {
        fprintf(stderr, "Couldn't initialise list!\n");
        exit(EXIT_FAILURE);
    } else {
        list -> next = NULL;
        list -> data = malloc(sizeof(int));
        *((int * ) list -> data) = GARBAGE;
        if (!list -> data) {
            free(list -> data);
            fprintf(stderr, "Couldn't initialise list!\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Add first element
void addFirst(struct LinkedList ** head, int new_data) {
    if (!head) {
        fprintf(stderr, "Couldn't insert first element!\n");
        exit(EXIT_FAILURE);
    }
    struct LinkedList * new = NULL;
    new = malloc(sizeof(struct LinkedList));
    init_list(new);
    *((int * ) new -> data) = new_data;
    new -> next = * head;
    * head = new;
}

// Add last element
void addLast(struct LinkedList * head, int new_data) {
    if (!head) {
        fprintf(stderr, "Couldn't insert last element!\n");
        exit(EXIT_FAILURE);
    }

    while (head -> next)
        head = head -> next;

    head -> next = malloc(sizeof(struct LinkedList));
    head -> next -> data = malloc(sizeof(int));

    *((int * ) head -> next -> data) = new_data;

    head -> next -> next = NULL;

}

// Add node to nth position
void add_nth_node(struct LinkedList ** list, int n, void * new_data)
{
    // !list
    if (! * list) {

        * list = malloc(sizeof(struct LinkedList));
        init_list( * list);
        *((int * )( * list) -> data) = * ((int * )(new_data));

    }
    // list is empty
    else if (!( * list) -> next && * ((int * )( * list) -> data) == GARBAGE) {

        *((int * )( * list) -> data) = * ((int * )(new_data));
    }
    // bad index
    else if (n < 0) {
        fprintf(stderr, "Error index!\n");
        return;
    }
    // first
    else if (n == 0) {
        addFirst(list, *((int * ) new_data));
    }

    // last
    else if (n >= get_size( * list)) {
        addLast( * list, *((int * ) new_data));
    }
    // > 0, < list_length
    else if (n > 0 && n < get_size( * list)) {
        struct LinkedList * new = malloc(sizeof(struct LinkedList));
        struct LinkedList * start = * list;
        init_list(new);
        *((int * ) new -> data) = * ((int * )(new_data));
        for (int i = 0; i < n - 1; i++)
            *
            list = ( * list) -> next;
        new -> next = ( * list) -> next;
        ( * list) -> next = new;
        * list = start;
    }

}

// Remove node nth
struct Node * remove_nth_node(struct LinkedList ** head, int n) {
    if (! * head) {
        struct Node * my_new_node = malloc(sizeof(struct Node));
        init_list_node(my_new_node);
        return my_new_node;

    } else if (!(( * head) -> next)) {
        struct Node * my_new_node = malloc(sizeof(struct Node));
        init_list_node(my_new_node);
        *((int * ) my_new_node -> data) = * ((int * )( * head) -> data);
        ( * head) -> next = NULL;
        free(( * head) -> data);
        free( * head);
        * head = NULL;

        return my_new_node;

    } else if ( * ((int * )( * head) -> data) == GARBAGE) {

        free(( * head) -> data);
        free( * head);
        * head = NULL;
        struct Node * my_new_node = malloc(sizeof(struct Node));
        init_list_node(my_new_node);
        return my_new_node;

    } else if (n < 0) {
        fprintf(stderr, "Invalid index!");
        struct Node * my_new_node = malloc(sizeof(struct Node));
        init_list_node(my_new_node);
        return my_new_node;

    } else if (n == 0) {
        struct Node * my_new_node = malloc(sizeof(struct Node));
        init_list_node(my_new_node);
        *((int * ) my_new_node -> data) = * ((int * )( * head) -> data);
        struct LinkedList * start = * head;
        * head = ( * head) -> next;
        free(start -> data);
        free(start);
        return my_new_node;

    } else if (n >= get_size( * head)) {

        struct LinkedList * copy = * head;
        while (copy -> next -> next)
            copy = copy -> next;

        struct Node * my_new_node = malloc(sizeof(struct Node));
        init_list_node(my_new_node);
        *((int * ) my_new_node -> data) = * ((int * ) copy -> next -> data);
        free(copy -> next -> data);
        free(copy -> next);
        copy -> next = NULL;

        return my_new_node;

    } else if (n > 0 && n < get_size( * head)) {

        struct LinkedList * copy = * head;

        for (int i = 0; i < n - 1; i++)
            copy = copy -> next;

        struct Node * my_node = malloc(sizeof(struct Node));
        init_list_node(my_node);
        *((int * ) my_node -> data) = * ((int * )( * head) -> next -> data);

        struct LinkedList * copy_new = copy -> next;
        copy -> next = copy -> next -> next;
        free(copy_new -> data);
        free(copy_new);
        return my_node;
    }
}

// Get the size of the list
int get_size(struct LinkedList * list) {
    if (!list)
        return 0;
    return 1 + get_size(list -> next);
}

// Release the list
void free_list(struct LinkedList ** pp_list) {

    struct LinkedList * tmp;
    while ( * pp_list) {
        tmp = * pp_list;
        * pp_list = ( * pp_list) -> next;
        free(tmp -> data);
        free(tmp);
    }
    free( * pp_list);

}

// Print the list as int
void print_int_linkedlist(struct LinkedList * list) {

    if (!list || * ((int * ) list -> data) == GARBAGE) {
        fprintf(stderr, "Couldn't display list!\n");
        return;
    }
    while (list) {
        printf("%d ", *((int * ) list -> data));
        list = list -> next;
    }
    printf("\n");
}

// Print the list as string
void print_string_linkedlist(struct LinkedList * list) {
    if (!list || * ((int * ) list -> data) == GARBAGE) {
        fprintf(stderr, "Couldn't display list!\n");
        return;
    }

    while (list) {
        printf("%s ", (char*)(list -> data));
        list = list -> next;
        if(list->next == NULL) {
            int i = 0;
            for(int i=0;i<4;i++)
                printf("%c",*(char*)(list -> data+i));
            break;
        }
    }

    printf("\n");
}
