#include <stdio.h>

int findMissingNumber(int arr[], int n) {
    int expectedSum = (n + 1) * (n + 2) / 2;
    int actualSum = 0;
    for (int i = 0; i < n; i++) {
        actualSum += arr[i];
    }
    return expectedSum - actualSum;
}

int main() {
    // Test cases
    int testCase1[] = {1, 2, 3, 5};
    int testCase2[] = {1, 2, 4, 5};
    int testCase3[] = {1, 3, 4, 5};
    int testCase4[] = {2, 3, 4, 5};
    int testCase5[] = {1, 2, 3, 4};

    printf("Missing number in testCase1: %d\n", findMissingNumber(testCase1, 4));
    printf("Missing number in testCase2: %d\n", findMissingNumber(testCase2, 4));
    printf("Missing number in testCase3: %d\n", findMissingNumber(testCase3, 4));
    printf("Missing number in testCase4: %d\n", findMissingNumber(testCase4, 4));
    printf("Missing number in testCase5: %d\n", findMissingNumber(testCase5, 4));

    return 0;
}