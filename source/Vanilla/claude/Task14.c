
#include <stdio.h>

int findEqualIndex(int arr[], int size) {
    int totalSum = 0;
    for(int i = 0; i < size; i++) {
        totalSum += arr[i];
    }
    
    int leftSum = 0;
    for(int i = 0; i < size; i++) {
        int rightSum = totalSum - leftSum - arr[i];
        if(leftSum == rightSum) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    int test1[] = {1,2,3,4,3,2,1};
    int test2[] = {1,100,50,-51,1,1};
    int test3[] = {20,10,-80,10,10,15,35};
    int test4[] = {1,2,3};
    int test5[] = {1};
    
    printf("%d\\n", findEqualIndex(test1, 7));  // 3
    printf("%d\\n", findEqualIndex(test2, 6));  // 1
    printf("%d\\n", findEqualIndex(test3, 7));  // 0
    printf("%d\\n", findEqualIndex(test4, 3));  // -1
    printf("%d\\n", findEqualIndex(test5, 1));  // 0
    
    return 0;
}
