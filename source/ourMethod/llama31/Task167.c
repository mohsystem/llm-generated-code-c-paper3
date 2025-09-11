#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double sideLength = cbrt(volume);
    double diagonal = sideLength * sqrt(3);
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    printf("%f\n", cubeDiagonal(8)); // 3.46
    printf("%f\n", cubeDiagonal(343)); // 12.12
    printf("%f\n", cubeDiagonal(1157.625)); // 18.19
    printf("%f\n", cubeDiagonal(1000)); // 18.20
    printf("%f\n", cubeDiagonal(125)); // 7.28
    return 0;
}