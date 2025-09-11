
#include <stdio.h>
#include <stdlib.h>

void two_sum(int* numbers, int numbersLength, int target, int* result) {
    for (int i = 0; i < numbersLength - 1; i++) {
        for (int j = i + 1; j < numbersLength; j++) {
            if (numbers[i] + numbers[j] == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
    result[0] = -1;
    result[1] = -1;
}

int main() {
    // Test cases
    int test1[] = {1, 2, 3};
    int test2[] = {3, 2, 4};
    int test3[] = {2, 2, 3};
    int test4[] = {1, 3, 4, 2};
    int test5[] = {5, 2, 7, 1, 8};
    
    int targets[] = {4, 6, 4, 6, 9};
    int* testArrays[] = {test1, test2, test3, test4, test5};
    int lengths[] = {3, 3, 3, 4, 5};
    
    int result[2];
    
    for (int i = 0; i < 5; i++) {
        two_sum(testArrays[i], lengths[i], targets[i], result);
        printf("Test %d: [%d, %d]\\n", i + 1, result[0], result[1]);
    }
    
    return 0;
}
