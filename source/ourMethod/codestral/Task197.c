#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Solution;

Solution* solutionCreate(double radius, double x_center, double y_center) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    srand(time(0));
    return obj;
}

double* solutionRandPoint(Solution* obj, int* retSize) {
    double angle = 2 * M_PI * ((double)rand() / RAND_MAX);
    double r = obj->radius * sqrt((double)rand() / RAND_MAX);
    double x = r * cos(angle) + obj->x_center;
    double y = r * sin(angle) + obj->y_center;
    *retSize = 2;
    double* result = (double*)malloc(sizeof(double) * 2);
    result[0] = x;
    result[1] = y;
    return result;
}

void solutionFree(Solution* obj) {
    free(obj);
}

int main() {
    Solution* solution = solutionCreate(1.0, 0.0, 0.0);
    int retSize;
    double* point = solutionRandPoint(solution, &retSize);
    printf("%f, %f\n", point[0], point[1]);
    free(point);
    point = solutionRandPoint(solution, &retSize);
    printf("%f, %f\n", point[0], point[1]);
    free(point);
    point = solutionRandPoint(solution, &retSize);
    printf("%f, %f\n", point[0], point[1]);
    free(point);
    solutionFree(solution);
    return 0;
}