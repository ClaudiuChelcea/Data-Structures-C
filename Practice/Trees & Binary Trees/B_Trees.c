#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct binary_tree
{
	void * data;
	struct binary_tree* left;
	struct binary_tree* right;
} node_t;

// Initialise tree
struct binary_tree* initialise_tree()
{
	struct binary_tree* new_tree = NULL;
	new_tree = malloc(sizeof(struct binary_tree));
	if(!new_tree) {
		fprintf(stderr,"Couldn't create tree!\n");
		return NULL;
	}
	new_tree->data = NULL;
	new_tree->left = NULL;
	new_tree->right = NULL;
	return new_tree;
}

// Create node
node_t* create_node(void* data, unsigned int data_size)
{
	node_t* new = initialise_tree();
	if(!new) {
		fprintf(stderr,"Couldn't create node!\n");
		return NULL;
	}
	new->data = malloc(data_size);
	memcpy(new->data,data,data_size);
	return new;
}

// Create hierarchy
void create_hierarchy(struct binary_tree* my_tree)
{
	// Add values to tree
	int value = 0;

	// Create root
	my_tree->data = malloc(sizeof(int));
	memmove(my_tree->data,&value,sizeof(int));

	// Create other nodes
	value = 5;
	my_tree->left = create_node(&value,sizeof(value));
	value = 9;
	my_tree->right = create_node(&value,sizeof(value));
	value = 7;
	my_tree->left->left = create_node(&value,sizeof(value));
	value = 3;
	my_tree->right->left = create_node(&value,sizeof(value));;
	value = 4;
	my_tree->right->right = create_node(&value,sizeof(value));

	/*
							0
					5				9
				7		NULL    3		4
	*/
}

// Insert node in balanced tree
void insert_balanced_node(struct binary_tree **my_tree, void* data)
{
	if(*my_tree == NULL || (*my_tree)->data == NULL) {
		*my_tree = create_node(data,sizeof(int));
		return;
	}
	
	// Find the position to insert to
	if(*((int*)(data)) < *((int*)((*my_tree)->data)))
		insert_balanced_node(&((*my_tree)->left),data);
	else
		insert_balanced_node(&((*my_tree)->right),data);
}

// Create hierarchy
void create_hierarchy_balanced(struct binary_tree* my_tree)
{
	srand(time(0));

	// Add 7 random elements
	for(int i=0;i<7;i++) {

		int value = rand()%15;
		insert_balanced_node(&my_tree,&value);
	}	
}

// Print the tree
void print_tree(struct binary_tree* my_tree)
{
	if(my_tree == NULL || my_tree->data == NULL)
		return;

	printf("%d ",*((int*)my_tree->data));
	// Left
	print_tree(my_tree->left);

	// Right
	print_tree(my_tree->right);
}

// Free the memory used by the tree
void clean_tree(struct binary_tree* my_tree)
{
	if(my_tree == NULL)
		return;

	// Left nodes
	clean_tree(my_tree->left);
	
	// Right nodes
	clean_tree(my_tree->right);

	// Release memory
	free(my_tree->data);
	free(my_tree);
	my_tree = NULL;
}

int main(void)
{
	// Create tree
	struct binary_tree* my_tree = NULL;
	my_tree = initialise_tree();

	// Put values in
	create_hierarchy(my_tree);

	// Print tree
	printf("Normal tree:\n");
	print_tree(my_tree);
	printf("\n");

	// Free memory
	clean_tree(my_tree);
	my_tree = NULL;

	// Create balanced tree
	my_tree = initialise_tree();

	// Populate the tree
	create_hierarchy_balanced(my_tree);

	// Print tree
	print_tree(my_tree);
}
