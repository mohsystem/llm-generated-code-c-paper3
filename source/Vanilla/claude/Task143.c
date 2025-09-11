
#include <stdio.h>

void sortArray(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
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
    int test3[] = {3};
    int test4[] = {1, 1, 1, 1};
    int test5[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    int sizes[] = {7, 5, 1, 4, 10};
    int* testCases[] = {test1, test2, test3, test4, test5};
    
    for(int i = 0; i < 5; i++) {
        printf("Test case %d Before sorting: ", i+1);
        for(int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        
        sortArray(testCases[i], sizes[i]);
        
        printf("\\nAfter sorting: ");
        for(int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\\n\\n");
    }
    
    return 0;
}
