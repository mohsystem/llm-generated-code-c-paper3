
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double cubeDiagonal(double volume) {
    if (volume <= 0) {
        fprintf(stderr, "Error: Volume must be positive\\n");
        exit(1);
    }
    
    // Calculate side length from volume (volume = side^3)
    double side = cbrt(volume);
    
    // Main diagonal = side * sqrt(3)
    double diagonal = side * sqrt(3);
    
    // Round to 2 decimal places
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    // Test cases
    printf("%.2f\\n", cubeDiagonal(8));         // Should print 3.46
    printf("%.2f\\n", cubeDiagonal(343));       // Should print 12.12
    printf("%.2f\\n", cubeDiagonal(1157.625));  // Should print 18.19
    printf("%.2f\\n", cubeDiagonal(1));         // Should print 1.73
    printf("%.2f\\n", cubeDiagonal(27));        // Should print 5.20
    return 0;
}
