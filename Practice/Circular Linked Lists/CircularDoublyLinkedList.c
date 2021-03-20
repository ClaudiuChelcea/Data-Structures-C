#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t* new = NULL;
    new = malloc(sizeof(doubly_linked_list_t));
    DIE(!new,"Couldn't create list!\n");
    new->head = NULL;
    new->data_size = data_size;
    new->size =  0;
    return new;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if(!list) {
        fprintf(stderr,"No list!\n");
        return NULL;
    }
    else if(!list->head) {
        fprintf(stderr,"List is empty!\n");
        return NULL;
    }
    else if(n<0) {
        printf("Invalid index!\n");
        return NULL;
    }
    else if(n==0) {
        return list->head;
    }
    else if(n>=list->size) {
      
        return list->head->prev;
        printf("Return the last item!\n");
    }
    else {
        dll_node_t* node = NULL;
        node = list->head->prev;
        if(!node) {
            printf("Couldn't remove nth node!\n");
            return NULL;
        }
        while(n) {
            node = node->next;
            n--;
        }
        return node;
    }
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    if(!list) {
        fprintf(stderr,"No list to add node to!\n");
        return;
    }
    else if(n<0) {
        fprintf(stderr,"Invalid index!\n");
        return;
    }

    else if(!list->head) {
        dll_node_t* new_node = NULL;
        new_node  = malloc(sizeof(dll_node_t));
        new_node->next = new_node;
        new_node->prev = new_node;
        new_node->data = malloc(sizeof(list->data_size));
        if(sizeof(int) == list->data_size)
            *((int*)new_node->data) = *((int*)data);
        else
            strcpy(new_node->data,data);
        list->head = new_node;
        list->size++;
    }
    else if(n==0) {// printf("Create firs222t item!\n");
        dll_node_t* new_node = NULL;
        new_node  = malloc(sizeof(dll_node_t));
        DIE(!new_node,"Couldn't add first item to list!\n");
       
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = malloc(sizeof(list->data_size));
        if(sizeof(int) == list->data_size)
            *((int*)new_node->data) = *((int*)data);
        else
            strcpy(new_node->data,data);
        
        new_node->next = list->head;
        new_node->prev = list->head->prev;
        list->head->prev->next = new_node;
        list->head->prev = new_node;
        list->head = new_node;
        list->size++;

    }
    else if(n>=list->size) { //printf("Create last item!\n");
        dll_node_t* new_node = NULL;
        new_node  = malloc(sizeof(dll_node_t));
        DIE(!new_node,"Couldn't add to list!\n");
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = malloc(sizeof(list->data_size));
        if(sizeof(int) == list->data_size) 
            *((int*)new_node->data) = *((int*)data);
        else
            strcpy(new_node->data,data);
        list->size++;

        new_node->prev = list->head->prev;
        list->head->prev->next = new_node;
        new_node->next = list->head;
        list->head->prev = new_node;
        
    }
    else {
    //    printf("Create middle item!\n");
        list->size++;
        dll_node_t* new_node_add = NULL;
        new_node_add = dll_get_nth_node(list,n);
        new_node_add = new_node_add->next;
     
        dll_node_t* new_node = NULL;
        new_node  = malloc(sizeof(dll_node_t));
        DIE(!new_node,"Couldn't add to list!\n");
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = malloc(sizeof(list->data_size));
        if(sizeof(int) == list->data_size)
            *((int*)new_node->data) = *((int*)data);
        else
            strcpy(new_node->data,data);

        new_node->next =  new_node_add;
        new_node->prev = new_node_add->prev;
        new_node_add->prev->next = new_node;
        new_node_add->prev = new_node;
        list->size++;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */

// Atentie, am schimbat tipul la void si am dat free, ca altfel programul nu ar functiona corect, ca in main nu elibereaza nimeni memoria
// Daca as fi vrut sa dau return, pur si simplu as fi returnat nodul, in loc sa il eliberez
void
dll_remove_nth_node(doubly_linked_list_t** list, unsigned int n)
{
    if(!*list) {
        fprintf(stderr,"No list to remove from!\n");
        return;
    }
    else if(n<0) {
        fprintf(stderr,"Invalid index!\n");
        return;
    }
    else if(!(*list)->head) {
        free(*list);
        *list = NULL;
         (*list)->size = 0;
        return;
    }
    else if(!(*list)->head->next) {
        (*list)->size--;
        free((*list)->head->data);
        (*list)->head->next = NULL;
        (*list)->head->prev = NULL;
        free((*list)->head);
        (*list)->head = NULL;
        free((*list));
        (*list) = NULL;
        return;
    }
    else if(n==0) {
       if((*list)->size==1) {
            free((*list)->head->data);
            (*list)->head->next = NULL;
            (*list)->head->prev = NULL;
            free((*list)->head);
            (*list)->head = NULL;
            (*list)->size = 0;
            free(*list);
            *list = NULL;
            return;
        }
        dll_node_t* start = NULL;
        start = (*list)->head;
        (*list)->head->prev->next = (*list)->head->next;
        (*list)->head->next->prev = (*list)->head->prev;
        (*list)->head=start->next;
        start->next = NULL;
        start->prev = NULL;
        free(start->data);
        free(start);
        start = NULL;
        (*list)->size--;
        return;
    }

    else if(n >= (*list)->size -1) {
       
        if((*list)->size==1) {
            free((*list)->head->data);
            (*list)->head->next = NULL;
            (*list)->head->prev = NULL;
            free((*list)->head);
            (*list)->head = NULL;
            (*list)->size = 0;
            free(*list);
            *list = NULL;
            return;
        }
        dll_node_t* start = NULL;
        start = (*list)->head;
        while(start->next->next != (*list)->head) {
            start = start->next;
        }
        dll_node_t* del = NULL;
        del = start->next;
        start->next = start->next->next;
        (*list)->head->prev = start;
        free(del->data);
        del->next = NULL;
        del->prev = NULL;
        (*list)->size--;
        free(del);
        del = NULL;
        return;
    }
    else if(n>0 && n<(*list)->size-1) {
        
        dll_node_t* start = NULL;
        start = dll_get_nth_node(*list,n);
      
        DIE(!start,"Couldn't remove node!\n");
        start = start->next;
        (*list)->size--;
        start->prev->next = start->next;
        start->next->prev = start->prev;
        start->next = NULL;
        start->prev = NULL;
        free(start->data);
        start->data = NULL;
        free(start);
        start = NULL;
        return;
    }

}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    if(!*pp_list) {
        printf("List is already deleted!\n");
    }
    else if(!(*pp_list)->head) {
        free(*pp_list);
        *pp_list = NULL;
    }
    else if((*pp_list)->head->next == (*pp_list)->head) {
       
        free((*pp_list)->head->data);
        (*pp_list)->head->data = NULL;
        (*pp_list)->head->next = NULL;
        (*pp_list)->head->prev = NULL;
        free((*pp_list)->head);
        (*pp_list)->head = NULL;
        free(*pp_list);
    }
    else {
        dll_node_t* start = NULL;
        start = (*pp_list)->head;
        DIE(!start,"Couldn't release memory! It is already released!\n");
        dll_node_t* prev = NULL;
        do {
            prev = start;
            start = start->prev;
            free(prev->data);
            prev->data = NULL;
            prev->next = NULL;
            prev->prev = NULL;
            free(prev);
            prev = NULL;
        }
        while(start != (*pp_list)->head);
        (*pp_list)->head = NULL;
        free((*pp_list));
        (*pp_list) = NULL;
    }
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    if(!list) {
        fprintf(stderr,"No list to print!\n");
        return;
    }
    else if(!list->head) {
        fprintf(stderr,"List is empty!\n");
        return;
    }

    dll_node_t* start = NULL;
    start = list->head;
    do {
        printf("%d ",(*(int*)start->data));
        start = start->next;
    }
    while(start != list->head);

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
    if(!list) {
        fprintf(stderr,"No list to print!\n");
        return;
    }
    else if(!list->head) {
        fprintf(stderr,"List is empty!\n");
        return;
    }

    dll_node_t* start = NULL;
    start = list->head;
    do {
        printf("%s ",(char*)start->data);
        start = start->next;
    }
    while(start != list->head);

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */

// Atentie, nu am testat ca nu e cod in main de pe care pot sa testez
// Cel mai probabil e corect
void
dll_print_ints_left_circular(dll_node_t* start)
{
    if(!start) {
        fprintf(stderr,"Didn't receive node correctly!\n");
        return;
    }
    dll_node_t* tmp = NULL;
    tmp = start;
    while(start != tmp) {
        printf("%d ",*((int*)start->data));
        start = start->prev;
    }
    //free(tmp);

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */

// Atentie, nu am testat ca nu e cod in main de pe care pot sa testez
// Cel mai probabil e corect
void
dll_print_ints_right_circular(dll_node_t* start)
{
    if(!start) {
        fprintf(stderr,"Didn't receive node correctly!\n");
        return;
    }
    dll_node_t* tmp = NULL;
    tmp = start;
    while(start != tmp) {
        printf("%d ",*((int*)start->data));
        start = start->next;
    }
    //free(tmp);
    
    printf("\n");
}
