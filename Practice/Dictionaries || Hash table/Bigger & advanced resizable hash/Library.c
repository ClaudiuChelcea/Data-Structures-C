#include "Library.h"

int main(void) {
    // Get the file with the books
    FILE * fptr = NULL;
    fptr = fopen("BookList.txt", "rt");
    if (!fptr) {
        fprintf(stderr, "Missing file with books!\n");
        exit(EXIT_FAILURE);
    }

    // Get the number of books
    printf("Number of books:");
    int nr_books = 0;
    fscanf(fptr, "%d", & nr_books);
    printf(" %d\n\n", nr_books);

    // Create the hash_table
    book_t ** my_library = NULL;
    my_library = malloc(HASH_SIZE * sizeof(book_t));
    if (!my_library) {
        fprintf(stderr, "Couldn't allocate space for the library!\n");
        exit(EXIT_FAILURE);
    }
    init_hash(my_library);

    // create status variables
    bool added_author = 0;
    int list_size = HASH_SIZE;
    int list_entries = 0;
    int resizes = 1;

    // Add books from file
    for (int i = 0; i < nr_books; i++) {
        // Read a book from the file
        book_t * my_book = NULL;
        my_book = get_book(fptr);
        if (!my_book) {
            fprintf(stderr, "Couldn't read book from file!\n");
            exit(EXIT_FAILURE);
        }

        // Add the book to the library
        added_author = false;
        add_Book(my_library, my_book, & list_size, & added_author);
        if (added_author == true) {
            list_entries++;
        }

        // Resize when there is only one element left
        if (list_entries != 0 && ((list_entries / HASH_SIZE) == resizes) && added_author == 1) {
            resize(my_library, & list_size, list_entries);
            resizes++;
        }
    }

    // Display initial list
    print_Table(my_library, list_size);

    // Print the status of a book
    printf("\n");
    print_status("Money: Master the game", my_library, list_size);
    print_status("Animal Farm", my_library, list_size);

    // Show the books of a certain author in our library
    char * name = NULL;
    name = malloc(NAME * sizeof(char));
    if (!name) {
        fprintf(stderr, "Couldn't get the space for the author's name!\n");
        exit(EXIT_FAILURE);
    }
    getc(fptr);
    fgets(name, NAME, fptr);
    name[strlen(name) - 1] = '\0';
    printf("Books from %s:\n", name);
    show_books(name, my_library, list_size);

    // Remove borrowed books
    remove_borrowed(my_library, list_size);
    printf("Table after removing borrowed books:\n");
    print_Table(my_library, list_size);

    // Release the memory
    fclose(fptr);
    free_memory(my_library, list_size);
    free(name);

    return 0;
}
