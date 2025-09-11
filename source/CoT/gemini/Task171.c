#include <stdio.h>
#include <limits.h>

int reversePairs(int nums[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] > 2LL * nums[j]) { // Use long long to avoid potential overflow
                count++;
            }
        }
    }
    return count;
}

int main() {
    int test1[] = {1, 3, 2, 3, 1};
    int test2[] = {2, 4, 3, 5, 1};
    int test3[] = {};
    int test4[] = {1};
    int test5[] = {INT_MAX, INT_MIN};

    printf("Test case 1: %d\n", reversePairs(test1, sizeof(test1) / sizeof(test1[0]))); // Output: 2
    printf("Test case 2: %d\n", reversePairs(test2, sizeof(test2) / sizeof(test2[0]))); // Output: 3
    printf("Test case 3: %d\n", reversePairs(test3, sizeof(test3) / sizeof(test3[0]))); // Output: 0
    printf("Test case 4: %d\n", reversePairs(test4, sizeof(test4) / sizeof(test4[0]))); // Output: 0
    printf("Test case 5: %d\n", reversePairs(test5, sizeof(test5) / sizeof(test5[0]))); // Output: 1


    return 0;
}