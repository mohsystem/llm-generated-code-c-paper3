#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool calculateCircleArea(double radius, double *area) {
    if (radius < 0) {
        return false;
    }
    *area = M_PI * pow(radius, 2);
    return true;
}

int main() {
    double area;
    if (calculateCircleArea(5, &area)) {
        printf("%f\n", area);  // 78.53981633974483
    }
    if (calculateCircleArea(10, &area)) {
        printf("%f\n", area);  // 314.1592653589793
    }
    if (calculateCircleArea(0, &area)) {
        printf("%f\n", area);  // 0.0
    }
    if (!calculateCircleArea(-5, &area)) {
        printf("Radius cannot be negative\n");
    }
    if (calculateCircleArea(12.3, &area)) {
        printf("%f\n", area);  // 475.2040891132375
    }
    return 0;
}