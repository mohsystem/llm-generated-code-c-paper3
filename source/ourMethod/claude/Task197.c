
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct Task197 {
    double radius;
    double xCenter;
    double yCenter;
};

// Initialize random number generator
void init_random() {
    srand(time(NULL));
}

// Get random double between 0 and 1
double rand_double() {
    return (double)rand() / RAND_MAX;
}

struct Task197* createSolution(double radius, double x_center, double y_center) {
    if (radius <= 0 || radius > 1e8) {
        return NULL;
    }
    if (fabs(x_center) > 1e7 || fabs(y_center) > 1e7) {
        return NULL;
    }
    
    struct Task197* obj = (struct Task197*)malloc(sizeof(struct Task197));
    if (obj == NULL) {
        return NULL;
    }
    
    obj->radius = radius;
    obj->xCenter = x_center;
    obj->yCenter = y_center;
    
    return obj;
}

// Returns dynamically allocated array with two doubles
double* randPoint(struct Task197* obj) {
    if (obj == NULL) {
        return NULL;
    }
    
    double* result = (double*)malloc(2 * sizeof(double));
    if (result == NULL) {
        return NULL;
    }
    
    double len = sqrt(rand_double()) * obj->radius;
    double angle = rand_double() * 2 * M_PI;
    
    result[0] = obj->xCenter + len * cos(angle);
    result[1] = obj->yCenter + len * sin(angle);
    
    return result;
}

void freeSolution(struct Task197* obj) {
    free(obj);
}

int main() {
    init_random();
    struct Task197* solution = createSolution(1.0, 0.0, 0.0);
    
    if (solution == NULL) {
        printf("Failed to create solution\\n");
        return 1;
    }
    
    // Test cases
    for (int i = 0; i < 5; i++) {
        double* point = randPoint(solution);
        if (point == NULL) {
            printf("Failed to generate random point\\n");
            freeSolution(solution);
            return 1;
        }
        
        printf("Random point %d: [%.5f, %.5f]\\n", i+1, point[0], point[1]);
        
        // Verify point is inside circle
        double distance = sqrt(point[0] * point[0] + point[1] * point[1]);
        printf("Distance from center: %.5f (should be <= 1.0)\\n", distance);
        
        free(point);
    }
    
    freeSolution(solution);
    return 0;
}
