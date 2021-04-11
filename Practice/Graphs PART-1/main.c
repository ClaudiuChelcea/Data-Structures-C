#include "graphs.h"
#define VERTICES_NR 10

int main(void)
{
	// Create matrix graph
	matrix_graph_t* my_matrix_graph = matrix_graph_create(VERTICES_NR);

	// Create list graph
	list_graph_t* my_list_graph = list_graph_create(VERTICES_NR);

	// Release memory
	release_mg(my_matrix_graph);
	release_lg(my_list_graph);

	return 0;
}