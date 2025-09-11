#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double RAD, XC, YC;
} Task197;

Task197* Task197Create(double radius, double x_center, double y_center) {
    Task197* obj = (Task197*)malloc(sizeof(Task197));
    obj->RAD = radius;
    obj->XC = x_center;
    obj->YC = y_center;
    return obj;
}

void Task197RandPoint(Task197* obj, double* point) {
    double ang = (double)rand() / RAND_MAX * 2 * M_PI;
    double hyp = sqrt((double)rand() / RAND_MAX) * obj->RAD;
    point[0] = obj->XC + cos(ang) * hyp;
    point[1] = obj->YC + sin(ang) * hyp;
}

int main() {
    srand(time(NULL));
    Task197* solution = Task197Create(1.0, 0.0, 0.0);
    double point[2];
    for (int i = 0; i < 5; i++) {
        Task197RandPoint(solution, point);
        printf("[%f, %f]\n", point[0], point[1]);
    }
    free(solution);
    return 0;
}