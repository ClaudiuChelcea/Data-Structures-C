#include "binary_tree.h"

// Read input and insert nodes
void read_tree(b_tree_t * b_tree) {
    int N = 0, data = 0;

    scanf("%d", & N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", & data);
        b_tree_insert(b_tree, & data);
    }
}

// Print (void*) data as (int)
void print_data(void * data) {
    printf("%d ", *(int * ) data);
}

int main(void) {
    // Read tree and create it
    b_tree_t * binary_tree = NULL;
    binary_tree = b_tree_create(sizeof(int));
    read_tree(binary_tree);

    // Print order
    b_tree_print_preorder(binary_tree, print_data);
    b_tree_print_inorder(binary_tree, print_data);
    b_tree_print_postorder(binary_tree, print_data);

    // Check if every node is the sum of its children
    if (is_sum_of_children(binary_tree)) {
        printf("Is sum of children: true\n");
    } else {
        printf("Is sum of children: false\n");
    }

    // Check if the tree is full
    if (check_full_tree(binary_tree -> root))
        printf("Is full: full\n");
    else
        printf("Is full: not full\n");

    // Release memory
    b_tree_free(binary_tree, free);

    return 0;
}
