
#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
        
    if (right < n && arr[right] > arr[largest])
        largest = right;
        
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
        
    // Extract elements from heap one by one
    for (int i = n-1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\\n");
}

int main() {
    // Test Case 1: Regular array
    int arr1[] = {12, 11, 13, 5, 6, 7};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    printf("Test 1: ");
    heapSort(arr1, n1);
    printArray(arr1, n1);
    
    // Test Case 2: Already sorted array
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    printf("Test 2: ");
    heapSort(arr2, n2);
    printArray(arr2, n2);
    
    // Test Case 3: Reverse sorted array
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    printf("Test 3: ");
    heapSort(arr3, n3);
    printArray(arr3, n3);
    
    // Test Case 4: Array with duplicates
    int arr4[] = {4, 4, 2, 2, 3, 3};
    int n4 = sizeof(arr4)/sizeof(arr4[0]);
    printf("Test 4: ");
    heapSort(arr4, n4);
    printArray(arr4, n4);
    
    // Test Case 5: Single element array
    int arr5[] = {1};
    int n5 = sizeof(arr5)/sizeof(arr5[0]);
    printf("Test 5: ");
    heapSort(arr5, n5);
    printArray(arr5, n5);
    
    return 0;
}
