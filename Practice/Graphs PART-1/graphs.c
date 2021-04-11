#include "graphs.h"

/*
 *  INITIALISATION
 */
// Create matrix graph
matrix_graph_t* matrix_graph_create(int nr_vertices)
{
	// Create graph
	matrix_graph_t* my_matrix_graph = NULL;
	my_matrix_graph = malloc(sizeof(matrix_graph_t));
	DIE(!my_matrix_graph, "Error creating matrix graph\n");

	// Allocate the matrix for the vertices
	my_matrix_graph->vertices_number = nr_vertices;
	my_matrix_graph->edges = malloc(nr_vertices * sizeof(int*));
	for(int i=0;i<nr_vertices;i++) {
		my_matrix_graph->edges[i] = calloc(nr_vertices, sizeof(int));
	}

	// Return the newly created matrix graph
	return my_matrix_graph;
}

// Create list graph
list_graph_t* list_graph_create(int nr_vertices)
{
	// Create graph
	list_graph_t* my_list_graph = NULL;
	my_list_graph = malloc(sizeof(list_graph_t));
	DIE(!my_list_graph, "Error creating list graph\n");
	
	// Allocate lists
	my_list_graph->vertices_number = nr_vertices;
	my_list_graph->neighbors = malloc(nr_vertices * sizeof(linked_list_t*));

	// Create each list empty
	for(int i=0;i<nr_vertices;i++) {
		my_list_graph->neighbors[i] = ll_create(sizeof(int));
	}

	// Return the newly created graph
	return my_list_graph;
}

/*
 *   RELEASING
 */ 

// Release the memory for the matrix graph
void release_mg(matrix_graph_t* my_matrix_graph)
{
	if(!my_matrix_graph)
		return;
	
	// Release each row
	for(int i=0;i<my_matrix_graph->vertices_number;i++) {
		free(my_matrix_graph->edges[i]);
	}

	// Release and null the pointer
	free(my_matrix_graph->edges);
	my_matrix_graph->edges = NULL;
	free(my_matrix_graph);
	my_matrix_graph = NULL;
}

// Release the memory for the list graph
void release_lg(list_graph_t* my_list_graph)
{
	if(!my_list_graph)
		return;

	// Release each list
	for(int i=0;i<my_list_graph->vertices_number;i++) {
		while(my_list_graph->neighbors[i]->head) 
			ll_remove_nth_node(my_list_graph->neighbors[i], 0);

		// Release the list and null it
		free(my_list_graph->neighbors[i]);
		my_list_graph->neighbors[i] = NULL;
	}

	// Release and null the pointer
	free(my_list_graph->neighbors);
	my_list_graph->neighbors = NULL;
	free(my_list_graph);
	my_list_graph = NULL;
}
