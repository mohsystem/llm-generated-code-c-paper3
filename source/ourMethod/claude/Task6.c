
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

double find_uniq(const double arr[], size_t n) {
    if (arr == NULL || n < 3) {
        fprintf(stderr, "Array must contain at least 3 elements\\n");
        exit(1);
    }
    
    // Handle first three elements to determine pattern
    if (fabs(arr[0] - arr[1]) > EPSILON) {
        return fabs(arr[0] - arr[2]) <= EPSILON ? arr[1] : arr[0];
    }
    
    double common_value = arr[0];
    for (size_t i = 2; i < n; i++) {
        if (fabs(arr[i] - common_value) > EPSILON) {
            return arr[i];
        }
    }
    
    fprintf(stderr, "No unique element found\\n");
    exit(1);
}

int main() {
    // Test cases
    double arr1[] = {1, 1, 1, 2, 1, 1};
    double arr2[] = {0, 0, 0.55, 0, 0};
    double arr3[] = {1, 1, 1, 1, 1, 2};
    double arr4[] = {2, 1, 1, 1, 1, 1};
    double arr5[] = {1.0, 1.0, 1.1, 1.0};
    
    printf("%.2f\\n", find_uniq(arr1, 6)); // 2.00
    printf("%.2f\\n", find_uniq(arr2, 5)); // 0.55
    printf("%.2f\\n", find_uniq(arr3, 6)); // 2.00
    printf("%.2f\\n", find_uniq(arr4, 6)); // 2.00
    printf("%.2f\\n", find_uniq(arr5, 4)); // 1.10
    
    return 0;
}
