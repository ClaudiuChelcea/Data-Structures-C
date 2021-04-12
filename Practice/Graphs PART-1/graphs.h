#ifndef __GRAPHS__H
#define __GRAPHS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "linkedlist.h"

#define VERTICES_NR 10
#define DIE(assertion,message)									 	 \
	if(assertion) {             									 \
		printf("Error at line %d in file %s!\n",__LINE__, __FILE__); \
		perror("Error message");								 	 \
		printf("Your message: %s",message); 						 \
		exit(errno);												 \
	}
#define WHITE -1
#define GRAY 0
#define BLACK 1
													
// Adjacent matrix graph
typedef struct
{
	int ** edges;
	int vertices_number;
} matrix_graph_t;

// Adjacent list graph
typedef struct
{
	linked_list_t** neighbors;
	int vertices_number;
} list_graph_t;

/*
 *    MATRIX GRAPH
 */ 
// Create matrix graph
matrix_graph_t* matrix_graph_create(int nr_vertices);

// Add edge to matrix
void add_edge_mg(matrix_graph_t* my_matrix_graph, int graph_node1, int graph_node2);

// Check if we have edge
int has_edge_mg(matrix_graph_t* my_matrix_graph, int node_to_check1, int node_to_check2);

// Remove edge to matrix
void remove_edge_mg(matrix_graph_t* my_matrix_graph, int graph_node1, int graph_node2);

// Release the memory for the matrix graph
void release_mg(matrix_graph_t* my_matrix_graph);

// Display the graph in adjacent matrix form
void print_mg(matrix_graph_t* my_matrix_graph);

// Display the nodes in the BFS order
void bfs_mg(matrix_graph_t* my_matrix_graph, int node, int* color, int *parent);

// Display the nodes in the DFS order
void dfs_mg(matrix_graph_t* my_matrix_graph, int node,int* t_desc,int* t_fin);

// Visit a node
void visit_node(int* time_count, int* t_desc, int node, int* visited);

// Calculate shortest routes with floyd_warshall algorthm
void floyd_warshall(matrix_graph_t* my_matrix_graph);

/*
 *    LIST GRAPH
 */ 

// Create list graph
list_graph_t* list_graph_create(int nr_vertices);

// Add edge to list graph
void add_edge_lg(list_graph_t* my_list_graph, int vertix1, int vertix2);

// Add edge to list graph
int has_edge_lg(list_graph_t* my_list_graph, int vertix1, int vertix2);

// Remove edge
void remove_edge_lg(list_graph_t* my_list_graph, int edge1, int edge2);

// Get list's neighbors
linked_list_t* get_neighbors(list_graph_t* my_list_graph, int node);

// Display list graph in BFS order
void BFS_lg(list_graph_t* my_list_graph, int node);

// Display list graph in DFS order
void DFS_lg(list_graph_t* my_list_graph, int node);

// Print adjacent list
void print_lg(list_graph_t* my_list_graph);

// Release the memory for the list graph
void release_lg(list_graph_t* my_list_graph);


#endif