#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extra_tasks.h"

int main(void) {
    // Initialise two lists
    node_t * head = malloc(sizeof(node_t));
    node_t * second_head = malloc(sizeof(node_t));
    init_head(head);
    init_head(second_head);

    // Get the list lenght
    printf("Insert list_1 length: ");
    int list_length;
    scanf("%d", & list_length);
    printf("Insert list_2 length: ");
    int list_length_2;
    scanf("%d", & list_length_2);
    printf("\n");

    // Insert n random nodes
    srand(time(0));
    for (int i = 0; i < list_length; i++)
        insertFirst( & head, rand() % 15);

    for (int i = 0; i < list_length_2; i++)
        insertFirst( & second_head, rand() % 15);

    // Choose task
    choose_task(head, second_head);

    return 0;
}
