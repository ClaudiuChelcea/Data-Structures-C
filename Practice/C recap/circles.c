#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Create circle data-type
typedef struct {
    int x;
    int y;
    int radius;
}
circle_t;

// Calculate the distance between two coordinates
static int distance(circle_t first_circle, circle_t second_circle)
{
    return sqrt((second_circle.x - first_circle.x) * (second_circle.x - first_circle.x) +
            (second_circle.y - first_circle.y) * (second_circle.y - first_circle.y));
}

int main(void) {
    // Get the number of circles
    int circles_number = 0;
    scanf("%d", &circles_number);

    // Get the circles
    circle_t * my_circles = malloc(circles_number * sizeof(circle_t));
    if(!my_circles) {
        fprintf(stderr,"Error allocating circles array");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < circles_number; i++)
        scanf("%d%d%d", &my_circles[i].x, &my_circles[i].y, &my_circles[i].radius);

    // Count the number of intersecting circles
    int count_intersecting_circles = 0;
    for (int i = 0; i < circles_number - 1; i++) {
        for (int j = i + 1; j < circles_number; j++) {
            if (distance(my_circles[i], my_circles[j]) <= my_circles[i].radius + my_circles[j].radius) {
                count_intersecting_circles++;
            }
        }
    }

    // Display the result
    printf("%d\n", count_intersecting_circles);

    // Free the memory
    free(my_circles);

    return 0;
}
