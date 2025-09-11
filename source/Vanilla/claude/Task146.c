
#include <stdio.h>

int findMissingNumber(int arr[], int size) {
    int n = size + 1;
    int expectedSum = (n * (n + 1)) / 2;
    int actualSum = 0;
    for(int i = 0; i < size; i++) {
        actualSum += arr[i];
    }
    return expectedSum - actualSum;
}

int main() {
    int testCases[][4] = {
        {1, 2, 4, 5}, // missing 3
        {1, 3, 4, 5}, // missing 2
        {2, 3, 4, 5}, // missing 1
        {1, 2, 3, 5}, // missing 4
        {1, 2, 3, 4}  // missing 5
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Test Case %d: Missing number is %d\\n", 
               i+1, findMissingNumber(testCases[i], 4));
    }
    return 0;
}
