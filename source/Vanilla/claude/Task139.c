
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

double calculateArea(double radius) {
    return PI * radius * radius;
}

int main() {
    // Test cases
    printf("%f\\n", calculateArea(5));   // 78.539816
    printf("%f\\n", calculateArea(2.5)); // 19.634954
    printf("%f\\n", calculateArea(7));   // 153.938040
    printf("%f\\n", calculateArea(1));   // 3.141593
    printf("%f\\n", calculateArea(10));  // 314.159265
    return 0;
}
