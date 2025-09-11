#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Solution;

Solution* SolutionCreate(double radius, double x_center, double y_center) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    srand(time(NULL));
    return obj;
}

double* randPoint(Solution* obj) {
    double theta = 2 * M_PI * ((double)rand() / RAND_MAX);
    double r = sqrt((double)rand() / RAND_MAX) * obj->radius;
    double* point = (double*)malloc(2 * sizeof(double));
    point[0] = obj->x_center + r * cos(theta);
    point[1] = obj->y_center + r * sin(theta);
    return point;
}

void SolutionFree(Solution* obj) {
    free(obj);
}

int main() {
    Solution* solution = SolutionCreate(1.0, 0.0, 0.0);
    for (int i = 0; i < 5; ++i) {
        double* point = randPoint(solution);
        printf("[%f, %f]\n", point[0], point[1]);
        free(point);
    }
    SolutionFree(solution);
    return 0;
}