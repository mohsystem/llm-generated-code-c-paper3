
#include <stdio.h>

double findUniq(const double arr[], size_t n) {
    if(arr[0] != arr[1] && arr[0] != arr[2]) return arr[0];
    if(arr[1] != arr[0] && arr[1] != arr[2]) return arr[1];
    
    double commonNum = (arr[0] == arr[1]) ? arr[0] : arr[2];
    
    for(size_t i = 2; i < n; i++) {
        if(arr[i] != commonNum) return arr[i];
    }
    return commonNum;
}

int main() {
    // Test cases
    double test1[] = {1, 1, 1, 2, 1, 1};
    double test2[] = {0, 0, 0.55, 0, 0};
    double test3[] = {3, 3, 3, 3, 1};
    double test4[] = {8, 8, 8, 7, 8};
    double test5[] = {2, 1, 2, 2, 2};
    
    printf("%f\\n", findUniq(test1, 6)); // 2.0
    printf("%f\\n", findUniq(test2, 5)); // 0.55
    printf("%f\\n", findUniq(test3, 5)); // 1.0
    printf("%f\\n", findUniq(test4, 5)); // 7.0
    printf("%f\\n", findUniq(test5, 5)); // 1.0
    
    return 0;
}
