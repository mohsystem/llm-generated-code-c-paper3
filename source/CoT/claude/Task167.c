
#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    // Calculate side length from volume (cube root)
    double side = cbrt(volume);
    
    // Calculate diagonal using formula: diagonal = side * sqrt(3)
    double diagonal = side * sqrt(3);
    
    // Round to 2 decimal places
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    // Test cases
    printf("%.2f\\n", cubeDiagonal(8));        // Expected: 3.46
    printf("%.2f\\n", cubeDiagonal(343));      // Expected: 12.12
    printf("%.2f\\n", cubeDiagonal(1157.625)); // Expected: 18.19
    printf("%.2f\\n", cubeDiagonal(27));       // Expected: 5.20
    printf("%.2f\\n", cubeDiagonal(125));      // Expected: 8.66
    
    return 0;
}
