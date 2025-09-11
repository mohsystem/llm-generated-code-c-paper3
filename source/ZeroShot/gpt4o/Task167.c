#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double cubeDiagonal(double volume) {
    if (volume < 0) {
        fprintf(stderr, "Volume must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    double side = cbrt(volume);
    return round(sqrt(3) * side * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8)); // ➞ 3.46
    printf("%.2f\n", cubeDiagonal(343)); // ➞ 12.12
    printf("%.2f\n", cubeDiagonal(1157.625)); // ➞ 18.19
    printf("%.2f\n", cubeDiagonal(0)); // ➞ 0.0
    printf("%.2f\n", cubeDiagonal(1)); // ➞ 1.73
    return 0;
}