
#include <stdio.h>
#include <stdlib.h>

int* posNegSort(int* arr, int size, int* resultSize) {
    if (arr == NULL || size == 0) {
        *resultSize = 0;
        return NULL;
    }
    
    // Count positive numbers
    int posCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            posCount++;
        }
    }
    
    // Create array for positive numbers
    int* positives = (int*)malloc(posCount * sizeof(int));
    if (positives == NULL) {
        *resultSize = 0;
        return NULL;
    }
    
    int posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positives[posIndex++] = arr[i];
        }
    }
    
    // Sort positive numbers
    for (int i = 0; i < posCount - 1; i++) {
        for (int j = 0; j < posCount - i - 1; j++) {
            if (positives[j] > positives[j + 1]) {
                int temp = positives[j];
                positives[j] = positives[j + 1];
                positives[j + 1] = temp;
            }
        }
    }
    
    // Create result array
    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        free(positives);
        *resultSize = 0;
        return NULL;
    }
    
    posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            result[i] = positives[posIndex++];
        } else {
            result[i] = arr[i];
        }
    }
    
    free(positives);
    *resultSize = size;
    return result;
}

int main() {
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int test3[] = {-5, -5, -5, -5, 7, -5};
    int resultSize;
    
    // Test case 1
    int* result1 = posNegSort(test1, 7, &resultSize);
    if (result1 != NULL) {
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", result1[i]);
        }
        printf("\\n");
        free(result1);
    }
    
    // Test case 2
    int* result2 = posNegSort(test2, 8, &resultSize);
    if (result2 != NULL) {
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", result2[i]);
        }
        printf("\\n");
        free(result2);
    }
    
    // Test case 3
    int* result3 = posNegSort(test3, 6, &resultSize);
    if (result3 != NULL) {
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", result3[i]);
        }
        printf("\\n");
        free(result3);
    }
    
    // Test case 4 (empty array)
    int* result4 = posNegSort(NULL, 0, &resultSize);
    if (result4 == NULL) {
        printf("[]\\n");
    }
    
    // Test case 5
    int test5[] = {1, 2, 3, 4, 5};
    int* result5 = posNegSort(test5, 5, &resultSize);
    if (result5 != NULL) {
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", result5[i]);
        }
        printf("\\n");
        free(result5);
    }
    
    return 0;
}
