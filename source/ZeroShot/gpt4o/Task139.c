#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calculateCircleArea(double radius) {
    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    return M_PI * radius * radius;
}

int main() {
    printf("%lf\n", calculateCircleArea(5));  // Test case 1
    printf("%lf\n", calculateCircleArea(0));  // Test case 2
    printf("%lf\n", calculateCircleArea(2.5)); // Test case 3
    printf("%lf\n", calculateCircleArea(10)); // Test case 4
    printf("%lf\n", calculateCircleArea(7.5)); // Test case 5
    return 0;
}