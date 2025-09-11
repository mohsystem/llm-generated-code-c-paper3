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
    static double point[2];
    double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
    double length = sqrt((double)rand() / RAND_MAX) * obj->radius;
    point[0] = obj->x_center + length * cos(angle);
    point[1] = obj->y_center + length * sin(angle);
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
    }
    SolutionFree(solution);
    return 0;
}