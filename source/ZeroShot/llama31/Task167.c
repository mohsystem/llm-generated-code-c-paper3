#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double sideLength = pow(volume, 1.0 / 3.0);
    return round(sqrt(3) * sideLength * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8));
    printf("%.2f\n", cubeDiagonal(343));
    printf("%.2f\n", cubeDiagonal(1157.625));
    printf("%.2f\n", cubeDiagonal(1000));
    printf("%.2f\n", cubeDiagonal(512));
    return 0;
}