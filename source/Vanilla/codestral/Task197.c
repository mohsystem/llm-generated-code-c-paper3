#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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
    return obj;
}

double* Solution_randPoint(Solution* obj, int* retSize) {
    double* result = malloc(sizeof(double) * 2);
    *retSize = 2;
    double r = obj->radius * sqrt((double)rand() / RAND_MAX);
    double theta = 2 * M_PI * ((double)rand() / RAND_MAX);
    double x = obj->x_center + r * cos(theta);
    double y = obj->y_center + r * sin(theta);
    result[0] = x;
    result[1] = y;
    return result;
}

int main() {
    Solution* solution = SolutionCreate(1.0, 0.0, 0.0);
    int retSize;
    double* point = Solution_randPoint(solution, &retSize);
    printf("[%lf, %lf]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%lf, %lf]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%lf, %lf]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%lf, %lf]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%lf, %lf]\n", point[0], point[1]);
    free(point);
    free(solution);
    return 0;
}