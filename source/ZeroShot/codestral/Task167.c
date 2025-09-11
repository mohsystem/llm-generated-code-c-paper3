#include<stdio.h>
#include<math.h>

double cubeDiagonal(double volume) {
    double side = cbrt(volume);
    return round(side * sqrt(3) * 100.0) / 100.0;
}

int main() {
    printf("%f\n", cubeDiagonal(8));
    printf("%f\n", cubeDiagonal(343));
    printf("%f\n", cubeDiagonal(1157.625));
    return 0;
}