
#include <stdio.h>

int binaryArrayToNumber(int arr[], int size) {
    int result = 0;
    for(int i = 0; i < size; i++) {
        result = result * 2 + arr[i];
    }
    return result;
}

int main() {
    int test1[] = {0, 0, 0, 1};
    int test2[] = {0, 0, 1, 0};
    int test3[] = {0, 1, 0, 1};
    int test4[] = {1, 0, 0, 1};
    int test5[] = {1, 1, 1, 1};
    
    printf("%d\\n", binaryArrayToNumber(test1, 4)); // 1
    printf("%d\\n", binaryArrayToNumber(test2, 4)); // 2
    printf("%d\\n", binaryArrayToNumber(test3, 4)); // 5
    printf("%d\\n", binaryArrayToNumber(test4, 4)); // 9
    printf("%d\\n", binaryArrayToNumber(test5, 4)); // 15
    
    return 0;
}
