#include <stdio.h>
#include <math.h>

double calculateCircleArea(double radius) {
    return M_PI * radius * radius;
}

int main() {
    printf("%f\n", calculateCircleArea(1)); // π
    printf("%f\n", calculateCircleArea(2)); // 4π
    printf("%f\n", calculateCircleArea(3)); // 9π
    printf("%f\n", calculateCircleArea(4)); // 16π
    printf("%f\n", calculateCircleArea(5)); // 25π
    return 0;
}