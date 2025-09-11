#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double xCenter;
    double yCenter;
} Task197;

Task197* Task197_new(double radius, double xCenter, double yCenter) {
    Task197* solution = malloc(sizeof(Task197));
    solution->radius = radius;
    solution->xCenter = xCenter;
    solution->yCenter = yCenter;
    return solution;
}

double* Task197_randPoint(Task197* solution) {
    double length = sqrt((double)rand() / RAND_MAX * solution->radius * solution->radius);
    double angle = 2 * M_PI * (double)rand() / RAND_MAX;
    double x = solution->xCenter + length * cos(angle);
    double y = solution->yCenter + length * sin(angle);
    static double point[2];
    point[0] = x;
    point[1] = y;
    return point;
}

int main() {
    srand(time(NULL));
    Task197* solution = Task197_new(1.0, 0.0, 0.0);
    for (int i = 0; i < 5; i++) {
        double* point = Task197_randPoint(solution);
        printf("[%f, %f]\n", point[0], point[1]);
    }
    free(solution);
    return 0;
}