
#include <stdio.h>
#include <stdlib.h>

int longestRun(const int arr[], int size) {
    if (arr == NULL || size == 0) {
        return 0;
    }
    if (size == 1) {
        return 1;
    }
    
    int maxLen = 1;
    int currLen = 1;
    
    for (int i = 1; i < size; i++) {
        int diff = arr[i] - arr[i-1];
        if (diff == 1 || diff == -1) {
            currLen++;
            maxLen = currLen > maxLen ? currLen : maxLen;
        } else {
            currLen = 1;
        }
    }
    
    return maxLen;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int arr2[] = {1, 2, 3, 10, 11, 15};
    int arr3[] = {5, 4, 2, 1};
    int arr4[] = {3, 5, 7, 10, 15};
    int arr5[] = {1};
    
    printf("%d\\n", longestRun(arr1, 8)); // 5
    printf("%d\\n", longestRun(arr2, 6)); // 3
    printf("%d\\n", longestRun(arr3, 4)); // 2
    printf("%d\\n", longestRun(arr4, 5)); // 1
    printf("%d\\n", longestRun(arr5, 1)); // 1
    
    return 0;
}
