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
 *    OPERATIONS ON GRAPHS
 */

// Add edge to matrix
void add_edge_mg(matrix_graph_t* my_matrix_graph, int graph_node1, int graph_node2)
{
	if(!my_matrix_graph)
		return;
	my_matrix_graph->edges[graph_node1][graph_node2] = 1;
	my_matrix_graph->edges[graph_node2][graph_node1] = 1;
}

// Check if we have edge
int has_edge_me(matrix_graph_t* my_matrix_graph, int node_to_check1, int node_to_check2)
{
	if(!my_matrix_graph)
		return 0;
	if(my_matrix_graph->edges[node_to_check1][node_to_check2] == 1)
		return 1;
	return 0;	
}

// Remove edge to matrix
void remove_edge_mg(matrix_graph_t* my_matrix_graph, int graph_node1, int graph_node2)
{
	if(!my_matrix_graph)
		return;
	my_matrix_graph->edges[graph_node1][graph_node2] = 0;
	my_matrix_graph->edges[graph_node2][graph_node1] = 0;
}

// DIsplay the graph in adjacent matrix form
void print_mg(matrix_graph_t* my_matrix_graph)
{
	if(!my_matrix_graph)
		return;
	for(int i=0;i<my_matrix_graph->vertices_number;i++) {
		for(int j=0;j<my_matrix_graph->vertices_number;j++)
			printf("%d ",my_matrix_graph->edges[i][j]);
		printf("\n");	
	}
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

