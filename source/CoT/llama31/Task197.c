#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double radius;
    double xCenter;
    double yCenter;
} Task197;

Task197* Task197Create(double radius, double xCenter, double yCenter) {
    Task197* obj = (Task197*)malloc(sizeof(Task197));
    obj->radius = radius;
    obj->xCenter = xCenter;
    obj->yCenter = yCenter;
    return obj;
}

double* Task197RandPoint(Task197* obj) {
    double angle = (double)rand() / RAND_MAX * 2 * M_PI;
    double rSquared = (double)rand() / RAND_MAX * obj->radius * obj->radius;
    double r = sqrt(rSquared);
    double adj = cos(angle) * r;
    double opp = sin(angle) * r;
    static double point[2];
    point[0] = obj->xCenter + adj;
    point[1] = obj->yCenter + opp;
    return point;
}

int main() {
    srand(time(NULL));
    Task197* solution = Task197Create(1.0, 0.0, 0.0);
    for (int i = 0; i < 5; i++) {
        double* point = Task197RandPoint(solution);
        printf("[%f, %f]\n", point[0], point[1]);
    }
    free(solution);
    return 0;
}