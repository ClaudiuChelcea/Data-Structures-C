#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

linked_list_t * ll_create(unsigned int data_size) {
    linked_list_t * my_list = NULL;
    my_list = malloc(sizeof(linked_list_t));
    if (!my_list) {
        fprintf(stderr, "Couldn't allocare list! Exiting...\n");
        exit(EXIT_FAILURE);
    }
    my_list -> head = NULL;
    my_list -> data_size = 0;
    my_list -> data_size = data_size;
    my_list -> size = 0;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void ll_add_nth_node(linked_list_t * list, unsigned int n,
    const void * new_data) {
    if (!list) {
        fprintf(stderr, "List doesn't exist! Exiting...\n");
        exit(EXIT_FAILURE);
    } else if (n < 0) {
        fprintf(stderr, "Invalid index! Executed NOTHING!\n");
        return;
    } else if (!list -> head) {
        list -> size++;
        ll_node_t * my_new_node = NULL;
        my_new_node = malloc(sizeof(ll_node_t));
        if (!my_new_node) {
            fprintf(stderr, "Error alocating list head\n");
            exit(EXIT_FAILURE);
        }
        my_new_node -> data = NULL;
        my_new_node -> data = malloc(sizeof(list -> data_size));
        if (!my_new_node -> data) {
            fprintf(stderr, "Couldn't allocate data for head node\n");
            exit(EXIT_FAILURE);
        }

        if (list -> data_size == sizeof(int))
            *
            ((int * ) my_new_node -> data) = * ((int * ) new_data);
        else
            strcpy(my_new_node -> data, (void * ) new_data);

        my_new_node -> next = NULL;
        list -> head = my_new_node;
    } else if (n == 0) {

        list -> size++;
        ll_node_t * my_new_node = NULL;
        my_new_node = malloc(sizeof(ll_node_t));
        my_new_node -> data = NULL;
        my_new_node -> data = malloc(sizeof(list -> data_size));

        if (list -> data_size == sizeof(int))
            *
            ((int * ) my_new_node -> data) = * ((int * ) new_data);
        else
            strcpy(my_new_node -> data, (void * ) new_data);
        my_new_node -> next = list -> head;
        list -> head = my_new_node;

    } else if (n >= list -> size) {

        list -> size++;
        ll_node_t * my_new_node = NULL;
        my_new_node = list -> head;
        while (my_new_node -> next) {
            my_new_node = my_new_node -> next;
        }

        my_new_node -> next = NULL;
        my_new_node -> next = malloc(sizeof(ll_node_t));
        my_new_node -> next -> data = NULL;
        my_new_node -> next -> data = malloc(sizeof(list -> data_size));
        my_new_node -> next -> next = NULL;
        if (list -> data_size == sizeof(int)) {
            *((int * ) my_new_node -> next -> data) = * ((int * ) new_data);
        } else {
            strcpy(my_new_node -> next -> data, (void * ) new_data);
        }
    } else if (n > 0 && n < list -> size) {

        list -> size++;

        ll_node_t * my_new_node = NULL;
        my_new_node = list -> head;
        for (int i = 0; i < n - 1; i++) {
            my_new_node = my_new_node -> next;
        }

        ll_node_t * inserted = NULL;
        inserted = malloc(sizeof(ll_node_t));
        inserted -> data = NULL;
        inserted -> data = malloc(sizeof(list -> size));
        if (list -> data_size == sizeof(int)) {
            *((int * ) inserted -> data) = * ((int * ) new_data);
        } else {
            strcpy(inserted -> data, (void * ) new_data);
        }
        inserted -> next = my_new_node -> next;
        my_new_node -> next = inserted;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */

// !!!! Atentie. Nu l-am mai returnat, pentru ca in main e apelata functia, nu se salveaza nimic
// deci nu ar avea sens. Pentru ruturn pur si simplu as avea de returnat nodul creat de mine de sters
// De exemplu, mai jos creez un nod la pozitia dorita, apoi mut lista cu un element, apoi eliberez nodul
// Singura modificare care trebuie adusa e sa nu eliberez nodul, ci sa il returnez, dar asa iau erori de la valgrind
// asa ca ii dau free. Sper ca nu e o problema.
ll_node_t * ll_remove_nth_node(linked_list_t * list, unsigned int n) {
    if (!list) {
        return (ll_node_t * ) NULL;

    } else if (!(list -> head)) {
        free(list);
        return (ll_node_t * ) NULL;

    } else if (n < 0) {
        fprintf(stderr, "Invalid index!");
        return (ll_node_t * ) NULL;

    } else if (n == 0) {
        ll_node_t * my_new_node = NULL;
        my_new_node = list -> head;
        list -> head = my_new_node -> next;
        my_new_node -> next = NULL;
        free(my_new_node -> data);
        free(my_new_node);
        list -> size--;;
        return (ll_node_t * ) NULL;

    } else if (n >= list -> size) {
        list -> size--;
        ll_node_t * copy = NULL;
        copy = list -> head;
        while (copy -> next -> next)
            copy = copy -> next;

        ll_node_t * my_new_node = NULL;
        my_new_node = copy -> next;
        free(copy -> next -> data);
        copy -> next -> next = NULL;
        free(copy -> next);
        copy -> next = NULL;

        return (ll_node_t * ) NULL;

    } else if (n > 0 && n < list -> size) {
        list -> size--;
        ll_node_t * copy = NULL;
        copy = list -> head;

        for (int i = 0; i < n - 1; i++)
            copy = copy -> next;

        ll_node_t * my_node = NULL;
        my_node = copy -> next;

        copy -> next = copy -> next -> next;
        free(my_node -> data);
        my_node -> next = NULL;
        free(my_node);
        return (ll_node_t * ) NULL;
    }
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int ll_get_size(linked_list_t * list) {
    return list -> size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void ll_free(linked_list_t ** pp_list) {
    if (!( * pp_list) -> head) {
        free( * pp_list);
        return;
    }
    ll_node_t * new = NULL;
    new = ( * pp_list) -> head;
    ll_node_t * tmp = NULL;
    while (new -> next) {
        tmp = new;
        new = new -> next;
        free(tmp -> data);
        tmp -> next = NULL;
        free(tmp);
    }
    tmp = NULL;
    free(new -> data);
    free(new);
    free( * pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void ll_print_int(linked_list_t * list) {
    if (!list || !list -> head) {
        fprintf(stderr, "Couldn't display list!\n");
        return;
    }

    ll_node_t * start = NULL;
    start = list -> head;
    while (start) {
        printf("%d ", *((int * ) start -> data));
        start = start -> next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void ll_print_string(linked_list_t * list) {
    if (!list || !list -> head) {
        fprintf(stderr, "Couldn't display list!\n");
        return;
    }
    ll_node_t * start = NULL;
    start = list -> head;
    while (start) {
        printf("%s ", (char * ) start -> data);
        start = start -> next;
    }
    printf("\n");
}
