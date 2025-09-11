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
    double angle = (double)rand() / RAND_MAX * 2 * M_PI;
    double r = obj->radius * sqrt((double)rand() / RAND_MAX);
    double x = obj->x_center + r * cos(angle);
    double y = obj->y_center + r * sin(angle);
    double* point = (double*)malloc(sizeof(double) * 2);
    point[0] = x;
    point[1] = y;
    *retSize = 2;
    return point;
}

int main() {
    srand(time(NULL));

    Task197 solution1 = {1.0, 0.0, 0.0};
    int retSize;
    double *point1 = randPoint(&solution1, &retSize);
    printf("[%f, %f]\n", point1[0], point1[1]);
        free(point1);
    double *point1_2 = randPoint(&solution1, &retSize);
    printf("[%f, %f]\n", point1_2[0], point1_2[1]);
        free(point1_2);
    double *point1_3 = randPoint(&solution1, &retSize);
    printf("[%f, %f]\n", point1_3[0], point1_3[1]);
        free(point1_3);


    Task197 solution2 = {0.000001, 0, 0};
    double *point2 = randPoint(&solution2, &retSize);
    printf("[%f, %f]\n", point2[0], point2[1]);
        free(point2);

    Task197 solution3 = {100, -50, 75.5};
    double *point3 = randPoint(&solution3, &retSize);
    printf("[%f, %f]\n", point3[0], point3[1]);
        free(point3);

    Task197 solution4 = {107.99, -107, 107};
    double *point4 = randPoint(&solution4, &retSize);
    printf("[%f, %f]\n", point4[0], point4[1]);
        free(point4);

    Task197 solution5 = {50, 0, 0};
    double *point5 = randPoint(&solution5, &retSize);
    printf("[%f, %f]\n", point5[0], point5[1]);
        free(point5);


    return 0;
}