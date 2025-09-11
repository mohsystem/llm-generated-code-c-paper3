#include <stdio.h>
#include <stdlib.h>

int findMiddleIndex(int arr[], int size) {
    if (size == 0) return -1;
    int leftSum = 0;
    int rightSum = 0;
    for (int i = 0; i < size; i++) rightSum += arr[i];
    for (int i = 0; i < size; i++) {
        rightSum -= arr[i];
        if (leftSum == rightSum) return i;
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    int test1[] = {1, 2, 3, 4, 3, 2, 1};
    int test2[] = {1, 100, 50, -51, 1, 1};
    int test3[] = {20, 10, -80, 10, 10, 15, 35};
    int test4[] = {1, 2, 3};
    int test5[] = {};

    int sizes[] = {7, 6, 7, 3, 0};

    printf("%d\n", findMiddleIndex(test1, sizes[0])); // Output: 3
    printf("%d\n", findMiddleIndex(test2, sizes[1])); // Output: 1
    printf("%d\n", findMiddleIndex(test3, sizes[2])); // Output: 0
    printf("%d\n", findMiddleIndex(test4, sizes[3])); // Output: -1
    printf("%d\n", findMiddleIndex(test5, sizes[4])); // Output: -1

    return 0;
}