#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// ALlocate matrix and get values from STDIN
static int ** get_matrix(const int n, const int m) {
    // Allocate the rows
    int ** dump_matrix = calloc(n, sizeof(int * ));
	DIE(!dump_matrix,"Error allocating matrix rows");
   
    // Allocate the columns
    for (int i = 0; i < n; i++) {
        dump_matrix[i] = calloc(m, sizeof(int));
        DIE(!dump_matrix[i], "Error allocating matrix columns");
        for (int j = 0; j < m; j++)
            scanf("%d", &dump_matrix[i][j]);
    }

    return dump_matrix;
}

// Try to find the element and display true / false
static void foundElement(const int my_element, int ** my_matrix,
    					 const int n, const int m)
{
	// Get the line to search for
	int my_line = 0;
    for (int i = 0; i < n; i++) {
		if(my_element <= my_matrix[i][m-1] && my_element >= my_matrix[i][0]) {
			my_line = i;
			break;
		}
	}

	// Search the whole line and display the output
	for (int j = 0; j < m; j++)
		if (my_element == my_matrix[my_line][j]) {
			printf("true\n");
			return;
		}

    printf("false\n");
}

int main(void) {
    // Get matrix dimensions
    int m = 0, n = 0;
    scanf("%d%d", &m, &n);

    // Allocate matrix and scan it
    int ** my_matrix = NULL;
    my_matrix = get_matrix(n, m);

    // Get the requested element
    int my_element = 0;
    printf("Element to search:");
    scanf("%d", &my_element);

    // Display the output
    foundElement(my_element, my_matrix, n, m);

    // Free the memory
    for (int i = 0; i < n; i++)
        free(my_matrix[i]);
    free(my_matrix);

    return 0;
}

/*
	Examples: 
	3 3
	1 2 3
	2 3 4
	3 4 5

	4 5
	1 2 3 4 5
	6 7 8 9 10
	11 12 13 14 15
	16 17 18 19 20

	~~~~~~~Valgrind~~~~~~~~~~:
	Command: valgrind --leak-check=full --show-leak-kinds=all ./matrix_exec
	Output:
	==6112== Memcheck, a memory error detector
	==6112== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
	==6112== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
	==6112== Command: ./matrix_exec
	==6112== 
	2 5
	1 2 3 4 5
	2 3 4 5 6
	Element to search:7
	false
	==6112== 
	==6112== HEAP SUMMARY:
	==6112==     in use at exit: 0 bytes in 0 blocks
	==6112==   total heap usage: 8 allocs, 8 frees, 2,128 bytes allocated
	==6112== 
	==6112== All heap blocks were freed -- no leaks are possible
	==6112== 
	==6112== For lists of detected and suppressed errors, rerun with: -s
	==6112== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/
