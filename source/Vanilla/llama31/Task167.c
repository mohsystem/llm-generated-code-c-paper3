#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double side = pow(volume, 1.0 / 3.0);
    double diagonal = side * sqrt(3);
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8)); // ➞ 3.46
    printf("%.2f\n", cubeDiagonal(343)); // ➞ 12.12
    printf("%.2f\n", cubeDiagonal(1157.625)); // ➞ 18.19
    printf("%.2f\n", cubeDiagonal(27)); // ➞ 4.62
    printf("%.2f\n", cubeDiagonal(1000)); // ➞ 17.32
    return 0;
}