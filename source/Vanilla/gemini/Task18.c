#include <stdio.h>

int binaryArrayToInt(int binaryArray[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int test1[] = {0, 0, 0, 1};
    printf("Testing: [0, 0, 0, 1] ==> %d\n", binaryArrayToInt(test1, 4));
    int test2[] = {0, 0, 1, 0};
    printf("Testing: [0, 0, 1, 0] ==> %d\n", binaryArrayToInt(test2, 4));
    int test3[] = {0, 1, 0, 1};
    printf("Testing: [0, 1, 0, 1] ==> %d\n", binaryArrayToInt(test3, 4));
    int test4[] = {1, 0, 0, 1};
    printf("Testing: [1, 0, 0, 1] ==> %d\n", binaryArrayToInt(test4, 4));
    int test5[] = {0, 0, 1, 0};
    printf("Testing: [0, 0, 1, 0] ==> %d\n", binaryArrayToInt(test5, 4));
    int test6[] = {0, 1, 1, 0};
    printf("Testing: [0, 1, 1, 0] ==> %d\n", binaryArrayToInt(test6, 4));
    int test7[] = {1, 1, 1, 1};
    printf("Testing: [1, 1, 1, 1] ==> %d\n", binaryArrayToInt(test7, 4));
    int test8[] = {1, 0, 1, 1};
    printf("Testing: [1, 0, 1, 1] ==> %d\n", binaryArrayToInt(test8, 4));
    return 0;
}