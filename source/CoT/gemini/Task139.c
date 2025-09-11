#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calculateCircleArea(double radius) {
    if (radius < 0) {
       fprintf(stderr, "Radius cannot be negative.\n");
       exit(EXIT_FAILURE); // Or return an error value.
    }
    return M_PI * radius * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    double area = calculateCircleArea(radius);
    printf("The area of the circle is: %lf\n", area);

    // Test cases
    printf("%lf\n", calculateCircleArea(5)); // Expected: 78.53981633974483
    printf("%lf\n", calculateCircleArea(10)); // Expected: 314.1592653589793
    printf("%lf\n", calculateCircleArea(0)); // Expected: 0.0
    printf("%lf\n", calculateCircleArea(1)); // Expected: 3.141592653589793
    
    // Note: In C, handling negative input differently than C++/Java/Python due to exception mechanisms
     calculateCircleArea(-1); // This will print error message and exit due to the exit(EXIT_FAILURE) inside the function.
    return 0;
}