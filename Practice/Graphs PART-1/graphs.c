#include "graphs.h"
#include "queue.h"
#include "stack.h"

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

// Display the graph in adjacent matrix form
void print_mg(matrix_graph_t* my_matrix_graph)
{
	if(!my_matrix_graph)
		return;
	printf("   ");
	for(int i=0;i<my_matrix_graph->vertices_number;i++)
		printf("%d ",i);
	printf("\n   ");
	for(int i=0;i<my_matrix_graph->vertices_number;i++)
		printf("- ");
	printf("\n");
	for(int i=0;i<my_matrix_graph->vertices_number;i++) {
		printf("%d: ",i);
		for(int j=0;j<my_matrix_graph->vertices_number;j++) {
			printf("%d ",my_matrix_graph->edges[i][j]);
		}
		printf("\n");	
	}
}

// Display the nodes in the BFS order
void bfs_mg(matrix_graph_t* my_matrix_graph, int node, int* color, int *parent)
{
	if(!my_matrix_graph)
		return;

	// Initialise values
	for(int i=0;i<VERTICES_NR;i++) {
		color[i] = WHITE;
		parent[i] = -1;
	}

	// Set the starter node
	color[node] = GRAY;
	queue_t* my_queue = q_create(sizeof(int),VERTICES_NR);
	q_enqueue(my_queue, &node);

	// Add every non-visited node to the list
	// For each node, add their neighbours too
	// Dequeue parents
	while(!q_is_empty(my_queue)) {

		// Get first node
		int front = *((int*)q_front(my_queue));
		q_dequeue(my_queue);

		// Go through the neighbours
		for(int i=0;i<VERTICES_NR;i++) {

			// If the node is a neighbor
			if(my_matrix_graph->edges[front][i] == 1) {

				// If it's not visited, visit it and add it to the queue
				if(color[i] == WHITE) {
					color[i] = GRAY;
					parent[i] = front;
					q_enqueue(my_queue, &i);
				}
			}
		}

	// Turn the node black
	color[front] = BLACK;
	printf("Node: %d.\n",front);
	}
	printf("Parent list:\n");
	for(int i=0;i<VERTICES_NR;i++)
		printf("%d ",parent[i]);
}

// Visit a node
void visit_node(int* time_count, int* t_desc, int node, int* visited)
{
	visited[node] = GRAY;
	*time_count = *time_count + 1;
	t_desc[node] = *time_count;
	printf("Node %d.\n", node);
}

// Display the nodes in the DFS order
void dfs_mg(matrix_graph_t* my_matrix_graph, int node, int* t_desc, int* t_fin)
{
	if(!my_matrix_graph)
		return;
	
	int neighbors = 0;
	
	for(int i=0;i<VERTICES_NR;i++)
		for(int j=0;j<VERTICES_NR;j++)
			if(my_matrix_graph->edges[i][j] == 1)
				neighbors++;

	int visited[VERTICES_NR];
	for(int i=0;i<neighbors/2;i++) {
		t_desc[i] = 0;
		t_fin[i] = 0;
		visited[i] = WHITE;
	}
	int time_count = 0;

	stack_t* my_stack = st_create(sizeof(int));
	visit_node(&time_count, t_desc, node, visited);
	st_push(my_stack, &node);

	while(!st_is_empty(my_stack)) {
		int search_item = *((int*)st_peek(my_stack));
		int found = -1;
		for(int i=0;i<VERTICES_NR;i++) {
			if(my_matrix_graph->edges[search_item][i] == 1 && visited[i] == WHITE) {
				found = i;
				break;
			}
		}
		if(found != -1) {
			st_push(my_stack, &found);
			visit_node(&time_count,t_desc,found,visited);
		}	
		else {
			st_pop(my_stack);
			t_fin[search_item] = ++time_count;
		}
	}

}

// Calculate shortest routes with floyd_warshall algorthm
void floyd_warshall(matrix_graph_t* my_matrix_graph)
{
	// Create copy matrix
	int distance_matrix[VERTICES_NR][VERTICES_NR];
	for(int i=0;i<VERTICES_NR;i++)
		for(int j=0;j<VERTICES_NR;j++)
			distance_matrix[i][j] = my_matrix_graph->edges[i][j];

	// For each vertix
	for(int k=0;k<VERTICES_NR;k++) {
		// Scan the whole adjacency table
		for(int i=0;i<VERTICES_NR;i++) {
			for(int j=0;j<VERTICES_NR;j++) {
				if(i == j || k == 0)
					continue;
				// If the k node is the shortest path from i to j
				if (distance_matrix[i][j] > (distance_matrix[i][k] + distance_matrix[k][j]) && (distance_matrix[i][k] + distance_matrix[k][j] != 0)) {
					distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
				}
			}
		}
	}
			
	// Display matrix
	for(int i=0;i<VERTICES_NR;i++) {
		printf("%d: ",i);
		for(int j=0;j<VERTICES_NR;j++) {
			printf("%d ",distance_matrix[i][j]);
		}
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

