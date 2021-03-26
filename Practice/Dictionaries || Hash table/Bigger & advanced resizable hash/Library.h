#ifndef __LIB_H__
#define __LIB_H__
#define HASH_SIZE 5
#define NAME 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool {
    false = 0, true = 1
}
bool;

// Create the book structure
typedef struct Book {
    char * book_title;
    char * book_author;
    unsigned int book_launch_year;
    // If not borrowed, then it is on the shelf
    bool borrowed;
    struct Book * next;
}
book_t;

// One-way basic hash function
unsigned int hash(char * str);

// Create a book with input from stdin
book_t * get_book(FILE * fptr);

// Initialise the hash table
void init_hash(book_t ** hash_table);

// Print a certain book
void print_Book(book_t * my_book);

// Resize the library
void resize(book_t ** my_library, int * list_size, int list_entries);

// Add element to hashtable
void add_Book(book_t ** hash_table, book_t * book, int * list_size, bool * added_author);

// Print the hash_table
void print_Table(book_t ** hash_table, int list_size);

// Display the status of a book
void print_status(const char * str, book_t ** hash_table, int list_size);

// Show the books of a certain author in our library
void show_books(char * str, book_t ** hash_table, int list_size);

// Remove all borrowed books from the library
void remove_borrowed(book_t ** hash_table, int list_size);

// Remove all data
void free_memory(book_t ** hash_table, int list_size);

#endif
