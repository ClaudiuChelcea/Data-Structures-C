#ifndef __FCT_H
#define __FCT_H
#define TABLE_SIZE 10
#define NAME_SIZE 64

// The hash table will store persons
typedef struct person
{
	char name[NAME_SIZE];
	int age;
} person_t;

// Create simple hash function
unsigned int hash(const char* name);

// Initialise the table
void init_table(person_t* hash_table[]);

// Display the table
void print_hash_table(person_t* hash_table[]);

// Insert person to the table
void insert_person(person_t* person, person_t* hash_table[]);

// Return one person by name or NULL
person_t* hash_table_find(const char* name, person_t* hash_table[]);

// Display a single person
void printPerson(person_t* person);

// 	Remove person by name
void deletePerson(const char* name, person_t* hash_table[]);

#endif