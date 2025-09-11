#include <stdio.h>
#include <stdlib.h>

int binaryArrayToInt(const int binaryArray[], size_t len) {
    int result = 0;
    for (size_t i = 0; i < len; i++) {
         if (binaryArray[i] != 0 && binaryArray[i] != 1) {
             fprintf(stderr,"Error: Invalid input in array\n");
             exit(EXIT_FAILURE); // Or handle the error as appropriate.
        }
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int test1[] = {0, 0, 0, 1};
    int test2[] = {0, 0, 1, 0};
    int test3[] = {0, 1, 0, 1};
    int test4[] = {1, 0, 0, 1};
    int test5[] = {1, 1, 1, 1};


    printf("Testing: [0, 0, 0, 1] ==> %d\n", binaryArrayToInt(test1, sizeof(test1)/sizeof(test1[0])));
    printf("Testing: [0, 0, 1, 0] ==> %d\n", binaryArrayToInt(test2, sizeof(test2)/sizeof(test2[0])));
    printf("Testing: [0, 1, 0, 1] ==> %d\n", binaryArrayToInt(test3, sizeof(test3)/sizeof(test3[0])));
    printf("Testing: [1, 0, 0, 1] ==> %d\n", binaryArrayToInt(test4, sizeof(test4)/sizeof(test4[0])));
    printf("Testing: [1, 1, 1, 1] ==> %d\n", binaryArrayToInt(test5, sizeof(test5)/sizeof(test5[0])));

    return 0;
}