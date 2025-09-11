// C
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double calculateCircleArea(double radius) {
    if(radius < 0) {
        fprintf(stderr, "Radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    return M_PI * radius * radius;
}

int main() {
    printf("%f\n", calculateCircleArea(5));  // Expected: 78.53981633974483
    printf("%f\n", calculateCircleArea(0));  // Expected: 0.0
    printf("%f\n", calculateCircleArea(10)); // Expected: 314.1592653589793
    printf("%f\n", calculateCircleArea(2.5)); // Expected: 19.634954084936208
    calculateCircleArea(-1); // Expected: Program will print error message and exit
    return 0;
}