#include <stdio.h>
#include <math.h>

double calculateCircleArea(double radius) {
    return M_PI * radius * radius;
}

int main() {
    double radii[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        printf("Area of circle with radius %.2f: %.2f\n", radii[i], calculateCircleArea(radii[i]));
    }
    return 0;
}