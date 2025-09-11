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

double* Solution_randPoint(Solution* obj, int* returnSize) {
    double* result = malloc(2 * sizeof(double));
    double r = sqrt((double)rand() / RAND_MAX) * obj->radius;
    double theta = (double)rand() / RAND_MAX * 2 * M_PI;
    result[0] = obj->x_center + r * cos(theta);
    result[1] = obj->y_center + r * sin(theta);
    *returnSize = 2;
    return result;
}

void Solution_free(Solution* obj) {
    free(obj);
}

int main() {
    Solution* solution = SolutionCreate(1.0, 0.0, 0.0);
    int returnSize;
    double* point = Solution_randPoint(solution, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%lf ", point[i]);
    }
    printf("\n");
    Solution_free(solution);
    free(point);
    return 0;
}