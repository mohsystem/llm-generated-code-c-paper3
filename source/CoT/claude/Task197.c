
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double x_center;
    double y_center;
} Task197;

void init(Task197* obj, double radius, double x_center, double y_center) {
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    srand(time(NULL));
}

double* randPoint(Task197* obj) {
    double* result = (double*)malloc(2 * sizeof(double));
    if (result == NULL) return NULL;
    
    double len = sqrt((double)rand() / RAND_MAX) * obj->radius;
    double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
    
    result[0] = obj->x_center + len * cos(angle);
    result[1] = obj->y_center + len * sin(angle);
    
    return result;
}

int main() {
    Task197 solution;
    init(&solution, 1.0, 0.0, 0.0);
    
    // Test cases
    for (int i = 0; i < 5; i++) {
        double* point = randPoint(&solution);
        if (point != NULL) {
            printf("Random point %d: [%.5f, %.5f]\\n", i + 1, point[0], point[1]);
            free(point);
        }
    }
    
    return 0;
}
