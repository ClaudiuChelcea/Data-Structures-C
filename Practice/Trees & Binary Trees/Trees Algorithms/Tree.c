#include "Tree.h"

// Initialise a tree
struct Tree * init_tree(unsigned int data_size) {
    // Allocate memory
    struct Tree * my_tree = malloc(sizeof(tree_t));
    DIE(!my_tree, "Couldn't create tree");

    // Default values
    my_tree -> data_size = data_size;
    my_tree -> root = NULL;

    return my_tree;
}

// Create a node
struct Node * __create_node(void * data, unsigned int data_size) {
    // Check if we receive data correctly
    if (!data)
        return NULL;

    // Create new node
    struct Node * new_node = NULL;
    new_node = malloc(sizeof(struct Node));
    DIE(!new_node, "Couldn't create new node!");

    // Get data
    new_node -> data = NULL;
    new_node -> data = malloc(data_size);
    DIE(!new_node -> data, "Couldn't save data in the node!");
    memcpy(new_node -> data, data, data_size);
    new_node -> left = NULL;
    new_node -> right = NULL;

    // Return node
    return new_node;
}

// Add new node with breadth-first-search
static void __bfs_add_node(struct Node * root, void * data, unsigned int data_size) {
    // Check if we receive parameters correctly
    if (!root || !data) {
        return;
    }

    // Create queue of node addresses
    queue_t * queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(queue, & root);

    // Search all elements
    while (!q_is_empty(queue)) {
        // Get first element from queue
        struct Node * front_element = * ((struct Node ** ) q_front(queue));
        q_dequeue(queue);

        // Find the first empty child and create it
        if (!front_element -> left) {
            front_element -> left = __create_node(data, data_size);
            q_free(queue);
            return;
        } else if (!front_element -> right) {
            front_element -> right = __create_node(data, data_size);
            q_free(queue);
            return;
        }

        // If we didn't add any node, continue searching
        q_enqueue(queue, & front_element -> left);
        q_enqueue(queue, & front_element -> right);
    }
    q_free(queue);
}

// Add node while always having a full tree
void add_node(struct Tree ** my_tree, void * data) {
    // Check if the tree exists
    if (! * my_tree) {
        return;
    }

    // Add as root
    if (!( * my_tree) -> root) {
        ( * my_tree) -> root = __create_node(data, ( * my_tree) -> data_size);
        return;
    }

    // Add as node
    __bfs_add_node(( * my_tree) -> root, data, ( * my_tree) -> data_size);
}

// Release tree nodes
static void __clean_tree(struct Node * root) {
    if (!root)
        return;

    // Postorder release
    __clean_tree(root -> left);
    __clean_tree(root -> right);

    // Free each node
    free(root -> data);
    root -> data = NULL;
    free(root);
    root = NULL;
}

// Release the memory for the tree
void burn_Tree(struct Tree * my_tree) {
    // Check if the tree exists
    if (!my_tree)
        return;

    // Release nodes
    __clean_tree(my_tree -> root);

    // Release tree
    free(my_tree);
    my_tree = NULL;
}

static void __print_preorder(struct Node * root) {
    if (!root)
        return;
    printf("%d ", *(int * ) root -> data);
    __print_preorder(root -> left);
    __print_preorder(root -> right);
}

// Print tree in preorder
void print_preorder(struct Tree * my_tree) {
    if (!my_tree)
        return;

    if (my_tree -> data_size == sizeof(int)) {
        __print_preorder(my_tree -> root);
        printf("\n");
    } else {
        printf("Printing for this data type is not supported yet!\n");
    }

}

static void __print_inorder(struct Node * root) {
    if (!root)
        return;

    __print_inorder(root -> left);
    printf("%d ", *(int * ) root -> data);
    __print_inorder(root -> right);
}

// Print tree in inorder
void print_inorder(struct Tree * my_tree) {
    if (!my_tree)
        return;
    if (my_tree -> data_size == sizeof(int)) {
        __print_inorder(my_tree -> root);
        printf("\n");
    } else {
        printf("Printing for this data type is not supported yet!\n");
    }
}

