#include <stdio.h>

int binaryArrayToInt(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = result * 2 + arr[i];
    }
    return result;
}

int main() {
    int arr1[] = {0, 0, 0, 1};
    int arr2[] = {0, 0, 1, 0};
    int arr3[] = {0, 1, 0, 1};
    int arr4[] = {1, 0, 0, 1};
    int arr5[] = {0, 0, 1, 0};
    printf("%d\n", binaryArrayToInt(arr1, 4)); // 1
    printf("%d\n", binaryArrayToInt(arr2, 4)); // 2
    printf("%d\n", binaryArrayToInt(arr3, 4)); // 5
    printf("%d\n", binaryArrayToInt(arr4, 4)); // 9
    printf("%d\n", binaryArrayToInt(arr5, 4)); // 2
    return 0;
}