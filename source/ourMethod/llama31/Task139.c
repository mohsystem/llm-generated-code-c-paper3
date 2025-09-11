#include <stdio.h>
#include <math.h>

void mainFunction() {
    // Test cases
    double radii[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int size = sizeof(radii) / sizeof(radii[0]);
    for (int i = 0; i < size; i++) {
        printf("Area of circle with radius %.2f: %.2f\n", radii[i], calculateCircleArea(radii[i]));
    }
}

double calculateCircleArea(double radius) {
    // Validate input to prevent negative or zero radius
    if (radius <= 0) {
        fprintf(stderr, "Error: Radius must be a positive number\n");
        return -1.0; // Indicate error
    }
    
    // Calculate area using the formula: π * r^2
    double area = M_PI * pow(radius, 2);
    return area;
}

int main() {
    mainFunction();
    return 0;
}