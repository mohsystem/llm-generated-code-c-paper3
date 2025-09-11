#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int queueTime(int customers[], int customers_size, int n) {
    if (customers_size == 0) {
        return 0;
    }
    if (n <= 0) {
        return -1; // Or handle the error as needed
    }

    int *tills = (int *)malloc(n * sizeof(int));
    if (tills == NULL) {
        return -1; // Memory allocation failed
    }
    for (int i = 0; i < n; i++) {
        tills[i] = 0;
    }

    for (int i = 0; i < customers_size; i++) {
        int minTill = 0;
        for (int j = 1; j < n; j++) {
            if (tills[j] < tills[minTill]) {
                minTill = j;
            }
        }
        tills[minTill] += customers[i];
    }

    int maxTime = 0;
    for (int i = 0; i < n; i++) {
        if (tills[i] > maxTime) {
            maxTime = tills[i];
        }
    }

    free(tills);
    return maxTime;
}

int main() {
    int test1[] = {5, 3, 4};
    printf("%d\n", queueTime(test1, 3, 1)); // 12

    int test2[] = {10, 2, 3, 3};
    printf("%d\n", queueTime(test2, 4, 2)); // 10

    int test3[] = {2, 3, 10};
    printf("%d\n", queueTime(test3, 3, 2)); // 12

    int test4[] = {};
    printf("%d\n", queueTime(test4, 0, 2)); // 0

    int test5[] = {1, 2, 3, 4, 5};
    printf("%d\n", queueTime(test5, 5, 3)); // 7

    return 0;
}