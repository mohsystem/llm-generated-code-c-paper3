#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double sideLength = cbrt(volume);
    return round(sideLength * sqrt(3) * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8));        // 3.46
    printf("%.2f\n", cubeDiagonal(343));      // 12.12
    printf("%.2f\n", cubeDiagonal(1157.625)); // 18.19
    printf("%.2f\n", cubeDiagonal(27));       // 5.20
    printf("%.2f\n", cubeDiagonal(1));        // 1.73
    return 0;
}