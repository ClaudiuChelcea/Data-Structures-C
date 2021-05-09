#include "heap.h"
#include "utils.h"
#define GARBAGE - 2324143

heap_t * heap_create(int( * cmp_f)(const team_t * ,
    const team_t * )) {
    heap_t * heap;

    heap = malloc(sizeof( * heap));
    DIE(heap == NULL, "heap malloc");

    heap -> cmp = cmp_f;
    heap -> size = 0;
    heap -> capacity = 2;
    heap -> arr = malloc(heap -> capacity * sizeof( * heap -> arr));
    DIE(heap -> arr == NULL, "heap->arr malloc");

    return heap;
}

char to_lower(char c) {
    if ('A' <= c && c <= 'Z')
        return c + 0x20;
    return c;
}

int heap_cmp_teams(const team_t * key1,
    const team_t * key2) {
    int score_diff = key2 -> score - key1 -> score;

    if (score_diff != 0)
        return score_diff;

    return heap_cmp_str_lexicographically(key1 -> name, key2 -> name);
}

int heap_cmp_str_lexicographically(const char * key1,
    const char * key2) {
    int rc, i, len;

    len = strlen(key1) < strlen(key2) ? strlen(key1) : strlen(key2);
    for (i = 0; i < len; ++i) {
        rc = to_lower(key1[i]) - to_lower(key2[i]);

        if (rc == 0)
            continue;
        return rc;
        // printf("RC: %d\n",rc);
    }

    rc = to_lower(key1[i]) - to_lower(key2[i]);
    // printf("RC: %d\n",rc);
    return rc;
}

static void __heap_insert_fix(heap_t * heap, int pos) {
    if (!heap)
        return;

    // Get our elements score
    int get_current_score = heap -> arr[pos] -> score;

    // While our score is smaller than parent's score, swap
    // so we can validate our maxheap
    int get_current_index = pos;
    while (1) {

        int get_parent_position = GO_UP(get_current_index);

        // Check if the positions exist
        if (get_parent_position < 0 || get_current_index < 0)
            break;

        int get_parent_score = heap -> arr[get_parent_position] -> score;

        // Check if we need to swap
        // else the heap is valid
        if (get_parent_score < get_current_score) {
            team_t * tmp = heap -> arr[get_parent_position];
            heap -> arr[get_parent_position] = heap -> arr[get_current_index];
            heap -> arr[get_current_index] = tmp;
            get_current_index = get_parent_position;
        } else if (get_parent_score == get_current_score && heap_cmp_str_lexicographically(heap -> arr[get_parent_position] -> name, heap -> arr[get_current_index] -> name) < 0) {
            team_t * tmp = heap -> arr[get_parent_position];
            heap -> arr[get_parent_position] = heap -> arr[get_current_index];
            heap -> arr[get_current_index] = tmp;
            get_current_index = get_parent_position;
        } else {
            break;
        }
    }
}

void heap_insert(heap_t * heap, team_t * team) {
    char * rc;
    // Allocate first empty space in the array
    heap -> arr[heap -> size] = malloc(sizeof( ** heap -> arr));
    DIE(heap -> arr[heap -> size] == NULL, "heap_insert malloc");

    // Save the name and the score in the newly allocated element
    heap -> arr[heap -> size] -> name = calloc(TEAM_NAME_LEN, sizeof( * heap -> arr[heap -> size] -> name));
    DIE(heap -> arr[heap -> size] -> name == NULL, "heap_insert name calloc");
    rc = strncpy(heap -> arr[heap -> size] -> name, team -> name, TEAM_NAME_LEN - 1);
    DIE(rc != heap -> arr[heap -> size] -> name, "heap_insert name strncpy");
    heap -> arr[heap -> size] -> score = team -> score;

    // Put the element on the correct position (push / heapify UP)
    __heap_insert_fix(heap, heap -> size);

    // Reallocate the vector if it's full
    heap -> size++;
    if (heap -> size == heap -> capacity) {
        heap -> capacity *= 2;
        heap -> arr = realloc(heap -> arr, heap -> capacity * sizeof( * heap -> arr));
        DIE(heap -> arr == NULL, "heap->arr realloc");
    }
}

