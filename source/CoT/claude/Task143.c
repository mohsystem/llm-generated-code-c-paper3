
#include <stdio.h>
#include <stdlib.h>

void sortArray(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    int temp;
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    // Test cases
    int test1[] = {64, 34, 25, 12, 22, 11, 90};
    int test2[] = {5, 2, 8, 1, 9};
    int test3[] = {1};
    int test4[] = {};
    int test5[] = {10, 10, 10, 10};
    
    int sizes[] = {7, 5, 1, 0, 4};
    int* testCases[] = {test1, test2, test3, test4, test5};
    
    for (int i = 0; i < 5; i++) {
        printf("Test case %d Input: ", i+1);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\\n");
        
        sortArray(testCases[i], sizes[i]);
        printf("Sorted array: ");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\\n\\n");
    }
    
    return 0;
}
