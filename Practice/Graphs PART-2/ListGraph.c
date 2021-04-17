#include <stdio.h>

#include <stdlib.h>

#include "ListGraph.h"

#include "utils.h"

// Check if node is in the graph
static int is_node_in_graph(int n, int nodes) {
    return n >= 0 && n < nodes;
}

// Create list graph
list_graph_t *
lg_create(int nodes) {
        int i;

        list_graph_t * g = malloc(sizeof( * g));
        DIE(!g, "malloc graph failed");

        g -> neighbors = malloc(nodes * sizeof( * g -> neighbors));
        DIE(!g -> neighbors, "malloc neighbours failed");

        for (i = 0; i != nodes; ++i)
            g -> neighbors[i] = ll_create(sizeof(int));

        g -> nodes = nodes;

        return g;
    }

// Add edge to graph
void
lg_add_edge(list_graph_t * graph, int src, int dest) {
    if (
        !graph || !graph -> neighbors ||
        !is_node_in_graph(src, graph -> nodes) ||
        !is_node_in_graph(dest, graph -> nodes)
    )
        return;

    ll_add_nth_node(graph -> neighbors[src], 0, & dest);
}

// Check if node is in the graph
static ll_node_t * find_node(linked_list_t * ll, int node, unsigned int * pos) {
    ll_node_t * crt = ll -> head;
    unsigned int i;

    for (i = 0; i != ll -> size; ++i) {
        if (node == * (int * ) crt -> data) {
            * pos = i;
            return crt;
        }

        crt = crt -> next;
    }

    return NULL;
}

// CHeck if edge is in the graph
int
lg_has_edge(list_graph_t * graph, int src, int dest) {
    unsigned int pos;

    if (
        !graph || !graph -> neighbors ||
        !is_node_in_graph(src, graph -> nodes) ||
        !is_node_in_graph(dest, graph -> nodes)
    )
        return 0;

    return find_node(graph -> neighbors[src], dest, & pos) != NULL;
}

// Get the neighbors of a node
linked_list_t *
    lg_get_neighbours(list_graph_t * graph, int node) {
        if (
            !graph || !graph -> neighbors ||
            !is_node_in_graph(node, graph -> nodes)
        )
            return NULL;

        return graph -> neighbors[node];
    }

// Remove edge from list
void
lg_remove_edge(list_graph_t * graph, int src, int dest) {
    unsigned int pos;

    if (
        !graph || !graph -> neighbors ||
        !is_node_in_graph(src, graph -> nodes) ||
        !is_node_in_graph(dest, graph -> nodes)
    )
        return;

    if (!find_node(graph -> neighbors[src], dest, & pos))
        return;

    ll_remove_nth_node(graph -> neighbors[src], pos);
}

// Free list
void
lg_free(list_graph_t * graph) {
    int i;

    for (i = 0; i != graph -> nodes; ++i)
        ll_free(graph -> neighbors + i);

    free(graph -> neighbors);
    free(graph);
}

// Print adjacent list
void
print_lg(list_graph_t * my_list_graph) {
    if (!my_list_graph)
        return;

    for (int i = 0; i < (int) my_list_graph -> nodes; i++) {
        printf("%d: ", i);
        ll_node_t * new = my_list_graph -> neighbors[i] -> head;
        if (new) {
            for (int j = 0; j < (int) my_list_graph -> neighbors[i] -> size; j++) {
                if (j < (int) my_list_graph -> neighbors[i] -> size - 1)
                    printf("%d -> ", *((int * ) new -> data));
                else
                    printf("%d", *((int * ) new -> data));
                new = new -> next;
            }
        }
        printf("\n");
    }
}