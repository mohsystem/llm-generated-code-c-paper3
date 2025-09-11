
#include <stdio.h>
#include <limits.h>

int shortestSubarray(const int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0) {
        return -1;
    }
    
    int minLength = INT_MAX;
    
    for (int start = 0; start < numsSize; start++) {
        long long sum = 0;  // Using long long to prevent integer overflow
        for (int end = start; end < numsSize; end++) {
            sum += nums[end];
            if (sum >= k) {
                int currentLength = end - start + 1;
                minLength = (currentLength < minLength) ? currentLength : minLength;
                break;
            }
        }
    }
    
    return minLength == INT_MAX ? -1 : minLength;
}

int main() {
    // Test cases
    int test1[] = {1};
    int test2[] = {1,2};
    int test3[] = {2,-1,2};
    int test4[] = {1,1,1,1,1};
    int test5[] = {2,3,1,2,4,3};
    
    printf("%d\\n", shortestSubarray(test1, 1, 1));  // Expected: 1
    printf("%d\\n", shortestSubarray(test2, 2, 4));  // Expected: -1
    printf("%d\\n", shortestSubarray(test3, 3, 3));  // Expected: 3
    printf("%d\\n", shortestSubarray(test4, 5, 5));  // Expected: 5
    printf("%d\\n", shortestSubarray(test5, 6, 7));  // Expected: 2
    
    return 0;
}
