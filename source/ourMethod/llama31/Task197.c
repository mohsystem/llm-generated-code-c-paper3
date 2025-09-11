#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    double radius;
    double xCenter;
    double yCenter;
} Task197;

Task197* Task197_new(double radius, double xCenter, double yCenter) {
    Task197* solution = (Task197*)malloc(sizeof(Task197));
    solution->radius = radius;
    solution->xCenter = xCenter;
    solution->yCenter = yCenter;
    return solution;
}

void Task197_randPoint(Task197* solution, double* point) {
    double angle = 2 * M_PI * (double)rand() / RAND_MAX;
    double r = solution->radius * sqrt((double)rand() / RAND_MAX);
    point[0] = solution->xCenter + r * cos(angle);
    point[1] = solution->yCenter + r * sin(angle);
}

int main() {
    srand(time(NULL));
    Task197* solution = Task197_new(1.0, 0.0, 0.0);
    double point[2];
    for (int i = 0; i < 5; i++) {
        Task197_randPoint(solution, point);
        printf("[%f, %f]\n", point[0], point[1]);
    }
    free(solution);
    return 0;
}