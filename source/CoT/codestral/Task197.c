#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Solution;

Solution* Solution_create(double radius, double x_center, double y_center) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    srand(time(0));
    return obj;
}

double* Solution_randPoint(Solution* obj, int* retSize) {
    double* ret = (double*)malloc(sizeof(double) * 2);
    *retSize = 2;
    double r = sqrt((double)rand() / RAND_MAX) * obj->radius;
    double theta = (double)rand() / RAND_MAX * 2 * M_PI;
    ret[0] = obj->x_center + r * cos(theta);
    ret[1] = obj->y_center + r * sin(theta);
    return ret;
}

int main() {
    Solution* solution = Solution_create(1.0, 0.0, 0.0);
    int retSize;
    double* point = Solution_randPoint(solution, &retSize);
    printf("[%.5f, %.5f]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%.5f, %.5f]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%.5f, %.5f]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%.5f, %.5f]\n", point[0], point[1]);
    point = Solution_randPoint(solution, &retSize);
    printf("[%.5f, %.5f]\n", point[0], point[1]);
    free(point);
    free(solution);
    return 0;
}