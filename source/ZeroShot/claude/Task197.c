
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double radius;
    double xCenter;
    double yCenter;
} Task197;

Task197* createSolution(double radius, double x_center, double y_center) {
    Task197* obj = (Task197*)malloc(sizeof(Task197));
    obj->radius = radius;
    obj->xCenter = x_center;
    obj->yCenter = y_center;
    srand(time(NULL));
    return obj;
}

double* randPoint(Task197* obj) {
    double* result = (double*)malloc(2 * sizeof(double));
    double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
    double r = sqrt((double)rand() / RAND_MAX) * obj->radius;
    result[0] = obj->xCenter + r * cos(angle);
    result[1] = obj->yCenter + r * sin(angle);
    return result;
}

void freeSolution(Task197* obj) {
    free(obj);
}

int main() {
    Task197* solution = createSolution(1.0, 0.0, 0.0);
    
    // Test cases
    for (int i = 0; i < 5; i++) {
        double* point = randPoint(solution);
        printf("Random point %d: [%.5f, %.5f]\\n", i+1, point[0], point[1]);
        
        // Verify point is within circle
        double distance = sqrt(pow(point[0] - 0.0, 2) + pow(point[1] - 0.0, 2));
        printf("Distance from center: %.5f (should be <= 1.0)\\n", distance);
        
        free(point);
    }
    
    freeSolution(solution);
    return 0;
}
