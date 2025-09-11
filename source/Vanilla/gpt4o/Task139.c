#include <stdio.h>
#define PI 3.141592653589793

double calculateArea(double radius) {
    return PI * radius * radius;
}

int main() {
    printf("%f\n", calculateArea(1.0)); // Test case 1
    printf("%f\n", calculateArea(2.5)); // Test case 2
    printf("%f\n", calculateArea(3.0)); // Test case 3
    printf("%f\n", calculateArea(4.4)); // Test case 4
    printf("%f\n", calculateArea(5.5)); // Test case 5
    return 0;
}