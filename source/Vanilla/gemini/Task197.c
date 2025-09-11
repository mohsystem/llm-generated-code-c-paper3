#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Task197;

double* randPoint(Task197* obj) {
    double angle = (double)rand() / RAND_MAX * 2 * M_PI;
    double r = obj->radius * sqrt((double)rand() / RAND_MAX);
    double x = obj->x_center + r * cos(angle);
    double y = obj->y_center + r * sin(angle);

    double* point = (double*)malloc(sizeof(double) * 2);
    if (point == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    point[0] = x;
    point[1] = y;
    return point;
}



int main() {
    srand(time(NULL));

    Task197 solution = {1.0, 0.0, 0.0};
        Task197 solution2 = {10.0, 5.0, -7.5};

    for (int i = 0; i < 5; i++) {
        double* point = randPoint(&solution);
        printf("[%f, %f]\n", point[0], point[1]);
        free(point);
    }

    for (int i = 0; i < 3; i++) {
        double* point = randPoint(&solution2);
        printf("[%f, %f]\n", point[0], point[1]);
        free(point);
    }

    return 0;
}