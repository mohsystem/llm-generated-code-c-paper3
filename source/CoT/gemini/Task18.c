#include <stdio.h>
#include <math.h>

int binaryArrayToInt(int binaryArray[], int length) {
    int decimalValue = 0;
    int power = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (binaryArray[i] == 1) {
            decimalValue += pow(2, power);
        }
        power++;
    }
    return decimalValue;
}

int main() {
    int test1[] = {0, 0, 0, 1};
    int test2[] = {0, 0, 1, 0};
    int test3[] = {0, 1, 0, 1};
    int test4[] = {1, 0, 0, 1};
    int test5[] = {0, 0, 1, 0};
    int test6[] = {0, 1, 1, 0};
    int test7[] = {1, 1, 1, 1};
    int test8[] = {1, 0, 1, 1};


    printf("Testing: [0, 0, 0, 1] ==> %d\n", binaryArrayToInt(test1, 4));
    printf("Testing: [0, 0, 1, 0] ==> %d\n", binaryArrayToInt(test2, 4));
    printf("Testing: [0, 1, 0, 1] ==> %d\n", binaryArrayToInt(test3, 4));
    printf("Testing: [1, 0, 0, 1] ==> %d\n", binaryArrayToInt(test4, 4));
    printf("Testing: [0, 0, 1, 0] ==> %d\n", binaryArrayToInt(test5, 4));
    printf("Testing: [0, 1, 1, 0] ==> %d\n", binaryArrayToInt(test6, 4));
    printf("Testing: [1, 1, 1, 1] ==> %d\n", binaryArrayToInt(test7, 4));
    printf("Testing: [1, 0, 1, 1] ==> %d\n", binaryArrayToInt(test8, 4));

    return 0;
}