
#include <stdio.h>

int findEqualIndex(const int arr[], int size) {
    if (size == 0) return -1;
    
    long long totalSum = 0;
    for (int i = 0; i < size; i++) {
        totalSum += arr[i];
    }
    
    long long leftSum = 0;
    for (int i = 0; i < size; i++) {
        long long rightSum = totalSum - leftSum - arr[i];
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    // Test cases
    int arr1[] = {1,2,3,4,3,2,1};
    int arr2[] = {1,100,50,-51,1,1};
    int arr3[] = {20,10,-80,10,10,15,35};
    int arr4[] = {1,2,3};
    int arr5[] = {20,10,30,10,10,15,35};
    
    printf("%d\\n", findEqualIndex(arr1, 7));  // Expected: 3
    printf("%d\\n", findEqualIndex(arr2, 6));  // Expected: 1
    printf("%d\\n", findEqualIndex(arr3, 7));  // Expected: 0
    printf("%d\\n", findEqualIndex(arr4, 3));  // Expected: -1
    printf("%d\\n", findEqualIndex(arr5, 7));  // Expected: -1
    
    return 0;
}
