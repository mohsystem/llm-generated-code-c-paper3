
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Task197;

Task197* create(double radius, double x_center, double y_center) {
    Task197* obj = (Task197*)malloc(sizeof(Task197));
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    return obj;
}

double* randPoint(Task197* obj) {
    double* result = (double*)malloc(2 * sizeof(double));
    double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
    double r = sqrt((double)rand() / RAND_MAX) * obj->radius;
    result[0] = obj->x_center + r * cos(angle);
    result[1] = obj->y_center + r * sin(angle);
    return result;
}

void destroy(Task197* obj) {
    free(obj);
}

int main() {
    srand(time(NULL));

    // Test cases
    Task197* solution = create(1.0, 0.0, 0.0);
    for (int i = 0; i < 5; i++) {
        double* point = randPoint(solution);
        printf("Random point %d: [%.5f, %.5f]\\n", i+1, point[0], point[1]);
        free(point);
    }

    Task197* solution2 = create(2.0, 1.0, 1.0);
    for (int i = 0; i < 5; i++) {
        double* point = randPoint(solution2);
        printf("Random point %d (shifted): [%.5f, %.5f]\\n", i+1, point[0], point[1]);
        free(point);
    }

    destroy(solution);
    destroy(solution2);
    return 0;
}
