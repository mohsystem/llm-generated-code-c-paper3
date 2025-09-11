#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double findArea(double r) {
    return PI * r * r;
}

int main() {
    double testCases[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        printf("Area of Circle with radius %.1f is: %.6f\n", testCases[i], findArea(testCases[i]));
    }
    return 0;
}