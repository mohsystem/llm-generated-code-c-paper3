
#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(const int* numbers, int length, int* resultLength) {
    if (numbers == NULL || length <= 0) {
        *resultLength = 0;
        return NULL;
    }
    
    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }
    
    *resultLength = length - 1;
    int* result = (int*)malloc((*resultLength) * sizeof(int));
    if (result == NULL) {
        *resultLength = 0;
        return NULL;
    }
    
    for (int i = 0, j = 0; i < length; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    
    return result;
}

void printArray(const int* arr, int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) {
            printf(",");
        }
    }
    printf("]\\n");
}

int main() {
    // Test cases
    int test1[] = {1, 2, 3, 4, 5};
    int test2[] = {5, 3, 2, 1, 4};
    int test3[] = {2, 2, 1, 2, 1};
    int test4[] = {1};
    
    int resultLength;
    int* result;
    
    printf("Test 1:\\n");
    printf("Input: ");
    printArray(test1, 5);
    result = removeSmallest(test1, 5, &resultLength);
    printf("Output: ");
    printArray(result, resultLength);
    free(result);
    printf("\\n");
    
    printf("Test 2:\\n");
    printf("Input: ");
    printArray(test2, 5);
    result = removeSmallest(test2, 5, &resultLength);
    printf("Output: ");
    printArray(result, resultLength);
    free(result);
    printf("\\n");
    
    printf("Test 3:\\n");
    printf("Input: ");
    printArray(test3, 5);
    result = removeSmallest(test3, 5, &resultLength);
    printf("Output: ");
    printArray(result, resultLength);
    free(result);
    printf("\\n");
    
    printf("Test 4:\\n");
    printf("Input: ");
    printArray(test4, 1);
    result = removeSmallest(test4, 1, &resultLength);
    printf("Output: ");
    printArray(result, resultLength);
    free(result);
    
    return 0;
}
