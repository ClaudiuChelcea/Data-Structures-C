#include "binary_tree.h"
#define MAX_NODES 100

// Create node
static b_node_t *
    __b_node_create(void * data, size_t data_size) {
        b_node_t * b_node = NULL;

        b_node = malloc(sizeof( * b_node));
        DIE(b_node == NULL, "b_node malloc");

        b_node -> left = b_node -> right = NULL;

        b_node -> data = malloc(data_size);
        DIE(b_node -> data == NULL, "b_node->data malloc");
        memcpy(b_node -> data, data, data_size);

        return b_node;
    }

// Create tree
b_tree_t * b_tree_create(size_t data_size) {
    b_tree_t * new_tree = NULL;
    new_tree = malloc(sizeof(b_tree_t));
    new_tree -> data_size = data_size;
    new_tree -> root = NULL;
    return new_tree;
}

// Add created node to the first empty position by filling each level of the
// tree
void bfs_add(b_node_t ** root, void * data, b_node_t * b_node) {
    // Create queue
    queue_t * my_queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(my_queue, root);

    // Add each node to the queue
    while (!q_is_empty(my_queue)) {
        b_node_t * my_node = * (b_node_t ** ) q_front(my_queue);
        q_dequeue(my_queue);

        // If we have a node to the left, insert it
        // else add it
        if (my_node -> left) {
            q_enqueue(my_queue, & my_node -> left);
        } else {
            my_node -> left = b_node;
            q_free(my_queue);
            return;
        }

        // If we have a node to the right, insert it
        // else add it
        if (my_node -> right) {
            q_enqueue(my_queue, & my_node -> right);
        } else {
            my_node -> right = b_node;
            q_free(my_queue);
            return;
        }
    }
}

// Insert node in the tree
void b_tree_insert(b_tree_t * b_tree, void * data) {
    queue_t * q = NULL;
    b_node_t * b_node = NULL, * b_node_tmp = NULL;

    b_node = __b_node_create(data, b_tree -> data_size);

    // Insert as root
    if (!b_tree -> root) {
        b_tree -> root = b_node;
        return;
    } else {
        // Insert by filling levels
        bfs_add( & b_tree -> root, data, b_node);
    }
}

// Preorder print
static void __b_tree_print_preorder(b_node_t * b_node, void( * print_data)(void * )) {
    if (!b_node)
        return;

    printf("%d ", *(int * ) b_node -> data);
    __b_tree_print_preorder(b_node -> left, print_data);
    __b_tree_print_preorder(b_node -> right, print_data);
}

// Preorder print
void b_tree_print_preorder(b_tree_t * b_tree, void( * print_data)(void * )) {
    __b_tree_print_preorder(b_tree -> root, print_data);
    printf("\n");
}

// Inorder print
static void __b_tree_print_inorder(b_node_t * b_node, void( * print_data)(void * )) {
    if (!b_node) {
        return;
    }

    __b_tree_print_inorder(b_node -> left, print_data);
    printf("%d ", *(int * ) b_node -> data);
    __b_tree_print_inorder(b_node -> right, print_data);
}

// Inorder print
void b_tree_print_inorder(b_tree_t * b_tree, void( * print_data)(void * )) {
    __b_tree_print_inorder(b_tree -> root, print_data);
    printf("\n");
}

// Postorder print
static void __b_tree_print_postorder(b_node_t * b_node, void( * print_data)(void * )) {
    if (!b_node)
        return;
    __b_tree_print_postorder(b_node -> left, print_data);
    __b_tree_print_postorder(b_node -> right, print_data);
    printf("%d ", *(int * ) b_node -> data);

}

// Postorder print
void b_tree_print_postorder(b_tree_t * b_tree, void( * print_data)(void * )) {
    __b_tree_print_postorder(b_tree -> root, print_data);
    printf("\n");
}

// Release memory
static void __b_tree_free(b_node_t * b_node, void( * free_data)(void * )) {
    if (!b_node)
        return;

    __b_tree_free(b_node -> left, free_data);
    __b_tree_free(b_node -> right, free_data);
    free(b_node -> data);
    b_node -> data = NULL;
    free(b_node);
    b_node = NULL;
}

// Call the function to release the memory and release the tree
void b_tree_free(b_tree_t * b_tree, void( * free_data)(void * )) {
    __b_tree_free(b_tree -> root, free_data);
    free(b_tree);
}

// Check if every node is the sum of its children
static int __is_sum_of_children(b_node_t * root) {
    // If it's empty, false
    if (!root)
        return 0;

    if (root -> left == NULL && root -> right == NULL)
        return 0;

    // Create queue, add root
    queue_t * my_queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(my_queue, & root);

    // For each node, if it has children, get the sum of them
    while (!q_is_empty(my_queue)) {
        b_node_t * my_node = * (b_node_t ** ) q_front(my_queue);
        q_dequeue(my_queue);

        int sum = 0;
        int has_neighbors = 0;

        if (my_node -> left) {
            q_enqueue(my_queue, & my_node -> left);
            sum += * (int * ) my_node -> left -> data;
            has_neighbors++;
        }

        if (my_node -> right) {
            q_enqueue(my_queue, & my_node -> right);
            sum += * (int * ) my_node -> right -> data;
            has_neighbors++;

        }

        // If the sum is good or it doesn't have neighbors, continue
        // else, return false
        // in the end, if we didn't return false, return true
        if (sum == * (int * ) my_node -> data) {
            continue;
        } else if (!has_neighbors) {
            continue;
        } else {
            q_free(my_queue);
            return 0;
        }
    }

    // Release memory and return true
    q_free(my_queue);
    return 1;
}

// Call the function above
int is_sum_of_children(b_tree_t * b_tree) {
    return __is_sum_of_children(b_tree -> root);
}

// Check if the tree is full
// Attention. By the way that we are inserting in the tree, it will always be full
int check_full_tree(b_node_t * root) {
    // If it's empty, we might consider that it is full
    if (!root)
        return 1;

    if (root -> left == NULL && root -> right == NULL)
        return 1;

    // Create queue
    queue_t * my_queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(my_queue, & root);

    // While there are still nodes to visit
    while (!q_is_empty(my_queue)) {
        // Get them
        b_node_t * my_node = * (b_node_t ** ) q_front(my_queue);
        q_dequeue(my_queue);

        // If it has a left child, it must have a right child
        if (my_node -> left) {
            q_enqueue(my_queue, & my_node -> left);
            if (my_node -> right) {
                q_enqueue(my_queue, & my_node -> right);
            } else if (!my_node -> right && !my_node -> left -> left) {
                // If we are on the last level, we only need the left child
                // to exist
                continue;
            } else {
                q_free(my_queue);
                return 0;

            }
        }
    }

    // Release memory and return true
    q_free(my_queue);
    return 1;
}