static void __print_postorder(struct Node * root) {
    if (!root)
        return;

    __print_postorder(root -> left);
    __print_postorder(root -> right);
    printf("%d ", *(int * ) root -> data);

}

// Print tree in postorder
void print_postorder(struct Tree * my_tree) {
    if (!my_tree)
        return;

    if (my_tree -> data_size == sizeof(int)) {
        __print_postorder(my_tree -> root);
        printf("\n");
    } else {
        printf("Printing for this data type is not supported yet!\n");
    }
}

// Create this hierarchy by adding nodes in a way
// that we will always have a full tree
//                    0 
//             1               2
//       3 -------- 4     5 -------6
//    7 -- 8     9  
// Print the nodes in a hierarchy
void print_hierarchy() {
    printf("Created hierarchy:\n");
    printf("                 0            \n\n");
    printf("        1 -------------- 2    \n\n");
    printf("    3 ----- 4        5 ---- 6 \n\n");
    printf("  7 - 8   9 ---     ---    --- \n");
    printf("\n");
}

// Return the height of the tree
static int __find_tree_height(struct Node * root) {
    // If the root doesn't exist, the distance doesn't exist
    if (!root) {
        return -1;
    }

    // If we only have the root
    if (!root -> left && !root -> right)
        return 0;

    // Create queue of node addresses
    queue_t * queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(queue, & root);

    // Get level
    int level[MAX_NODES] = {
        0
    };

    // Search all elements
    while (!q_is_empty(queue)) {
        // Get first element from queue
        struct Node * front_element = * ((struct Node ** ) q_front(queue));
        q_dequeue(queue);

        // Continue searching
        if (front_element -> left) {
            q_enqueue(queue, & front_element -> left);
            level[ * (int * ) front_element -> left -> data] = level[ * (int * ) front_element -> data] + 1;
        }
        if (front_element -> right) {
            q_enqueue(queue, & front_element -> right);
            level[ * (int * ) front_element -> right -> data] = level[ * (int * ) front_element -> data] + 1;
        }
    }
    q_free(queue);

    int max_height = level[0];
    for (int i = 0; i < MAX_NODES; i++) {
        if (max_height < level[i])
            max_height = level[i];
    }

    return max_height;
}

// Return the height of the tree
int find_tree_height(struct Tree * my_tree) {
    if (!my_tree)
        return -1;

    return __find_tree_height(my_tree -> root);
}

// Check if all leaves are on the same level
static bool __check_leaves_level(struct Node * root) {
    // If no root, impossible
    if (!root)
        return -1;

    // If we have only the root, true
    if (!root -> left && !root -> right)
        return 1;

    // Create queue of node addresses
    queue_t * queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(queue, & root);

    // Create queue of terminal nodes
    queue_t * terminal_nodes = q_create(sizeof(int), MAX_NODES);

    // Get level
    int level[MAX_NODES] = {
        0
    };

    // Search all elements
    while (!q_is_empty(queue)) {
        // Get first element from queue
        struct Node * front_element = * ((struct Node ** ) q_front(queue));
        q_dequeue(queue);

        // Continue searching
        if (front_element -> left) {
            q_enqueue(queue, & front_element -> left);
            level[ * (int * ) front_element -> left -> data] = level[ * (int * ) front_element -> data] + 1;
        }
        if (front_element -> right) {
            q_enqueue(queue, & front_element -> right);
            level[ * (int * ) front_element -> right -> data] = level[ * (int * ) front_element -> data] + 1;
        }

        // Leaf
        if (!front_element -> left && !front_element -> right) {
            q_enqueue(terminal_nodes, front_element -> data);
        }
    }
    q_free(queue);

    // Find last level
    int max_height = level[0];
    for (int i = 0; i < MAX_NODES; i++) {
        if (max_height < level[i])
            max_height = level[i];
    }

    // Check if all the terminal nodes are on the last level
    for (int i = 0; i < terminal_nodes -> size; i++) {
        int my_node = * (int * ) q_front(terminal_nodes);
        q_dequeue(terminal_nodes);
        if (level[my_node] != max_height) {
            q_free(terminal_nodes);
            return false;
        }
    }

    q_free(terminal_nodes);
    return true;
}

