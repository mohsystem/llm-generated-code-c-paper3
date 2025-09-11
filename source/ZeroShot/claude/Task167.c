
#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    double sideLength = cbrt(volume);
    double diagonal = sqrt(3) * sideLength;
    return round(diagonal * 100.0) / 100.0;
}

int main() {
    printf("%.2f\\n", cubeDiagonal(8));
    printf("%.2f\\n", cubeDiagonal(343));
    printf("%.2f\\n", cubeDiagonal(1157.625));
    printf("%.2f\\n", cubeDiagonal(27));
    printf("%.2f\\n", cubeDiagonal(125));
    return 0;
}
