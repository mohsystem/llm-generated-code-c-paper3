#include <stdio.h>
#include <math.h>

double calculateArea(double radius) {
    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return -1;
    }
    return M_PI * radius * radius;
}

int main() {
    double radius, area;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return 1;
    }
    area = calculateArea(radius);
    if (area < 0) {
        return 1;
    }
    printf("The area of the circle is: %.2f\n", area);
    return 0;
}