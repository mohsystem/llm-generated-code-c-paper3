
#include <stdio.h>

int findOdd(const int arr[], int size) {
    int result = 0;
    for(int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    // Test cases
    int arr1[] = {7};
    printf("%d\\n", findOdd(arr1, 1)); // 7
    
    int arr2[] = {0};
    printf("%d\\n", findOdd(arr2, 1)); // 0
    
    int arr3[] = {1,1,2};
    printf("%d\\n", findOdd(arr3, 3)); // 2
    
    int arr4[] = {0,1,0,1,0};
    printf("%d\\n", findOdd(arr4, 5)); // 0
    
    int arr5[] = {1,2,2,3,3,3,4,3,3,3,2,2,1};
    printf("%d\\n", findOdd(arr5, 13)); // 4
    
    return 0;
}
