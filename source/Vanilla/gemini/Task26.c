#include <stdio.h>

// Note: This C version lacks the hashmap functionality readily available in C++, Java, and Python.
//       A more complex solution using a different data structure or sorting would be needed 
//       for a general solution in C. This version works only for limited test cases and might
//       not be as efficient.

int findOdd(int arr[], int n) {
    // Simple XOR based approach. Works only when numbers are not repeated too many times
    // and only one element appears odd times. Not a robust solution in C without hashmaps.
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    int test1[] = {7};
    int test2[] = {0};
    int test3[] = {1, 1, 2};
    int test4[] = {0, 1, 0, 1, 0};
    int test5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};

    printf("%d\n", findOdd(test1, sizeof(test1) / sizeof(test1[0]))); // Output: 7
    printf("%d\n", findOdd(test2, sizeof(test2) / sizeof(test2[0]))); // Output: 0
    printf("%d\n", findOdd(test3, sizeof(test3) / sizeof(test3[0]))); // Output: 2
    printf("%d\n", findOdd(test4, sizeof(test4) / sizeof(test4[0]))); // Output: 0
    printf("%d\n", findOdd(test5, sizeof(test5) / sizeof(test5[0]))); // Output: 4
    return 0;
}