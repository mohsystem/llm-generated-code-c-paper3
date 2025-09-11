#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double sideLength = pow(volume, 1.0 / 3.0);
    double diagonal = sideLength * sqrt(3);
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8));    // ➞ 3.46
    printf("%.2f\n", cubeDiagonal(343));  // ➞ 12.12
    printf("%.2f\n", cubeDiagonal(1157.625)); // ➞ 18.19
    printf("%.2f\n", cubeDiagonal(1000));  // ➞ 17.32
    printf("%.2f\n", cubeDiagonal(125));   // ➞ 5.59
    return 0;
}