#include <stdio.h>
#include <math.h>

double calculateCircleArea(double radius) {
    if (radius < 0) {
        return -1; // Indicate invalid input
    }
    return M_PI * radius * radius;
}

int main() {
    double radius1 = 5.0;
    double area1 = calculateCircleArea(radius1);
    printf("Area of circle with radius %f: %f\n", radius1, area1);

    double radius2 = 0.0;
    double area2 = calculateCircleArea(radius2);
    printf("Area of circle with radius %f: %f\n", radius2, area2);

    double radius3 = 10.0;
    double area3 = calculateCircleArea(radius3);
    printf("Area of circle with radius %f: %f\n", radius3, area3);

    double radius4 = -2;
    double area4 = calculateCircleArea(radius4);
    printf("Area of circle with radius %f: %f\n", radius4, area4);

    double radius5 = 2.5;
    double area5 = calculateCircleArea(radius5);
    printf("Area of circle with radius %f: %f\n", radius5, area5);

    return 0;
}