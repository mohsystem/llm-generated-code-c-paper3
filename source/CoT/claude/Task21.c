
#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(const int* numbers, int length, int* resultLength) {
    if (numbers == NULL || length == 0) {
        *resultLength = 0;
        return NULL;
    }
    
    int* result = (int*)malloc((length - 1) * sizeof(int));
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
    
    for (int i = 0, j = 0; i < length; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    
    *resultLength = length - 1;
    return result;
}

void printArray(const int* arr, int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf("]");
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 4, 5},
        {5, 3, 2, 1, 4},
        {2, 2, 1, 2, 1},
        {1},
        {}
    };
    
    int lengths[] = {5, 5, 5, 1, 0};
    
    for (int i = 0; i < 5; i++) {
        printf("Input: ");
        printArray(testCases[i], lengths[i]);
        
        int resultLength;
        int* result = removeSmallest(testCases[i], lengths[i], &resultLength);
        
        printf("\\nOutput: ");
        printArray(result, resultLength);
        printf("\\n\\n");
        
        free(result);
    }
    
    return 0;
}
