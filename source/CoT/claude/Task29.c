
#include <stdio.h>
#include <stdlib.h>

void twoSum(int* numbers, int numbersSize, int target, int* result) {
    if (numbers == NULL || numbersSize < 2) {
        result[0] = -1;
        result[1] = -1;
        return;
    }
    
    for (int i = 0; i < numbersSize - 1; i++) {
        for (int j = i + 1; j < numbersSize; j++) {
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
    int test3[] = {2, 7, 11, 15};
    int test4[] = {3, 3};
    int test5[] = {1, 5, 3, 7, 2};
    
    int* testArrays[] = {test1, test2, test3, test4, test5};
    int sizes[] = {3, 3, 4, 2, 5};
    int targets[] = {4, 6, 9, 6, 10};
    
    for (int i = 0; i < 5; i++) {
        int result[2];
        twoSum(testArrays[i], sizes[i], targets[i], result);
        printf("Test case %d: [%d, %d]\\n", i+1, result[0], result[1]);
    }
    
    return 0;
}
