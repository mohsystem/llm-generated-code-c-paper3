#include <stdio.h>
#include <stdlib.h>

int binaryArrayToInt(const int* binaryArray, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        if (binaryArray[i] != 0 && binaryArray[i] != 1) {
            fprintf(stderr, "Invalid binary number\n");
            exit(EXIT_FAILURE);
        }
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int arr1[] = {0, 0, 0, 1};
    printf("%d\n", binaryArrayToInt(arr1, sizeof(arr1)/sizeof(arr1[0]))); // 1
    int arr2[] = {0, 0, 1, 0};
    printf("%d\n", binaryArrayToInt(arr2, sizeof(arr2)/sizeof(arr2[0]))); // 2
    int arr3[] = {0, 1, 0, 1};
    printf("%d\n", binaryArrayToInt(arr3, sizeof(arr3)/sizeof(arr3[0]))); // 5
    // Add more test cases as needed
    return 0;
}