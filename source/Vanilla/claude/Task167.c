
#include <stdio.h>
#include <math.h>

double cubeDiagonal(double volume) {
    return round(sqrt(3) * pow(volume, 1.0/3) * 100) / 100;
}

int main() {
    printf("%.2f\\n", cubeDiagonal(8)); // 3.46
    printf("%.2f\\n", cubeDiagonal(343)); // 12.12
    printf("%.2f\\n", cubeDiagonal(1157.625)); // 18.19
    printf("%.2f\\n", cubeDiagonal(27)); // 5.20
    printf("%.2f\\n", cubeDiagonal(125)); // 8.66
    return 0;
}
