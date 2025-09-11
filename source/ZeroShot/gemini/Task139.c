#include <stdio.h>
#include <math.h>

double calculateArea(double radius) {
    return M_PI * radius * radius;
}

int main() {
    double radius1;
    scanf("%lf", &radius1);
    printf("%.6lf\n", calculateArea(radius1));
    double radius2;
    scanf("%lf", &radius2);
    printf("%.6lf\n", calculateArea(radius2));
    double radius3;
    scanf("%lf", &radius3);
    printf("%.6lf\n", calculateArea(radius3));
    double radius4;
    scanf("%lf", &radius4);
    printf("%.6lf\n", calculateArea(radius4));
    double radius5;
    scanf("%lf", &radius5);
    printf("%.6lf\n", calculateArea(radius5));
    return 0;
}