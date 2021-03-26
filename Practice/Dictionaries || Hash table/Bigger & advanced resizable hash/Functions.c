#include "Library.h"

// One-way basic hash function
unsigned int hash(char* str)
{
	unsigned int hash_value = 6731;
	while(*str) {
		hash_value += *str * 31 * 31;
		hash_value = ((((hash_value * hash_value) * *str) * 7) / 5) * *str;
		hash_value = hash_value / 3 * 7 * *str / 31 * hash_value / 3;
		hash_value += *str;
		str++;
	}
	return hash_value % HASH_SIZE;
}

// Create a book with input from stdin
book_t* get_book(FILE *fptr)
{
	// Create and allocate a new book
	book_t* my_book = NULL;
	my_book = malloc(sizeof(book_t));
	if(!my_book) {
		fprintf(stderr, "Couldn't create book!\n");
		exit(EXIT_FAILURE);
	}
	my_book->book_author = malloc((NAME + 1)* sizeof(char));
	my_book->book_title = malloc((NAME + 1) * sizeof(char));
	if(!my_book->book_author || !my_book->book_title) {
		fprintf(stderr, "Couldn't create book!\n");
		exit(EXIT_FAILURE);
	}
	
	// Get values and print them
	getc(fptr);
	printf("BOOK TITLE: ");
	fgets(my_book->book_title,NAME,fptr);
	my_book->book_title[strlen(my_book->book_title)-1] = '\0';
	printf("%s\n",my_book->book_title);
	printf("BOOK AUTHOR: ");
	fgets(my_book->book_author,NAME,fptr);
	my_book->book_author[strlen(my_book->book_author)-1] = '\0';
	printf("%s\n",my_book->book_author);
	printf("LAUNCH YEAR:");
	fscanf(fptr,"%d",&my_book->book_launch_year);
	printf(" %d\n",my_book->book_launch_year);
	printf("IS BORROWED? (0 | 1): ");
	int is_borrowed = 0;
	fscanf(fptr,"%d",&is_borrowed);
	if(is_borrowed == 0) {
		my_book->borrowed = false;
		printf("The book is not borrowed!\n");
	}
	else {
		my_book->borrowed = true;
		printf("The book is borrowed!\n");
	}
	printf("\n");

	// Return the book created with the received input
	return my_book;
}

// Initialise the hash table
void init_hash(book_t** hash_table)
{
	if(!hash_table) {
		fprintf(stderr,"No hash table to allocate!\n");
		exit(EXIT_FAILURE);
	}

	// Initialise the table's elements with NULL
	for(int i = 0; i < HASH_SIZE;i++)
		hash_table[i] = NULL;
}

// Print a certain book
void print_Book(book_t* my_book)
{
	if(!my_book) {
		fprintf(stderr,"No book to print!\n");
		return;
	}

	// Print the book's values
	printf("BOOK TITLE: ");
	printf("%s\n",my_book->book_title);
	printf("BOOK AUTHOR: ");
	printf("%s\n",my_book->book_author);
	printf("LAUNCH YEAR:");
	printf(" %d\n",my_book->book_launch_year);
	printf("IS BORROWED?: ");
	if(my_book->borrowed == 0) 
		printf("The book is not borrowed!\n\n");
	else 
		printf("The book is borrowed!\n\n");
}

// Resize the library
void resize(book_t** my_library, int *list_size, int list_entries)
{
	// Create a new table
	book_t** new_library = NULL;
	new_library = malloc((*list_size) * 2 * sizeof(book_t));
	if(!new_library) {
		fprintf(stderr,"Couldn't resize!\n");
		exit(EXIT_FAILURE);
	}

	// Copy the values from the first table
	for(int i=0;i<list_entries;i++) {
		new_library[i] = my_library[i];
	}
			
	// The rest of the table, which has no values to be copy from, is empty
	for(int i = list_entries;i<((*list_size) * 2); i++)
		new_library[i] = NULL;

	// Our library now points to the new library
	my_library = new_library;
	if(!my_library) {
		fprintf(stderr,"Couldn't resize!\n");
		exit(EXIT_FAILURE);
	}

	// Double our list's size
	(*list_size) = (*list_size) * 2;
}

// Add element to hashtable
void add_Book(book_t** hash_table, book_t* book, int* list_size, bool* added_author)
{
	// Check if we receive correct locations
	if(!hash_table)  {
		fprintf(stderr, "No library!\n");
		exit(EXIT_FAILURE);
	}
	else if(!book) {
		fprintf(stderr, "Didn't receive book!\n");
		exit(EXIT_FAILURE);
	}

	// Get the hash code for the book's author
	int index = 0;
	index = hash(book->book_author);
	
	// If the location at our hash code is empty, save our author there
	if(hash_table[index] == NULL) {
		hash_table[index] = book;
		*added_author =  true;
		return;
	}

	// If we can't find the author in that location, search in the whole table
	for(int i=0;i<(*list_size);i++) {
		if(hash_table[i] && (strcmp(hash_table[i]->book_author,book->book_author) == 0)) {
			*added_author = false;
			book->next = hash_table[i];
			hash_table[i] = book;
			return;
		}
	}

	// If it's not in the hash code location or anywhere in the list, find
	// the first empty spot, firstly checking after our hash position
	// and the from the beginning, stopping at first emtpy location 
	// aka linear probing
	for(int i = 0; i<(*list_size);i++) {
		int try = (index + i) % (*list_size);
		if(hash_table[try]==NULL) {
			hash_table[try] = book;
			*added_author = 1;
			return;	
		}
	}
	
}

