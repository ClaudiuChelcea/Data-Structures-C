#ifndef __GRAPHS__H
#define __GRAPHS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "linkedlist.h"
#define DIE(assertion,message)										\
	if(assertion) {             									\
		printf("Error at line %d in file %s!\n",__LINE__, __FILE__); \
		perror("Error message");									\
		printf("Your message: %s",message); 						\
		exit(errno);												\
	}				
													
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

// Release the memory for the matrix graph
void release_mg(matrix_graph_t* my_matrix_graph);

/*
 *    LIST GRAPH
 */ 

// Create list graph
list_graph_t* list_graph_create(int nr_vertices);

// Release the memory for the list graph
void release_lg(list_graph_t* my_list_graph);


#endif