// Check if all leaves are on the same level
bool check_leaves_level(struct Tree * my_tree) {
    if (!my_tree)
        return -1;

    return __check_leaves_level(my_tree -> root);
}

// Show all noted on certain level
static void __show_nodes_on_level(struct Node * root, int wanted_level) {
    if (!root)
        return;

    // If no root, impossible
    if (!root)
        return;

    // Create queue of node addresses
    queue_t * queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(queue, & root);

    // Get level
    int level[MAX_NODES] = {
        0
    };

    // Create value queue
    queue_t * values = q_create(sizeof(int), MAX_NODES);
    q_enqueue(values, root -> data);

    // Search all elements
    while (!q_is_empty(queue)) {
        // Get first element from queue
        struct Node * front_element = * ((struct Node ** ) q_front(queue));
        q_dequeue(queue);

        // Continue searching
        if (front_element -> left) {
            q_enqueue(queue, & front_element -> left);
            level[ * (int * ) front_element -> left -> data] = level[ * (int * ) front_element -> data] + 1;
            q_enqueue(values, front_element -> left -> data);
        }
        if (front_element -> right) {
            q_enqueue(queue, & front_element -> right);
            level[ * (int * ) front_element -> right -> data] = level[ * (int * ) front_element -> data] + 1;
            q_enqueue(values, front_element -> right -> data);
        }
    }

    q_free(queue);

    // Check if all the terminal nodes are on the last level
    int search_items = values -> size;
    for (int i = 0; i < search_items; i++) {
        int my_node = * (int * ) q_front(values);
        q_dequeue(values);
        if (level[my_node] == wanted_level) {
            printf("%d ", my_node);
        }
    }
    q_free(values);
}

// Show all noted on certain level
void show_nodes_on_level(struct Tree * my_tree, int wanted_level) {
    if (!my_tree)
        return;

    __show_nodes_on_level(my_tree -> root, wanted_level);

    printf("\n\n");
}

// Check if the tree is balanced
static int __check_balancer_tree(struct Node * root) {
    // If no root, impossible
    if (!root)
        return -1;

    // If we have only the root, true
    if (!root -> left && !root -> right)
        return 1;

    // Create queue of node addresses
    queue_t * queue = q_create(sizeof(void ** ), MAX_NODES);
    q_enqueue(queue, & root);

    // Create queue of terminal nodes
    queue_t * terminal_nodes = q_create(sizeof(int), MAX_NODES);

    // Get level
    int level[MAX_NODES] = {
        0
    };

    // Search all elements
    while (!q_is_empty(queue)) {
        // Get first element from queue
        struct Node * front_element = * ((struct Node ** ) q_front(queue));
        q_dequeue(queue);

        // Continue searching
        if (front_element -> left) {
            q_enqueue(queue, & front_element -> left);
            level[ * (int * ) front_element -> left -> data] = level[ * (int * ) front_element -> data] + 1;
        }
        if (front_element -> right) {
            q_enqueue(queue, & front_element -> right);
            level[ * (int * ) front_element -> right -> data] = level[ * (int * ) front_element -> data] + 1;
        }

        // Leaf
        if (!front_element -> left && !front_element -> right) {
            q_enqueue(terminal_nodes, front_element -> data);
        }
    }
    q_free(queue);

    // Find last level
    int max_height = level[0];
    for (int i = 0; i < MAX_NODES; i++) {
        if (max_height < level[i])
            max_height = level[i];
    }

    // Check if all the terminal nodes are on the last level
    // or on the penultimate level
    for (int i = 0; i < terminal_nodes -> size; i++) {
        int my_node = * (int * ) q_front(terminal_nodes);
        q_dequeue(terminal_nodes);
        if (level[my_node] != max_height && level[my_node] != max_height - 1) {
            q_free(terminal_nodes);
            return false;
        }
    }

    q_free(terminal_nodes);
    return true;
}

// Check if the tree is balanced
int check_balancer_tree(struct Tree * my_tree) {
    if (!my_tree)
        return -1;

    return __check_balancer_tree(my_tree -> root);
}
