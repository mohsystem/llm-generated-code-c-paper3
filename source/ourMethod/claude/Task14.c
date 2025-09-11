
#include <stdio.h>

int findEvenIndex(const int arr[], int length) {
    if (arr == NULL || length <= 0) {
        return -1;
    }
    
    long long totalSum = 0;
    for (int i = 0; i < length; i++) {
        totalSum += arr[i];
    }
    
    long long leftSum = 0;
    for (int i = 0; i < length; i++) {
        long long rightSum = totalSum - leftSum - arr[i];
        
        if (leftSum == rightSum) {
            return i;
        }
        
        leftSum += arr[i];
    }
    
    return -1;
}

void runTest(const int arr[], int length) {
    printf("%d\\n", findEvenIndex(arr, length));
}

int main() {
    // Test cases
    int test1[] = {1,2,3,4,3,2,1};
    int test2[] = {1,100,50,-51,1,1};
    int test3[] = {20,10,-80,10,10,15,35};
    int test4[] = {1,2,3,4,5};
    int test5[] = {2,2,2,2};
    
    runTest(test1, 7);  // Should print 3
    runTest(test2, 6);  // Should print 1
    runTest(test3, 7);  // Should print 0
    runTest(test4, 5);  // Should print -1
    runTest(test5, 4);  // Should print 2
    
    return 0;
}
