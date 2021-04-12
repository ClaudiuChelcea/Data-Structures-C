#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t* ll = calloc(1, sizeof(*ll));
    DIE(!ll, "calloc list");

    ll->data_size = data_size;
    ll->size = 0;
    ll->head = NULL;

    return ll;
}

static ll_node_t* get_nth_node(linked_list_t* list, unsigned int n)
{
    unsigned int len = list->size - 1;
    unsigned int i;
    ll_node_t* node = list->head;

    n = MIN(n, len);

    for (i = 0; i < n; ++i)
        node = node->next;

    return node;
}

static ll_node_t* create_node(const void* new_data, unsigned int data_size)
{
    ll_node_t* node = calloc(1, sizeof(*node));
    DIE(!node, "calloc node");

    node->data = malloc(data_size);
    DIE(!node->data, "malloc data");

    memcpy(node->data, new_data, data_size);

    return node;
}

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    ll_node_t *new_node, *prev_node;

    if (!list)
        return;

    new_node = create_node(new_data, list->data_size);

    if (!n || !list->size) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        prev_node = get_nth_node(list, n - 1);
        new_node->next = NULL;
        prev_node->next = new_node;
    }

    list->size++;
}

void
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    /* TODO */
    ll_node_t *prev_node, *removed_node;

    if (!list || !list->size)
        return;

    if (!n) {
        removed_node = list->head;
        list->head = removed_node->next;
        removed_node->next = NULL;
        free(removed_node->data);
        removed_node->data = NULL;
        free(removed_node);
        removed_node = NULL;
    } else {
        prev_node = get_nth_node(list, n - 1);
        removed_node = prev_node->next;
        prev_node->next = removed_node->next;
        removed_node->next = NULL;
        free(removed_node->data);
        removed_node->data = NULL;
        free(removed_node);
        removed_node = NULL;
    }

    list->size--;
}

void
ll_remove_nth_node_q(linked_list_t* list, unsigned int n)
{
    /* TODO */
    ll_node_t *prev_node, *removed_node;

    if (!list || !list->size)
        return;

    if (!n) {
        removed_node = list->head;
        list->head = list->head->next;
        removed_node->next = NULL;
        free(removed_node->data);
        removed_node->data = NULL;
        free(removed_node);
        removed_node = NULL;
    } else {
        prev_node = get_nth_node(list, n - 1);
        removed_node = prev_node->next;
        prev_node->next = removed_node->next;
        removed_node->next = NULL;
        free(removed_node->data);
        removed_node->data = NULL;
        free(removed_node);
        removed_node = NULL;
    }

    list->size--;
}

unsigned int
ll_get_size(linked_list_t* list)
{
    /* TODO */
    return !list ? 0 : list->size;
}

void
ll_free(linked_list_t** pp_list)
{
    /* TODO */
    ll_node_t *node;

    if (!pp_list || !*pp_list)
        return;

    while ((*pp_list)->size) {
        ll_remove_nth_node(*pp_list, 0);
        free(node->data);
        free(node);
    }

    free (*pp_list);
    *pp_list = NULL;
}

void
ll_print_int(linked_list_t* list)
{
    /* TODO */
    ll_node_t *node = list->head;

    for (; node; node = node->next)
        printf("%d ", *(int*)node->data);
    printf("\n");
}

void
ll_print_string(linked_list_t* list)
{
    /* TODO */
    ll_node_t *node = list->head;

    for (; node; node = node->next)
        printf("%s ", (char*)node->data);
    printf("\n");
}
