#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
	// Create persons
	person_t Alex = {.name = "Alex",.age = 28};
	person_t Claudiu = {.name = "Claudiu",.age = 19};
	person_t Maria =  {.name="Maria",.age = 23};

	// Create hash_table
	person_t* hash_table[TABLE_SIZE];
	init_table(hash_table);
	printf("Emtpy hash table:\n");
	print_hash_table(hash_table);

	// Insert persons in the table
	printf("Add two persons (the third is a collision)\n");
	insert_person(&Alex, hash_table);
	insert_person(&Claudiu, hash_table);
	insert_person(&Maria, hash_table);
	print_hash_table(hash_table);

	// Get one person by name
	printf("Get a person by name:\n");
	person_t* copy_person = hash_table_find("Alexa",hash_table);
	printPerson(copy_person);

	// Remove a person
	print_hash_table(hash_table);
	printf("Remove everything && add new person:\n");
	deletePerson("Alex",hash_table);
	deletePerson("Maria",hash_table);
	insert_person(&Claudiu, hash_table);
	print_hash_table(hash_table);

	return 0;
}
