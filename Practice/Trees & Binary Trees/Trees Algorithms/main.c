#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "Tree.h"

int main(void) {
    // Create tree
    struct Tree * my_tree = NULL;
    my_tree = init_tree(sizeof(int));

    // Add nodes
    for (int i = 0; i < 10; i++) {
        add_node( & my_tree, & i);
    }

    // Create this hierarchy by adding nodes in a way
    // that we will always have a full tree
    //                    0 
    //             1               2
    //       3 -------- 4     5 -------6
    //    7 -- 8     9 

    // Print the hierarchy
    print_hierarchy();

    // Print tree
    printf("Preorder:\n");
    print_preorder(my_tree);
    printf("Inorder:\n");
    print_inorder(my_tree);
    printf("Postorder:\n");
    print_postorder(my_tree);

    // Calculate tree height
    int tree_height = find_tree_height(my_tree);
    printf("\nTREE HEIGHT:%d\nTREE NUM LEVELS:%d\n\n", tree_height++, tree_height);

    // Check if all leaves are on the same level
    bool leaves_same_level = check_leaves_level(my_tree);
    printf("Are leaves on the same level: ");
    leaves_same_level == 1 ? printf("true\n\n") : printf("false\n\n");

    // Show all nodes on certain levels
    int wanted_level = 2;
    printf("Nodes on the wanted level (2): ");
    show_nodes_on_level(my_tree, wanted_level);

    // Check if the tree is balanced
    printf("Is the tree balanced: ");
    check_balancer_tree(my_tree) == 1 ? printf("true\n\n") : printf("false\n\n");

    // Release memory
    burn_Tree(my_tree);

    return 0;
}
