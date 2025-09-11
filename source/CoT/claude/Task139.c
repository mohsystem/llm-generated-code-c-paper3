
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double calculateArea(double radius, int* error) {
    if (radius < 0) {
        *error = 1;
        return -1;
    }
    *error = 0;
    return PI * radius * radius;
}

int main() {
    int error;
    double result;
    
    // Test cases
    double test_cases[] = {5.0, 2.5, 0.0, 10.0, 7.5};
    for(int i = 0; i < 5; i++) {
        result = calculateArea(test_cases[i], &error);
        if (error) {
            printf("Error: Radius cannot be negative\\n");
        } else {
            printf("Area for radius %.1f: %f\\n", test_cases[i], result);
        }
    }
    
    return 0;
}
