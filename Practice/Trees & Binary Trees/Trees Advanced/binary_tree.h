#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__
#include <string.h>
#include "Queue.h"
#include "utils.h"

typedef struct b_node_t b_node_t;
struct b_node_t {
    b_node_t * left; // left child
    b_node_t * right; // right child
    void * data; // data contained by the node
};

typedef struct b_tree_t b_tree_t;
struct b_tree_t {
    b_node_t * root; // root of the tree
    size_t data_size; // size of the data contained by the nodes
};

// Check if the tree is full
int check_full_tree(b_node_t * root);

// Check if every node is equal to the sum of its children
int is_sum_of_children(b_tree_t * b_tree);

// Create tree
b_tree_t * b_tree_create(size_t data_size);

// Insert node in the tree
void b_tree_insert(b_tree_t * b_tree, void * data);

// Preorder print
void b_tree_print_preorder(b_tree_t * b_tree, void( * print_data)(void * ));

// Inorder print
void b_tree_print_inorder(b_tree_t * b_tree, void( * print_data)(void * ));

// Postorder print
void b_tree_print_postorder(b_tree_t * b_tree, void( * print_data)(void * ));

// Release memory
void b_tree_free(b_tree_t * b_tree, void( * free_data)(void * ));

#endif /* BINARY_TREE_H__ */
