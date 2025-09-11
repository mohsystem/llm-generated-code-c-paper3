
#include <stdio.h>
#include <stdlib.h>

int convertBinaryArrayToInt(const int* binary, size_t length) {
    if (binary == NULL || length == 0) {
        return 0;
    }
    
    int result = 0;
    int power = 1;
    
    for (size_t i = length; i > 0; i--) {
        if (binary[i-1] != 0 && binary[i-1] != 1) {
            fprintf(stderr, "Array must contain only 0s and 1s\\n");
            return -1;
        }
        result += binary[i-1] * power;
        power *= 2;
    }
    
    return result;
}

int main() {
    // Test cases
    int test1[] = {0, 0, 0, 1};
    int test2[] = {0, 0, 1, 0};
    int test3[] = {0, 1, 0, 1};
    int test4[] = {1, 0, 0, 1};
    int test5[] = {1, 1, 1, 1};
    
    printf("%d\\n", convertBinaryArrayToInt(test1, 4)); // 1
    printf("%d\\n", convertBinaryArrayToInt(test2, 4)); // 2
    printf("%d\\n", convertBinaryArrayToInt(test3, 4)); // 5
    printf("%d\\n", convertBinaryArrayToInt(test4, 4)); // 9
    printf("%d\\n", convertBinaryArrayToInt(test5, 4)); // 15
    
    return 0;
}
