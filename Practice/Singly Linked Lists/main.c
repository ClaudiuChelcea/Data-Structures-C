#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "support.h"
#include "utils.h"

int main(void) {
    struct Node * head = NULL;
    head = malloc(sizeof(struct Node));
    DIE(!head, "Didn't allocate memory correctly!\n");

    int n;
    printf("Test number (1-4): ");
    scanf("%d", & n);

    // Choose the test
    switch (n) {
    case 1:
        test_1(head);
        break;
    case 2:
        test_2(head);
        break;
    case 3:
        test_3(head);
        break;
    case 4:
        test_4(head);
        break;
    default:
        fprintf(stderr, "Insert a number between 1 and 4!\n");
        return -1;
    }

    free(head);

    return 0;
}
