#include "graphs.h"
#define VERTICES_NR 10

int main(void)
{
	// Create matrix graph ( non-oriented graph )
	matrix_graph_t* my_matrix_graph = matrix_graph_create(VERTICES_NR);

	// Create list graph ( non-oriented graph )
	list_graph_t* my_list_graph = list_graph_create(VERTICES_NR);

	// Perform operations of matrix graph
	add_edge_mg(my_matrix_graph, 0, 1);
	add_edge_mg(my_matrix_graph, 0, 2);
	add_edge_mg(my_matrix_graph, 2, 3);
	add_edge_mg(my_matrix_graph, 2, 1);
	add_edge_mg(my_matrix_graph, 3, 4);
	print_mg(my_matrix_graph);
	// Perform operations of list graph


	// Release memory
	release_mg(my_matrix_graph);
	release_lg(my_list_graph);

	return 0;
}