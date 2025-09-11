#include <stdio.h>

int binaryArrayToInt(int* binaryArray, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int arr1[] = {0, 0, 0, 1};
    int arr2[] = {0, 0, 1, 0};
    printf("%d\n", binaryArrayToInt(arr1, 4));  // Output: 1
    printf("%d\n", binaryArrayToInt(arr2, 4));  // Output: 2
    // Add more test cases as needed
    return 0;
}