
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Maximum number of Solution instances for memory management
#define MAX_SOLUTIONS 100

typedef struct {
    double radius;
    double x_center;
    double y_center;
    int initialized;
} Solution;

// Global array to manage Solution instances with bounds checking
static Solution solutions[MAX_SOLUTIONS];
static int solution_count = 0;
static int random_initialized = 0;

// Initialize random number generator once
// Uses time-based seed for non-deterministic behavior
static void init_random(void) {
    if (!random_initialized) {
        srand((unsigned int)time(NULL));
        random_initialized = 1;
    }
}

// Generate random double in [0, 1) with validation
// Avoids division by zero and ensures valid range
static double rand_double(void) {
    // Use multiple rand() calls for better distribution on some platforms
    double r = (double)rand() / ((double)RAND_MAX + 1.0);
    // Clamp to ensure we stay in valid range
    if (r < 0.0) r = 0.0;
    if (r >= 1.0) r = 0.999999;
    return r;
}

// Create and initialize Solution with input validation
// Returns index on success, -1 on failure
int Solution_create(double radius, double x_center, double y_center) {
    init_random();
    
    // Validate radius is positive and within constraints
    if (radius <= 0.0 || radius > 1e8) {
        fprintf(stderr, "Error: Radius must be positive and <= 1e8\\n");
        return -1;
    }
    
    // Validate center coordinates are within constraints
    if (x_center < -1e7 || x_center > 1e7 || y_center < -1e7 || y_center > 1e7) {
        fprintf(stderr, "Error: Center coordinates must be in range [-1e7, 1e7]\\n");
        return -1;
    }
    
    // Check bounds to prevent buffer overflow
    if (solution_count >= MAX_SOLUTIONS) {
        fprintf(stderr, "Error: Maximum number of solutions reached\\n");
        return -1;
    }
    
    // Initialize Solution structure with validated inputs
    int idx = solution_count++;
    solutions[idx].radius = radius;
    solutions[idx].x_center = x_center;
    solutions[idx].y_center = y_center;
    solutions[idx].initialized = 1;
    
    return idx;
}

// Generate uniform random point inside circle
// Uses sqrt for radial distance to ensure uniform area distribution
// Returns 0 on success, -1 on error
int Solution_randPoint(int idx, double* x_out, double* y_out) {
    // Validate index to prevent out-of-bounds access
    if (idx < 0 || idx >= solution_count || !solutions[idx].initialized) {
        fprintf(stderr, "Error: Invalid solution index\\n");
        return -1;
    }
    
    // Validate output pointers to prevent null pointer dereference
    if (x_out == NULL || y_out == NULL) {
        fprintf(stderr, "Error: Output pointers cannot be NULL\\n");
        return -1;
    }
    
    Solution* sol = &solutions[idx];
    
    // Generate uniform random angle [0, 2*PI)
    double angle = rand_double() * 2.0 * M_PI;
    
    // Generate uniform random radius using sqrt for uniform area distribution
    double r = sqrt(rand_double()) * sol->radius;
    
    // Convert polar to Cartesian coordinates
    *x_out = sol->x_center + r * cos(angle);
    *y_out = sol->y_center + r * sin(angle);
    
    return 0;
}

// Clean up Solution instance
void Solution_destroy(int idx) {
    // Validate index before cleanup
    if (idx >= 0 && idx < solution_count && solutions[idx].initialized) {
        // Clear sensitive data using memset_s if available, otherwise memset
        #ifdef __STDC_LIB_EXT1__
        memset_s(&solutions[idx], sizeof(Solution), 0, sizeof(Solution));
        #else
        memset(&solutions[idx], 0, sizeof(Solution));
        #endif
        solutions[idx].initialized = 0;
    }
}

int main(void) {
    double x, y;
    int result;
    
    // Test case 1: Unit circle at origin
    printf("Test 1: Circle with radius=1.0, center=(0.0, 0.0)\\n");
    int sol1 = Solution_create(1.0, 0.0, 0.0);
    if (sol1 >= 0) {
        for (int i = 0; i < 5; i++) {
            result = Solution_randPoint(sol1, &x, &y);
            if (result == 0) {
                printf("[%.5f, %.5f]\\n", x, y);
            }
        }
    }
    
    // Test case 2: Larger circle at origin
    printf("\\nTest 2: Circle with radius=10.0, center=(0.0, 0.0)\\n");
    int sol2 = Solution_create(10.0, 0.0, 0.0);
    if (sol2 >= 0) {
        for (int i = 0; i < 5; i++) {
            result = Solution_randPoint(sol2, &x, &y);
            if (result == 0) {
                printf("[%.5f, %.5f]\\n", x, y);
            }
        }
    }
    
    // Test case 3: Circle at offset position
    printf("\\nTest 3: Circle with radius=5.0, center=(3.0, 4.0)\\n");
    int sol3 = Solution_create(5.0, 3.0, 4.0);
    if (sol3 >= 0) {
        for (int i = 0; i < 5; i++) {
            result = Solution_randPoint(sol3, &x, &y);
            if (result == 0) {
                printf("[%.5f, %.5f]\\n", x, y);
            }
        }
    }
    
    // Test case 4: Very small circle
    printf("\\nTest 4: Circle with radius=0.1, center=(0.0, 0.0)\\n");
    int sol4 = Solution_create(0.1, 0.0, 0.0);
    if (sol4 >= 0) {
        for (int i = 0; i < 5; i++) {
            result = Solution_randPoint(sol4, &x, &y);
            if (result == 0) {
                printf("[%.5f, %.5f]\\n", x, y);
            }
        }
    }
    
    // Test case 5: Circle at negative coordinates
    printf("\\nTest 5: Circle with radius=2.0, center=(-5.0, -5.0)\\n");
    int sol5 = Solution_create(2.0, -5.0, -5.0);
    if (sol5 >= 0) {
        for (int i = 0; i < 5; i++) {
            result = Solution_randPoint(sol5, &x, &y);
            if (result == 0) {
                printf("[%.5f, %.5f]\\n", x, y);
            }
        }
    }
    
    // Clean up all solutions
    Solution_destroy(sol1);
    Solution_destroy(sol2);
    Solution_destroy(sol3);
    Solution_destroy(sol4);
    Solution_destroy(sol5);
    
    return 0;
}
