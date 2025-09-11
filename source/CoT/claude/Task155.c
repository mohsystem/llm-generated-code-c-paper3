
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
        
    if (right < n && arr[right] > arr[largest])
        largest = right;
        
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    if (arr == NULL || n <= 1) return;
    
    // Build max heap
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
        
    // Extract elements from heap one by one    
    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    // Test cases
    int test1[] = {64, 34, 25, 12, 22, 11, 90};
    int test2[] = {5, 2, 8, 1, 9, 3};
    int test3[] = {1};
    int test4[] = {1, 2, 3, 4, 5};
    int test5[] = {5, 4, 3, 2, 1};
    
    int* testCases[] = {test1, test2, test3, test4, test5};
    int sizes[] = {7, 6, 1, 5, 5};
    
    for(int i = 0; i < 5; i++) {
        printf("Test case %d Before sorting: ", i+1);
        for(int j = 0; j < sizes[i]; j++)
            printf("%d ", testCases[i][j]);
            
        heapSort(testCases[i], sizes[i]);
        
        printf("\\nAfter sorting: ");
        for(int j = 0; j < sizes[i]; j++)
            printf("%d ", testCases[i][j]);
        printf("\\n\\n");
    }
    
    return 0;
}
