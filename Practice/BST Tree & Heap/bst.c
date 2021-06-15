#include "bst.h"

#include "utils.h"

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static bst_node_t * __bst_node_create(void * data, size_t data_size) {
    bst_node_t * bst_node;

    bst_node = malloc(sizeof( * bst_node));

    DIE(bst_node == NULL, "bst_node malloc");

    bst_node -> left = bst_node -> right = NULL;

    bst_node -> data = malloc(data_size);
    DIE(bst_node -> data == NULL, "bst_node->data malloc");
    memcpy(bst_node -> data, data, data_size);

    return bst_node;
}

bst_tree_t * bst_tree_create(size_t data_size,
    int( * cmp_f)(const void * ,
        const void * )) {
    bst_tree_t * bst_tree = NULL;

    bst_tree = malloc(sizeof( * bst_tree));
    DIE(bst_tree == NULL, "bst_tree malloc");

    bst_tree -> root = NULL;
    bst_tree -> data_size = data_size;
    bst_tree -> cmp = cmp_f;

    return bst_tree;
}

static void __bst_tree_insert(bst_node_t ** root, void * extra, int( * compare)(const void * key1,
    const void * key2), size_t data_size) {
    if (!( * root)) {
        ( * root) = __bst_node_create(extra, data_size);
        return;
    }

    if (compare(( * root) -> data, extra) < 0) {
        __bst_tree_insert( & (( * root) -> right), extra, compare, data_size);
    } else if (compare(( * root) -> data, extra) > 0) {
        __bst_tree_insert( & (( * root) -> left), extra, compare, data_size);
    }
}

void bst_tree_insert(bst_tree_t * bst_tree, void * data) {
    if (!bst_tree)
        printf("Program failure"), exit(EXIT_FAILURE);

    if (!bst_tree -> root) {
        bst_tree -> root = __bst_node_create(data, bst_tree -> data_size);
        return;
    } else {
        __bst_tree_insert( & bst_tree -> root, data, bst_tree -> cmp, bst_tree -> data_size);
    }
}

static bst_node_t * find_rc(void * data, bst_node_t * bst_node, int( * cmp)(const void * ,
    const void * )) {
    if (!bst_node)
        return NULL;

    if (cmp(bst_node -> data, data) == 0)
        return bst_node;

    if (cmp(bst_node -> data, data) < 0) {
        return find_rc(data, bst_node -> right, cmp);
    }
    if (cmp(bst_node -> data, data) > 0) {
        return find_rc(data, bst_node -> left, cmp);
    }

    return NULL;
}

static void free_data(bst_node_t * node) {
    if (!node)
        return;

    free(node -> data);
    node -> data = NULL;
    free(node);
    node = NULL;
}

/**
 * Helper function to remove an element from a BST
 * @bst_node: the binary search subtree's root where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 * @data_size: data size
 * @cmp: function used to compare the data contained by two nodes
 */
static void __bst_tree_remove(bst_node_t ** bst_node,
    void * data,
    int( * cmp)(const void * ,
        const void * )) {
    if (! * bst_node || !data)
        return;

    bst_node_t * my_node = find_rc(data, * bst_node, cmp);
    if (!my_node)
        return;

    // Leaf
    if (!my_node -> left && !my_node -> right) {
        int change_root = 0;
        if (cmp(my_node -> data, ( * bst_node) -> data) == 0) {
            change_root = 1;
        }
        free_data(my_node);
        if (change_root)
            ( * bst_node) = NULL;
        return;
    }

    // Only one child
    if (!my_node -> left) {
        memcpy(my_node, my_node -> right, sizeof(bst_node_t));
        if (my_node -> right) {
            free_data(my_node -> right);
        }
        my_node -> right = NULL;
        return;
    } else if (!my_node -> right) {
        memcpy(my_node, my_node -> left, sizeof(bst_node_t));
        if (my_node -> left) {
            free_data(my_node -> left);
        }
        my_node -> left = NULL;;
        return;
    }

    // Two childs
    bst_node_t * tmp = my_node -> left;
    while (tmp && tmp -> right)
        tmp = tmp -> right;

    bst_node_t * new_tmp = tmp;
    memcpy(my_node, tmp, sizeof(bst_node_t));
    free_data(new_tmp);
    if (my_node)
        free_data(my_node);
    if (new_tmp)
        free_data(new_tmp);
    if (tmp)
        free_data(tmp);
}

void bst_tree_remove(bst_tree_t * bst_tree, void * data) {
    if (!bst_tree -> root)
        return;

    __bst_tree_remove( & bst_tree -> root, data, bst_tree -> cmp);
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void __bst_tree_free(bst_node_t * bst_node, void( * free_data)(void * node)) {
    if (!bst_node)
        return;

    if (bst_node -> left)
        __bst_tree_free(bst_node -> left, free_data);
    if (bst_node -> right)
        __bst_tree_free(bst_node -> right, free_data);

    free_data(bst_node);

}

void bst_tree_free(bst_tree_t * bst_tree, void( * free_data)(void * )) {
    __bst_tree_free(bst_tree -> root, free_data);
    free(bst_tree);
}

static void
__bst_tree_print_inorder(bst_node_t * bst_node, void( * print_data)(void * )) {
    if (!bst_node)
        return;

    __bst_tree_print_inorder(bst_node -> left, print_data);
    print_data(bst_node -> data);
    __bst_tree_print_inorder(bst_node -> right, print_data);
}

void
bst_tree_print_inorder(bst_tree_t * bst_tree, void( * print_data)(void * node)) {
    if (!bst_tree -> root) {
        return;
    }

    __bst_tree_print_inorder(bst_tree -> root, print_data);
}
