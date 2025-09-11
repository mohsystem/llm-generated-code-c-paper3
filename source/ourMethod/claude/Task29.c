
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function returns dynamically allocated array of size 2
// Caller is responsible for freeing the memory
int* twoSum(const int* numbers, int numbersSize, int target, int* returnSize) {
    if (numbers == NULL || numbersSize < 2) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    *returnSize = 2;
    
    for (int i = 0; i < numbersSize - 1; i++) {
        for (int j = i + 1; j < numbersSize; j++) {
            // Use 64-bit arithmetic to prevent overflow
            int64_t sum = (int64_t)numbers[i] + numbers[j];
            if (sum == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    
    // Should not reach here given problem constraints
    free(result);
    *returnSize = 0;
    return NULL;
}

int main() {
    // Test cases
    int test1[] = {1, 2, 3};
    int test2[] = {3, 2, 4};
    int test3[] = {2, 7, 11, 15};
    int test4[] = {1234, 5678, 9012};
    int test5[] = {0, 0, 0};
    
    int* tests[] = {test1, test2, test3, test4, test5};
    int sizes[] = {3, 3, 4, 3, 3};
    int targets[] = {4, 6, 9, 14690, 0};
    
    for (int i = 0; i < 5; i++) {
        int returnSize;
        int* result = twoSum(tests[i], sizes[i], targets[i], &returnSize);
        if (result != NULL) {
            printf("Test %d: [%d, %d]\\n", i + 1, result[0], result[1]);
            free(result);
        } else {
            printf("Test %d: No solution found\\n", i + 1);
        }
    }
    
    return 0;
}
