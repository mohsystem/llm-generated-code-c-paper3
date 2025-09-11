#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double side = cbrt(volume);
    double diagonal = side * sqrt(3);
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8));        // 3.46
    printf("%.2f\n", cubeDiagonal(343));      // 12.12
    printf("%.2f\n", cubeDiagonal(1157.625)); // 18.19
    printf("%.2f\n", cubeDiagonal(1));        // 1.73
    printf("%.2f\n", cubeDiagonal(27));       // 5.20
    return 0;
}