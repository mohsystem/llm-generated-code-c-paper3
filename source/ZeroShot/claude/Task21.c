
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* removeSmallest(const int* numbers, int length, int* resultLength) {
    if (length == 0 || numbers == NULL) {
        *resultLength = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(sizeof(int) * (length - 1));
    if (result == NULL) {
        *resultLength = 0;
        return NULL;
    }
    
    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }
    
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    
    *resultLength = length - 1;
    return result;
}

void printArray(int* arr, int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) printf(", ");
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
    
    int* result1 = removeSmallest(test1, 5, &resultLength);
    printArray(result1, resultLength);
    free(result1);
    
    int* result2 = removeSmallest(test2, 5, &resultLength);
    printArray(result2, resultLength);
    free(result2);
    
    int* result3 = removeSmallest(test3, 5, &resultLength);
    printArray(result3, resultLength);
    free(result3);
    
    int* result4 = removeSmallest(test4, 1, &resultLength);
    printArray(result4, resultLength);
    free(result4);
    
    int* result5 = removeSmallest(NULL, 0, &resultLength);
    printArray(result5, resultLength);
    // No need to free result5 as it's NULL
    
    return 0;
}
