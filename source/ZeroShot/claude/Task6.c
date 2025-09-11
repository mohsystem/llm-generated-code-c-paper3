
#include <stdio.h>

double findUniq(const double arr[], size_t n) {
    if (arr[0] == arr[1] && arr[0] != arr[2]) return arr[2];
    if (arr[0] == arr[2] && arr[0] != arr[1]) return arr[1];
    if (arr[1] == arr[2] && arr[0] != arr[1]) return arr[0];
    
    for (size_t i = 3; i < n; i++) {
        if (arr[i] != arr[0]) return arr[i];
    }
    return arr[0];
}

int main() {
    double test1[] = {1, 1, 1, 2, 1, 1};
    double test2[] = {0, 0, 0.55, 0, 0};
    double test3[] = {3, 3, 3, 3, 1};
    double test4[] = {0, 1, 0, 0, 0};
    double test5[] = {5, 5, 5, 2.5, 5};
    
    printf("%f\\n", findUniq(test1, 6)); // 2
    printf("%f\\n", findUniq(test2, 5)); // 0.55
    printf("%f\\n", findUniq(test3, 5)); // 1
    printf("%f\\n", findUniq(test4, 5)); // 1
    printf("%f\\n", findUniq(test5, 5)); // 2.5
    
    return 0;
}
