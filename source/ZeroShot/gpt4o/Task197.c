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
    Solution* obj = (Solution*) malloc(sizeof(Solution));
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    srand(time(NULL));
    return obj;
}

double* randPoint(Solution* obj, double* result) {
    double angle = 2 * M_PI * ((double) rand() / RAND_MAX);
    double distance = sqrt((double) rand() / RAND_MAX) * obj->radius;
    result[0] = obj->x_center + distance * cos(angle);
    result[1] = obj->y_center + distance * sin(angle);
    return result;
}

void SolutionFree(Solution* obj) {
    if (obj) free(obj);
}

int main() {
    Solution* solution = SolutionCreate(1.0, 0.0, 0.0);
    double result[2];
    for (int i = 0; i < 5; i++) {
        randPoint(solution, result);
        printf("[%f, %f]\n", result[0], result[1]);
    }
    SolutionFree(solution);
    return 0;
}