#include <stdio.h>

int binaryArrayToInt(const int* binaryArray, int size) {
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int array1[] = {0, 0, 0, 1};
    int array2[] = {0, 0, 1, 0};
    int array3[] = {0, 1, 0, 1};
    int array4[] = {1, 0, 0, 1};
    int array5[] = {0, 1, 1, 0};

    printf("%d\n", binaryArrayToInt(array1, 4)); // 1
    printf("%d\n", binaryArrayToInt(array2, 4)); // 2
    printf("%d\n", binaryArrayToInt(array3, 4)); // 5
    printf("%d\n", binaryArrayToInt(array4, 4)); // 9
    printf("%d\n", binaryArrayToInt(array5, 4)); // 6

    return 0;
}