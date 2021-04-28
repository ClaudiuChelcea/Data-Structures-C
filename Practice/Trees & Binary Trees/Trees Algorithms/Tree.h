#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "Utils.h"

#include "Queue.h"

#define MAX_NODES 20

// Tree's nodes
typedef struct Node {
    void * data;
    struct Node * left;
    struct Node * right;
}
node_t;

// Tree structure
typedef struct Tree {
    unsigned int data_size;
    struct Node * root;
}
tree_t;

// Initialise a tree
struct Tree * init_tree(unsigned int data_size);

// Create a node
struct Node * __create_node(void * data, unsigned int data_size);

// Add node while always having a full tree
void add_node(struct Tree ** my_tree, void * data);

// Release the memory for the tree
void burn_Tree(struct Tree * my_tree);

// Print tree in preorder
void print_preorder(struct Tree * my_tree);

// Print tree in inorder
void print_inorder(struct Tree * my_tree);

// Print tree in postorder
void print_postorder(struct Tree * my_tree);

// Print the nodes in a hierarchy
void print_hierarchy();

// Return the height of the tree
int find_tree_height(struct Tree * my_tree);

// Check if all leaves are on the same level
bool check_leaves_level(struct Tree * my_tree);

// Show all noted on certain level
void show_nodes_on_level(struct Tree * my_tree, int wanted_level);

// Check if the tree is balanced
int check_balancer_tree(struct Tree * my_tree);

#endif // TREE_H_