team_t * heap_top(heap_t * heap) {
    if (!heap)
        return NULL;

    // Returns the node or NULL 
    return heap -> arr[0];
}

// Revalidate the maxheap
static void __heap_pop_fix(heap_t * heap, int pos) {
    if (!heap)
        return;

    int get_current_index = pos;
    int get_current_score = heap -> arr[pos] -> score;

    while (1) {
        int get_child_left_value = GARBAGE;
        if (heap -> arr[2 * get_current_index + 1]) {
            get_child_left_value = heap -> arr[2 * get_current_index + 1] -> score;
        }
        int get_child_right_value = GARBAGE;
        if (heap -> arr[2 * get_current_index + 2]) {
            get_child_right_value = heap -> arr[2 * get_current_index + 2] -> score;
        }

        int swap_with = 0;
        // Both possibilities
        if (get_child_left_value != GARBAGE && get_child_right_value != GARBAGE) {
            if (get_child_right_value > get_child_left_value)
                swap_with = -1;
            else
                swap_with = 1;
        }

        // Only right
        else if (get_child_left_value == GARBAGE && get_child_right_value != GARBAGE) {
            swap_with = 1;
        }
        // Only left
        else if (get_child_left_value != GARBAGE && get_child_right_value == GARBAGE) {
            swap_with = -1;
        }
        // No possibility
        else {
            break;
        }

        // If swap is necessary
        // otherwise break
        if (swap_with == -1) { // swap with left
            if (get_current_score > get_child_left_value) {
                team_t * tmp = heap -> arr[pos];
                heap -> arr[pos] = heap -> arr[2 * get_current_index + 1];
                heap -> arr[2 * get_current_index + 1] = tmp;
            } else
                break;
        }

        if (swap_with == 1) { // swap with right
            if (get_current_score > get_child_right_value) {
                team_t * tmp = heap -> arr[pos];
                heap -> arr[pos] = heap -> arr[2 * get_current_index + 2];
                heap -> arr[2 * get_current_index + 2] = tmp;
            } else
                break;
        }
    }
}

void heap_pop(heap_t * heap) {
    free(heap -> arr[0] -> name);
    free(heap -> arr[0]);

    heap -> arr[0] = heap -> arr[heap -> size - 1];
    heap -> size--;

    __heap_pop_fix(heap, 0);
}

int heap_empty(heap_t * heap) {
    return heap -> size <= 0;
}

void heap_free(heap_t ** heap) {
    if (! * heap)
        return;

}

// Get the maximum item by score
team_t * get_max(heap_t * heap, int * index) {
    if (!heap)
        return NULL;
    * index = 0;

    // Get biggest store
    int value = heap -> arr[0] -> score;
    for (int i = 0; i < heap -> size; i++) {
        if (value <= heap -> arr[i] -> score) {
            * index = i;
            value = heap -> arr[i] -> score;
        }
    }

    // Double check for the name sorting
    char * my_name = malloc(100 * sizeof(char));
    strcpy(my_name, heap -> arr[ * index] -> name);
    for (int i = 0; i < heap -> size; i++) {
        if (heap -> arr[i] -> score == value) {
            if (heap_cmp_str_lexicographically(heap -> arr[i] -> name, heap -> arr[ * index] -> name) < 0) {
                * index = i;
            }
        }
    }

    return heap -> arr[ * index];
}

// Remove element from the heap
void remove_max(heap_t ** heap, int index) {
    if (! * heap)
        return;

    free(( * heap) -> arr[index] -> name);
    ( * heap) -> arr[index] -> name = NULL;
    free(( * heap) -> arr[index]);
    ( * heap) -> arr[index] = NULL;

    for (int i = index; i < ( * heap) -> size - 1; i++) {
        ( * heap) -> arr[i] = ( * heap) -> arr[i + 1];
    }
    ( * heap) -> size--;
}

// Display the ranking of the teams
void show_ranking(heap_t * heap) {
    if (!heap)
        return;
    int heap_size = heap -> size;
    for (int i = 0; i < heap_size; ++i) {

        // Sort heap
        int index = 0;
        team_t * tmp = get_max(heap, & index);
        DIE(!tmp, "Couldn't find max item");
        printf("%s %d\n", tmp -> name, tmp -> score);
        remove_max( & heap, index);
    }
}
