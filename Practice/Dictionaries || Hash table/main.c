#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
    // Create three persons
    person_t Alex = {
        .name = "Alex",
        .age = 28,
    };
        .next = NULL
    person_t Claudiu = {
        .name = "Claudiu",
        .age = 19,
        .next = NULL
    };
    person_t Maria = {
        .name = "Maria",
        .age = 23,
        .next = NULL
    };

    // Create hash_table
    person_t * hash_table[TABLE_SIZE];
    init_table(hash_table);
    printf("Emtpy hash table:\n");
    print_hash_table(hash_table);

    // Insert persons in the table
    printf("Add three persons (the third is a collision)\n");
    insert_person( & Alex, hash_table);
    insert_person( & Claudiu, hash_table);
    insert_person( & Maria, hash_table);
    print_hash_table(hash_table);

    // Get one person by name
    printf("Get a person by name: Alexa\n");
    person_t * copy_person = hash_table_find("Alexa", hash_table);
    if (copy_person)
        printPerson(copy_person);
    else
        printf("Person is not in list!\n");

    // Remove the table and add a new person
    print_hash_table(hash_table);
    printf("Remove everything && add new person:\n");
    deletePerson("Claudiu", hash_table);
    deletePerson("Alex", hash_table);
    deletePerson("Maria", hash_table);
    insert_person( & Claudiu, hash_table);
    print_hash_table(hash_table);

    // Insert more persons by linear probing
    printf("Current table:\n");
    print_hash_table(hash_table);
    printf("Table after inserting people with linear probing:\n");
    insert_person( & Maria, hash_table);
    insert_person( & Alex, hash_table);
	insert_person( & Alex, hash_table);
    print_hash_table(hash_table);

    // Delete all persons with a certain name
    printf("Delete all persons with name \"Maria\".\n");
    while (deletePerson("Maria", hash_table)) {};
    print_hash_table(hash_table);

    // Delete the whole list
    printf("Delete the whole list:\n");
    delete_hash_table(hash_table);
    print_hash_table(hash_table);
	  
    return 0;
}
