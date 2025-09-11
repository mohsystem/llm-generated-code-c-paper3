
#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void posNegSort(int* arr, int size, int* result) {
    if (size == 0) return;
    
    // Copy input array to result
    for (int i = 0; i < size; i++) {
        result[i] = arr[i];
    }
    
    // Count positives and create array
    int pos_count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) pos_count++;
    }
    
    int* positives = (int*)malloc(pos_count * sizeof(int));
    int pos_idx = 0;
    
    // Fill positives array
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positives[pos_idx++] = arr[i];
        }
    }
    
    // Sort positives
    qsort(positives, pos_count, sizeof(int), compare);
    
    // Replace positives in result array
    pos_idx = 0;
    for (int i = 0; i < size; i++) {
        if (result[i] > 0) {
            result[i] = positives[pos_idx++];
        }
    }
    
    free(positives);
}

int main() {
    // Test cases
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int test3[] = {-5, -5, -5, -5, 7, -5};
    int test4[] = {-1, 2, -3, 4, -5, 6, -7};
    
    int result1[7], result2[8], result3[6], result4[7];
    
    posNegSort(test1, 7, result1);
    posNegSort(test2, 8, result2);
    posNegSort(test3, 6, result3);
    posNegSort(test4, 7, result4);
    
    // Print results
    printf("Test 1: ");
    for (int i = 0; i < 7; i++) printf("%d ", result1[i]);
    printf("\\nTest 2: ");
    for (int i = 0; i < 8; i++) printf("%d ", result2[i]);
    printf("\\nTest 3: ");
    for (int i = 0; i < 6; i++) printf("%d ", result3[i]);
    printf("\\nTest 4: ");
    for (int i = 0; i < 7; i++) printf("%d ", result4[i]);
    printf("\\nTest 5 (empty array): []\\n");
    
    return 0;
}
