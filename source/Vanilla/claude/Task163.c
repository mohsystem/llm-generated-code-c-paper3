
#include <stdio.h>

int longestRun(int arr[], int size) {
    if (size <= 1) return size;
    
    int maxLen = 1;
    int currLen = 1;
    int isIncreasing = 1;  // Using 1 for true, 0 for false
    
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i-1] + 1) {
            if (isIncreasing || currLen == 1) {
                isIncreasing = 1;
                currLen++;
            } else {
                currLen = 2;
            }
        }
        else if (arr[i] == arr[i-1] - 1) {
            if (!isIncreasing || currLen == 1) {
                isIncreasing = 0;
                currLen++;
            } else {
                currLen = 2;
            }
        }
        else {
            currLen = 1;
        }
        maxLen = maxLen > currLen ? maxLen : currLen;
    }
    return maxLen;
}

int main() {
    // Test case 1
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    printf("%d\\n", longestRun(arr1, 8)); // 5
    
    // Test case 2
    int arr2[] = {1, 2, 3, 10, 11, 15};
    printf("%d\\n", longestRun(arr2, 6)); // 3
    
    // Test case 3
    int arr3[] = {5, 4, 2, 1};
    printf("%d\\n", longestRun(arr3, 4)); // 2
    
    // Test case 4
    int arr4[] = {3, 5, 7, 10, 15};
    printf("%d\\n", longestRun(arr4, 5)); // 1
    
    // Test case 5
    int arr5[] = {1};
    printf("%d\\n", longestRun(arr5, 1)); // 1
    
    return 0;
}
