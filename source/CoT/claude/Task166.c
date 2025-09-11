
#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void posNegSort(int arr[], int size, int result[]) {
    if (size == 0) {
        return;
    }
    
    // Extract positive numbers
    int* positives = (int*)malloc(size * sizeof(int));
    int posCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positives[posCount++] = arr[i];
        }
    }
    
    // Sort positive numbers
    qsort(positives, posCount, sizeof(int), compare);
    
    // Put numbers back maintaining negative positions
    int posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            result[i] = positives[posIndex++];
        } else {
            result[i] = arr[i];
        }
    }
    
    free(positives);
}

int main() {
    // Test cases
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int test3[] = {-5, -5, -5, -5, 7, -5};
    int test4[] = {1, 2, 3, 4, 5};
    
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
