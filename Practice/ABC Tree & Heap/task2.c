#include <stdio.h>

#include <stdlib.h>

#include "heap.h"

#include "utils.h"

int main(void) {
    heap_t * heap;
    team_t * team, * tmp_team;
    int N = 0, task;

    heap = heap_create(heap_cmp_teams);

    team = malloc(sizeof( * team));
    DIE(!team, "team malloc");
    team -> name = malloc(BUFSIZ * sizeof( * team -> name));
    DIE(!team -> name, "team->name malloc");

    scanf("%d", & N);
    fflush(stdout);

    while (N--) {
        scanf("%d", & task);

        switch (task) {
        case 1:
            memset(team -> name, 0, BUFSIZ);
            scanf("%s %d", team -> name, & team -> score);
            heap_insert(heap, team);
            break;
        case 2:
            if (!heap_empty(heap)) {
                tmp_team = heap_top(heap);
                printf("%s %d\n", tmp_team -> name, tmp_team -> score);
            }
            break;
        case 3:
            if (!heap_empty(heap)) {
                heap_pop(heap);
            }
            break;
        default:
            perror("Invalid task!");
        }
    }

    // Display leaderboard
    show_ranking(heap);

    free(team -> name);
    free(team);

    return 0;
}