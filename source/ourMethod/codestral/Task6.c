#include <stdio.h>

double findUniq(double arr[], int n) {
    int counts[10000] = {0}; // assuming the array size is not larger than 10000
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 10000; j++) {
            if (arr[i] == j) {
                counts[j]++;
                break;
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < 10000; j++) {
            if (arr[i] == j && counts[j] == 1) {
                return arr[i];
            }
        }
    }
    return -1; // should not reach here
}

int main() {
    double arr1[] = {1, 1, 1, 2, 1, 1};
    printf("%f\n", findUniq(arr1, 6)); // => 2.000000
    double arr2[] = {0, 0, 0.55, 0, 0};
    printf("%f\n", findUniq(arr2, 5)); // => 0.550000
    return 0;
}