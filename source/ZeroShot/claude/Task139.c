
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double calculateArea(double radius) {
    if(radius < 0) {
        return -1; // Error case since C doesn't have exception handling
    }
    return PI * radius * radius;
}

int main() {
    // Test cases
    double result;
    
    result = calculateArea(5);
    if(result >= 0) printf("%.6f\\n", result);    // 78.539816
    
    result = calculateArea(2.5);
    if(result >= 0) printf("%.6f\\n", result);    // 19.634954
    
    result = calculateArea(0);
    if(result >= 0) printf("%.6f\\n", result);    // 0.000000
    
    result = calculateArea(10);
    if(result >= 0) printf("%.6f\\n", result);    // 314.159265
    
    result = calculateArea(7.5);
    if(result >= 0) printf("%.6f\\n", result);    // 176.714587
    
    return 0;
}
