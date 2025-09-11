
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
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
        
    for (int i = n - 1; i > 0; i--) {
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
    int test1[] = {4, 10, 3, 5, 1};
    int test2[] = {64, 34, 25, 12, 22, 11, 90};
    int test3[] = {1};
    int test4[] = {1, 2, 3, 4, 5};
    int test5[] = {5, 4, 3, 2, 1};
    
    printf("Test case 1 Before sorting: ");
    printArray(test1, 5);
    heapSort(test1, 5);
    printf("Test case 1 After sorting: ");
    printArray(test1, 5);
    printf("\\n");
    
    printf("Test case 2 Before sorting: ");
    printArray(test2, 7);
    heapSort(test2, 7);
    printf("Test case 2 After sorting: ");
    printArray(test2, 7);
    printf("\\n");
    
    printf("Test case 3 Before sorting: ");
    printArray(test3, 1);
    heapSort(test3, 1);
    printf("Test case 3 After sorting: ");
    printArray(test3, 1);
    printf("\\n");
    
    printf("Test case 4 Before sorting: ");
    printArray(test4, 5);
    heapSort(test4, 5);
    printf("Test case 4 After sorting: ");
    printArray(test4, 5);
    printf("\\n");
    
    printf("Test case 5 Before sorting: ");
    printArray(test5, 5);
    heapSort(test5, 5);
    printf("Test case 5 After sorting: ");
    printArray(test5, 5);
    printf("\\n");
    
    return 0;
}
