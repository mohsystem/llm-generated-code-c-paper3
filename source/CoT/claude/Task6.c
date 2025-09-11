
#include <stdio.h>
#include <stdlib.h>

double find_uniq(const double arr[], size_t n) {
    if (n < 3 || arr == NULL) {
        fprintf(stderr, "Array must contain at least 3 numbers\\n");
        exit(1);
    }
    
    // If first two numbers are equal, compare with rest
    if (arr[0] == arr[1]) {
        double common_value = arr[0];
        for (size_t i = 2; i < n; i++) {
            if (arr[i] != common_value) {
                return arr[i];
            }
        }
        return arr[2];  // Should not reach here given problem constraints
    } else {
        // First two numbers differ, return the one that's different from third
        return arr[0] == arr[2] ? arr[1] : arr[0];
    }
}

int main() {
    // Test cases
    double arr1[] = {1, 1, 1, 2, 1, 1};
    double arr2[] = {0, 0, 0.55, 0, 0};
    double arr3[] = {3, 3, 3, 3, 1};
    double arr4[] = {8, 8, 8, 7, 8};
    double arr5[] = {2, 1, 1, 1, 1};
    
    printf("%.2f\\n", find_uniq(arr1, 6));  // 2.00
    printf("%.2f\\n", find_uniq(arr2, 5));  // 0.55
    printf("%.2f\\n", find_uniq(arr3, 5));  // 1.00
    printf("%.2f\\n", find_uniq(arr4, 5));  // 7.00
    printf("%.2f\\n", find_uniq(arr5, 5));  // 2.00
    
    return 0;
}
