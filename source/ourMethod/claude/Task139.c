
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#define M_PI 3.14159265358979323846

double calculate_area(double radius, int* error) {
    *error = 0;
    
    if (isnan(radius)) {
        *error = 1;
        return 0;
    }
    
    if (radius < 0) {
        *error = 2;
        return 0;
    }
    
    double area = M_PI * radius * radius;
    
    if (isinf(area) || isnan(area)) {
        *error = 3;
        return 0;
    }
    
    return area;
}

int main() {
    double test_radii[] = {0, 1, 2.5, 10, 100};
    int num_tests = 5;
    int error;
    
    for (int i = 0; i < num_tests; i++) {
        double area = calculate_area(test_radii[i], &error);
        
        if (error == 0) {
            printf("Area of circle with radius %.2f = %.2f\\n", test_radii[i], area);
        } else if (error == 1) {
            printf("Error: Radius cannot be NaN\\n");
        } else if (error == 2) {
            printf("Error: Radius cannot be negative\\n");
        } else if (error == 3) {
            printf("Error: Area calculation resulted in invalid value\\n");
        }
    }
    
    return 0;
}
