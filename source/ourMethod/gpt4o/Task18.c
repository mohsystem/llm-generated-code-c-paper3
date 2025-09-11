#include <stdio.h>

int binaryArrayToInt(const int* binaryArray, int length) {
    int result = 0;
    for (int i = 0; i < length; ++i) {
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int arr1[] = {0, 0, 0, 1};
    int arr2[] = {0, 0, 1, 0};
    int arr3[] = {0, 1, 0, 1};
    int arr4[] = {1, 0, 0, 1};
    int arr5[] = {1, 0, 1, 1};

    printf("%d\n", binaryArrayToInt(arr1, 4)); // 1
    printf("%d\n", binaryArrayToInt(arr2, 4)); // 2
    printf("%d\n", binaryArrayToInt(arr3, 4)); // 5
    printf("%d\n", binaryArrayToInt(arr4, 4)); // 9
    printf("%d\n", binaryArrayToInt(arr5, 4)); // 11

    return 0;
}