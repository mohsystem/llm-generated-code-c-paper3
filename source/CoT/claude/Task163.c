
#include <stdio.h>
#include <stdlib.h>

int longestRun(int arr[], int size) {
    if (size == 0) return 0;
    if (size == 1) return 1;
    
    int maxLen = 1;
    int currLen = 1;
    
    for (int i = 1; i < size; i++) {
        if (abs(arr[i] - arr[i-1]) == 1) {
            currLen++;
            maxLen = (maxLen > currLen) ? maxLen : currLen;
        } else {
            currLen = 1;
        }
    }
    
    return maxLen;
}

int main() {
    // Test cases
    int test1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int test2[] = {1, 2, 3, 10, 11, 15};
    int test3[] = {5, 4, 2, 1};
    int test4[] = {3, 5, 7, 10, 15};
    int test5[] = {1, 2, 3, 4, 5};
    
    printf("%d\\n", longestRun(test1, 8)); // 5
    printf("%d\\n", longestRun(test2, 6)); // 3
    printf("%d\\n", longestRun(test3, 4)); // 2
    printf("%d\\n", longestRun(test4, 5)); // 1
    printf("%d\\n", longestRun(test5, 5)); // 5
    
    return 0;
}
