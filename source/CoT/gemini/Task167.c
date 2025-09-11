#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double side = cbrt(volume);
    double diagonal = side * sqrt(3);
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8));
    printf("%.2f\n", cubeDiagonal(343));
    printf("%.2f\n", cubeDiagonal(1157.625));
    printf("%.2f\n", cubeDiagonal(1));
    printf("%.2f\n", cubeDiagonal(0));
    return 0;
}