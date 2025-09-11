#include <stdio.h>

int findEvenIndex(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int leftSum = 0;
        for (int j = 0; j < i; j++) {
            leftSum += arr[j];
        }

        int rightSum = 0;
        for (int j = i + 1; j < n; j++) {
            rightSum += arr[j];
        }

        if (leftSum == rightSum) {
            return i;
        }
    }
    return -1;
}

int main() {
    int test1[] = {1, 2, 3, 4, 3, 2, 1};
    int test2[] = {1, 100, 50, -51, 1, 1};
    int test3[] = {20, 10, -80, 10, 10, 15, 35};
    int test4[] = {1, 2, 3, 4, 5};
    int test5[] = {1};

    printf("%d\n", findEvenIndex(test1, 7)); // Output: 3
    printf("%d\n", findEvenIndex(test2, 6)); // Output: 1
    printf("%d\n", findEvenIndex(test3, 7)); // Output: 0
    printf("%d\n", findEvenIndex(test4, 5)); // Output: -1
    printf("%d\n", findEvenIndex(test5, 1)); // Output: 0
    return 0;
}