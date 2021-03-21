#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// Create simple hash function
unsigned int hash(const char* name)
{
	if(!name) {
		fprintf(stderr,"No name to get hash from!\n");
		exit(EXIT_FAILURE);
	}
	int hash_value = 0;
	while(*name) {
		hash_value += *name;
		hash_value *= *name;
		name++;
	}
	return hash_value%TABLE_SIZE;
}

// Initialise the table
void init_table(person_t* hash_table[])
{
	if(!hash_table) {
		fprintf(stderr,"No table pointer list!\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0;i<TABLE_SIZE;i++)
		hash_table[i] = NULL;
}

// Display the table
void print_hash_table(person_t* hash_table[])
{
	printf("Hash table start.\n");
	if(!hash_table) {
		fprintf(stderr,"No table pointer list!\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0;i<TABLE_SIZE;i++) {
		if(hash_table[i] == NULL)
			printf("~~~~~~\n");
		else
			printf("%s is %d old!\n",hash_table[i]->name,hash_table[i]->age);
	}
	printf("Hash table end.\n\n");
}

// Insert person to the table
void insert_person(person_t* person, person_t* hash_table[])
{
	if(!person) {
		fprintf(stderr,"No person to insert!\n");
		exit(EXIT_FAILURE);
	}
	if(!hash_table) {
		fprintf(stderr,"No table to insert to!\n");
		exit(EXIT_FAILURE);
	}

	int index = hash(person->name);
	if(hash_table[index] == NULL)
		hash_table[index] = person;
	else
		return;
}

// Return one person by name or NULL
person_t* hash_table_find(const char* name, person_t* hash_table[])
{
	if(!name) {
		fprintf(stderr,"Name received isn't correct!\n");
		exit(EXIT_FAILURE);
	}
	if(!hash_table) {
		fprintf(stderr,"No table to find name inside!\n");
		exit(EXIT_FAILURE);
	}
	
	// Return person or NULL
	if(hash_table[hash(name)] && strcmp(hash_table[hash(name)]->name,name) ==0)
		return hash_table[hash(name)];
	else
		return NULL;
}

// Display a single person
void printPerson(person_t* person)
{
	if(!person) {
		fprintf(stderr,"This person is not in the list!\n");
		return;
	}
	else
		printf("%s is in list! His age is %d!\n",person->name,person->age);
}

// 	Remove person by name
void deletePerson(const char* name, person_t* hash_table[])
{
	if(!name) {
		fprintf(stderr,"Name received isn't correct!\n");
		exit(EXIT_FAILURE);
	}
	if(!hash_table) {
		fprintf(stderr,"No table to delete from!\n");
		exit(EXIT_FAILURE);
	}
	// Return person or NULL
	if(hash_table[hash(name)] && strcmp(hash_table[hash(name)]->name,name) ==0)
		hash_table[hash(name)] = NULL;
}
