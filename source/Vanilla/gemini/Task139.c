#include <stdio.h>
#include <math.h>

double calculateArea(double radius) {
    return M_PI * radius * radius;
}

int main() {
    printf("%f\n", calculateArea(5));
    printf("%f\n", calculateArea(10));
    printf("%f\n", calculateArea(2.5));
    printf("%f\n", calculateArea(0));
    printf("%f\n", calculateArea(1));
    return 0;
}