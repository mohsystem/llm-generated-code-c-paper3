#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int nums[], int n) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    int i;

    for (i = 0; i < n; i++) {
        maxEndingHere = (nums[i] > maxEndingHere + nums[i]) ? nums[i] : maxEndingHere + nums[i];
        maxSoFar = (maxSoFar > maxEndingHere) ? maxSoFar : maxEndingHere;
    }

    return maxSoFar;
}

int main() {
    int test1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int test2[] = {1};
    int test3[] = {5, 4, -1, 7, 8};
    int test4[] = {-1};
    int test5[] = {-2, -1};

    int n1 = sizeof(test1) / sizeof(test1[0]);
    int n2 = sizeof(test2) / sizeof(test2[0]);
    int n3 = sizeof(test3) / sizeof(test3[0]);
    int n4 = sizeof(test4) / sizeof(test4[0]);
    int n5 = sizeof(test5) / sizeof(test5[0]);


    printf("Test case 1: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", test1[i]);
    }
    printf("Max sum: %d\n", maxSubArraySum(test1, n1)); // Expected: 6

    printf("Test case 2: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", test2[i]);
    }
    printf("Max sum: %d\n", maxSubArraySum(test2, n2)); // Expected: 1

    printf("Test case 3: ");
    for (int i = 0; i < n3; i++) {
        printf("%d ", test3[i]);
    }
    printf("Max sum: %d\n", maxSubArraySum(test3, n3)); // Expected: 23

    printf("Test case 4: ");
    for (int i = 0; i < n4; i++) {
        printf("%d ", test4[i]);
    }
    printf("Max sum: %d\n", maxSubArraySum(test4, n4)); // Expected: -1

    printf("Test case 5: ");
    for (int i = 0; i < n5; i++) {
        printf("%d ", test5[i]);
    }
    printf("Max sum: %d\n", maxSubArraySum(test5, n5)); // Expected: -1


    return 0;
}