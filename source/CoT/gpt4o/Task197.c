#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Task197;

Task197* Task197_create(double radius, double x_center, double y_center) {
    Task197* solution = (Task197*) malloc(sizeof(Task197));
    solution->radius = radius;
    solution->x_center = x_center;
    solution->y_center = y_center;
    srand(time(0));
    return solution;
}

double* randPoint(Task197* solution) {
    double* point = (double*) malloc(2 * sizeof(double));
    double x, y;
    do {
        x = (2 * ((double) rand() / RAND_MAX) - 1) * solution->radius;
        y = (2 * ((double) rand() / RAND_MAX) - 1) * solution->radius;
    } while (x * x + y * y > solution->radius * solution->radius);
    point[0] = solution->x_center + x;
    point[1] = solution->y_center + y;
    return point;
}

int main() {
    Task197* solution = Task197_create(1.0, 0.0, 0.0);
    for (int i = 0; i < 5; ++i) {
        double* point = randPoint(solution);
        printf("[%lf, %lf]\n", point[0], point[1]);
        free(point);
    }
    free(solution);
    return 0;
}