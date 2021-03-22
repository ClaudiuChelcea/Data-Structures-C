#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// Create simple hash function
unsigned int hash(const char * name) {
    if (!name) {
        fprintf(stderr, "No name to get hash from!\n");
        exit(EXIT_FAILURE);
    }
    int hash_value = 0;
    while ( * name) {
        hash_value += * name;
        hash_value *= * name;
        name++;
    }
    return hash_value % TABLE_SIZE;
}

// Initialise the table
void init_table(person_t * hash_table[]) {
    if (!hash_table) {
        fprintf(stderr, "No table pointer list!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TABLE_SIZE; i++)
        hash_table[i] = NULL;
}

// Display the table
void print_hash_table(person_t * hash_table[]) {
    printf("Hash table start.\n");
    if (!hash_table) {
        fprintf(stderr, "No table pointer list!\n");
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL)
            printf("~~~~~~\n");
        else
            printf("%s is %d old!\n", hash_table[i] -> name, hash_table[i] -> age);
    }
    printf("Hash table end.\n\n");
}

// Insert person to the table
void insert_person(person_t * person, person_t * hash_table[]) {
    if (!person) {
        fprintf(stderr, "No person to insert!\n");
        exit(EXIT_FAILURE);
    }
    if (!hash_table) {
        fprintf(stderr, "No table to insert to!\n");
        exit(EXIT_FAILURE);
    }

    int index = hash(person -> name);
    if (hash_table[index] == NULL) {
        hash_table[index] = person;
	}
	else {
		person->next = hash_table[index];
		hash_table[index]->next = person;
	}
}

// Return one person by name or NULL
person_t * hash_table_find(const char * name, person_t * hash_table[]) {
    if (!name) {
        fprintf(stderr, "Name received isn't correct!\n");
        exit(EXIT_FAILURE);
    }
    if (!hash_table) {
        fprintf(stderr, "No table to find name inside!\n");
        exit(EXIT_FAILURE);
    }

	// Return person or NULL
	int index = hash(name);
	person_t* tmp = NULL;
	tmp = hash_table[index];
	if(!tmp) {
		return NULL;
	}
	if(!tmp->next) {
		if(strcmp(tmp->name,name)==0)
			return tmp;
		return NULL;
	}
	while(tmp) {
		if(strcmp(tmp->name,name)==0)
			return tmp;
		tmp = tmp->next;
	}
    if(!tmp)
		return NULL;
}

// Display a single person
void printPerson(person_t * person) {
    if (!person) {
        fprintf(stderr, "This person is not in the list!\n");
        return;
    } else
        printf("%s is in list! His age is %d!\n", person -> name, person -> age);
}

// 	Remove person by name
int deletePerson(const char * name, person_t * hash_table[]) {
    if (!name) {
        fprintf(stderr, "Name received isn't correct!\n");
        exit(EXIT_FAILURE);
    }
    if (!hash_table) {
        fprintf(stderr, "No table to delete from!\n");
        exit(EXIT_FAILURE);
    }
	
    // Delete person
	int index = hash(name);
	person_t* tmp = NULL;
	tmp = hash_table[index];

	// If list is empty
	if(!tmp) {
		return 0;
	}
	
	// If list has only one person
	if(!tmp->next) {
		if(strcmp(tmp->name,name)==0) {
			tmp = NULL;
			hash_table[index] = NULL;
		}
		return 1;
	}
	
	// If the first element is the right one
	person_t* prev = NULL;
	if(strcmp(tmp->name,name)==0) {
		prev = tmp;
		tmp = tmp->next;
		prev->next = NULL;
		prev = NULL;
		hash_table[index] = tmp;
		return 1;
	}

	// If we have more persons and it's not the first one
	while(tmp) {
		prev = tmp;
		tmp = tmp->next;
		if(prev->next && strcmp(prev->next->name,name)==0) {
			prev->next->next = NULL;
			prev->next = prev->next->next;
			tmp = tmp->next;
		}
		else if(prev && strcmp(prev->name,name)==0) {
			prev = NULL;
			tmp = NULL;
		}
		
	}
	
	return 1;
}

// Clean the whole list
void delete_hash_table(person_t * hash_table[])
{
	if(!hash_table) {
		fprintf(stderr,"Hash table is already empty!\n");
		return;
	}

	for(int i=0;i<TABLE_SIZE;i++) {
		hash_table[i] = NULL;
	}
}
