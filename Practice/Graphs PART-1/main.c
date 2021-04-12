#include "graphs.h"

int main(void) {
    // Create matrix graph ( non-oriented graph )
    matrix_graph_t * my_matrix_graph = matrix_graph_create(VERTICES_NR);

    // Create list graph ( non-oriented graph )
    list_graph_t * my_list_graph = list_graph_create(VERTICES_NR);

    // Perform operations of matrix graph
    printf("Matrix graph operations:\n");
    add_edge_mg(my_matrix_graph, 0, 1);
    add_edge_mg(my_matrix_graph, 0, 2);
    add_edge_mg(my_matrix_graph, 2, 3);
    add_edge_mg(my_matrix_graph, 2, 1);
    add_edge_mg(my_matrix_graph, 3, 4);
    print_mg(my_matrix_graph);
    printf("Check if we have an adge between node 0 and node 1: ");

    // Check for the existence of a node and delete it
    has_edge_mg(my_matrix_graph, 0, 1) == 1 ? printf("true!\n") : printf("false!\n");
    remove_edge_mg(my_matrix_graph, 0, 1);
    printf("Still?: ");
    has_edge_mg(my_matrix_graph, 0, 1) == 1 ? printf("true!\n") : printf("false!\n");
    add_edge_mg(my_matrix_graph, 0, 1);

    // BFS PRINT
    printf(" === BFS ===\n");
    int color[VERTICES_NR], parent[VERTICES_NR];
    bfs_mg(my_matrix_graph, 3, color, parent);
    printf("\n");

    // DFS PRINT
    printf(" === DFS ===\n");
    int t_desc[VERTICES_NR], t_fin[VERTICES_NR];
    dfs_mg(my_matrix_graph, 3, t_desc, t_fin);

    // FLOYD - WARSHALL PRINT
    printf("Floyd warshall:\n");
    add_edge_mg(my_matrix_graph, 1, 4);
    add_edge_mg(my_matrix_graph, 4, 5);
    floyd_warshall(my_matrix_graph);
    printf("\n");

    // Perform operations of list graph
    printf("List graph operations:\n");
    add_edge_lg(my_list_graph, 0, 2);
    add_edge_lg(my_list_graph, 0, 3);
    add_edge_lg(my_list_graph, 3, 4);
    add_edge_lg(my_list_graph, 2, 5);
    add_edge_lg(my_list_graph, 4, 5);
    print_lg(my_list_graph);

    // Check existence of certain edges
    printf("Check if we have a node between node 0 and node 4: ");
    has_edge_lg(my_list_graph, 0, 4) == 1 ? printf("true!\n") : printf("false!\n");
    printf("Add the edge and check again: ");
    add_edge_lg(my_list_graph, 0, 4);
    has_edge_lg(my_list_graph, 0, 4) == 1 ? printf("true!\n") : printf("false!\n");
    printf("Remove the edge and check again: ");
    remove_edge_lg(my_list_graph, 0, 4);
    has_edge_lg(my_list_graph, 0, 4) == 1 ? printf("true!\n") : printf("false!\n");

    // BFS PRINT
    printf(" === BFS ===\n");
    BFS_lg(my_list_graph, 4);

    // DFS PRINT
    printf(" === DFS ===\n");
    DFS_lg(my_list_graph, 3);

    // Release memory
    release_mg(my_matrix_graph);
    release_lg(my_list_graph);

    return 0;
}
