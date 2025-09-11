#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Task197;

double* randPoint(Task197* obj, int* retSize) {
    double r = sqrt((double)rand() / RAND_MAX) * obj->radius;
    double theta = (double)rand() / RAND_MAX * 2 * M_PI;
    double x = obj->x_center + r * cos(theta);
    double y = obj->y_center + r * sin(theta);
    double* point = (double*)malloc(sizeof(double) * 2);
    point[0] = x;
    point[1] = y;
    *retSize = 2;
    return point;
}

int main() {
    srand(time(NULL));
    Task197 solution = {1.0, 0.0, 0.0};
    int retSize;
    for (int i = 0; i < 5; ++i) {
        double* point = randPoint(&solution, &retSize);
        printf("[%f, %f]\n", point[0], point[1]);
        free(point);
    }
    return 0;
}