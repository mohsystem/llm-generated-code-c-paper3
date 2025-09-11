#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calculateArea(double radius) {
    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    return M_PI * radius * radius;
}

int main() {
    double testRadii[] = {1.0, 2.5, 0.0, -3.0, 10.0};
    for (int i = 0; i < 5; ++i) {
        double radius = testRadii[i];
        if (radius >= 0) {
            printf("Area of circle with radius %.1f is: %.2f\n", radius, calculateArea(radius));
        } else {
            fprintf(stderr, "Radius cannot be negative\n");
        }
    }
    return 0;
}