// Print the hash_table
void print_Table(book_t** hash_table, int list_size)
{
	// Check if we receive the table correctly
	if(!hash_table) {
		fprintf(stderr,"No library to print from!\n");
		return;
	}

	// Print each author and all of his books
	for(int i=0;i<list_size;i++) {
		if(hash_table[i]) {
			printf("Author: %s with books: %s",hash_table[i]->book_author,hash_table[i]->book_title);
			book_t* to_print = hash_table[i]->next;
			while(to_print) {
				printf(", %s ",to_print->book_title);
				to_print = to_print->next;
			}
			printf("\n");
		}
		else
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
}

// Display the status of a book
void print_status(const char* str, book_t** hash_table, int list_size)
{
	// Check if the data is received correctly
	if(!hash_table) {
		fprintf(stderr,"No library to print from!\n");
		return;
	}
	if(!str) {
		printf("Couldn't receive book's name correctly!\n");
		return;
	}

	// Show a book's values if it is in the list or show an error message
	for(int i = 0; i < list_size; i++) {
		if(hash_table[i] != NULL) {
			if(strcmp(hash_table[i]->book_title,str)==0) {
				printf("The book \"%s\" is in the library!\n",str);
				print_Book(hash_table[i]);
				return;
			}
			book_t* new = hash_table[i]->next;
			while(new) {
				if(strcmp(new->book_title,str)==0) {
					printf("The book \"%s\" is in the library!\n",str);
					print_Book(new);
					return;
				}
				new = new->next;
			}
			
		}
	}
	printf("The book \"%s\" has not been registered yet!\n",str);
}

// Show the books of a certain author in our library
void show_books(char* str, book_t** hash_table, int list_size)
{
	// Check if the input is received correctly
	if(!hash_table) {
		fprintf(stderr,"No library to print from!\n");
		return;
	}
	if(!str) {
		printf("Couldn't receive book's name correctly!\n");
		return;
	}

	// Show all the books by printing the linked list
	for(int i = 0; i < list_size; i++) {
		if(hash_table[i] != NULL) {
			if(strcmp(hash_table[i]->book_author,str)==0) {
				print_Book(hash_table[i]);
				book_t* new = hash_table[i]->next;
				while(new) {
					print_Book(new);
					new = new->next;
				}
				return;
			}
		}
	}
	printf("We don't have any books from %s\n",str);
}

// Remove all borrowed books from the library
void remove_borrowed(book_t** hash_table, int list_size)
{
	// Check if the data is received correctly
	if(!hash_table) {
		fprintf(stderr,"No library to remove from!\n");
		return;
	}
	// Remove all the borrowed books
	for(int i = 0; i < list_size; i++) {
		if(hash_table[i] != NULL) {
			book_t* start = NULL;
			start = hash_table[i];
			book_t* prev = start;
			if(hash_table[i]->borrowed == true) {
				hash_table[i] = hash_table[i]->next;
				start = start->next;
				prev->next = NULL;
				free(prev->book_author);
				prev->book_author = NULL;
				free(prev->book_title);
				prev->book_title = NULL;
				free(prev);
				prev = NULL;
			}
			else {
				prev = start;
				start = start->next;
			}
			while(start) {
				if(start->borrowed == true) {
					if(start->next) {
						prev->next = prev->next->next;
						free(start->book_author);
						start->book_author = NULL;
						free(start->book_title);
						start->book_title = NULL;
						free(start);
						start = NULL;
						start = prev;
					}
					else {
						start->next = NULL;
						free(start->book_author);
						start->book_author = NULL;
						free(start->book_title);
						start->book_title = NULL;
						free(start);
						start = NULL;
						prev->next = NULL;
					}
				}
				else {
					prev = start;
					start = start->next;
				}
			}
		}
	}
}

// Remove all data
void free_memory(book_t** hash_table, int list_size)
{
	// Check if the data is received correctly
	if(!hash_table) {
		fprintf(stderr,"No library to remove from!\n");
		return;
	}

	// Remove all data
	for(int i = 0; i < list_size; i++) {
		if(hash_table[i] != NULL) {
			book_t* start = NULL;
			start = hash_table[i];
			book_t* prev = start;
			
			hash_table[i] = hash_table[i]->next;
			start = start->next;
			prev->next = NULL;
			free(prev->book_author);
			prev->book_author = NULL;
			free(prev->book_title);
			prev->book_title = NULL;
			free(prev);
			prev = NULL;
			
			if(!start) {
				free(hash_table[i]);
				hash_table[i] = NULL;
			}
			while(start) {
				prev = start;
				if(start->next) {
					start = start->next;
					free(prev->book_author);
					prev->book_author = NULL;
					free(prev->book_title);
					prev->book_title = NULL;
					free(prev);
					prev = NULL;
				}
				else {
					free(start->book_author);
					start->book_author = NULL;
					// free(start->book_title);
					// start->book_title = NULL;
					//free(start);
					start = NULL;
				}
			}
		}
	}

	// Remove the list itself
	free(hash_table);
	hash_table = NULL;
}
