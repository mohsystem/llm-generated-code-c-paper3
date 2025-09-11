#include<stdio.h>
#include<math.h>

double cubeDiagonal(double volume) {
    double side = cbrt(volume);
    return round(side * sqrt(3) * 100.0) / 100.0;
}

int main() {
    printf("%.2f\n", cubeDiagonal(8));         // Output: 3.46
    printf("%.2f\n", cubeDiagonal(343));        // Output: 12.12
    printf("%.2f\n", cubeDiagonal(1157.625));   // Output: 18.19
    return 0;
}