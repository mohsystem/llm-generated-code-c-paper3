
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void posNegSort(int* arr, int size, int* result) {
    if (size == 0) return;
    
    // Copy input array to result
    memcpy(result, arr, size * sizeof(int));
    
    // Store positive numbers and their indices
    int* positives = (int*)malloc(size * sizeof(int));
    int* pos_indices = (int*)malloc(size * sizeof(int));
    int pos_count = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positives[pos_count] = arr[i];
            pos_indices[pos_count] = i;
            pos_count++;
        }
    }
    
    // Sort positive numbers
    qsort(positives, pos_count, sizeof(int), compare);
    
    // Place sorted positive numbers back in their positions
    for (int i = 0; i < pos_count; i++) {
        result[pos_indices[i]] = positives[i];
    }
    
    free(positives);
    free(pos_indices);
}

int main() {
    // Test cases
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int test3[] = {-5, -5, -5, -5, 7, -5};
    int test4[] = {1, -2, 3, -4, 5};
    
    int result1[7], result2[8], result3[6], result4[5];
    
    posNegSort(test1, 7, result1);
    posNegSort(test2, 8, result2);
    posNegSort(test3, 6, result3);
    posNegSort(test4, 5, result4);
    
    // Print results
    for (int i = 0; i < 7; i++) printf("%d ", result1[i]);
    printf("\\n");
    for (int i = 0; i < 8; i++) printf("%d ", result2[i]);
    printf("\\n");
    for (int i = 0; i < 6; i++) printf("%d ", result3[i]);
    printf("\\n");
    for (int i = 0; i < 5; i++) printf("%d ", result4[i]);
    printf("\\n");
    
    return 0;
}
