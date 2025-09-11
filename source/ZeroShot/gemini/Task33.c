#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int queueTime(int customers[], int customers_size, int n) {
    if (customers_size == 0) {
        return 0;
    }
    if (n <= 0) {
        return -1; // Or throw an exception
    }

    int *tills = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tills[i] = 0;
    }

    for (int i = 0; i < customers_size; i++) {
        int minTillIndex = 0;
        for (int j = 1; j < n; j++) {
            if (tills[j] < tills[minTillIndex]) {
                minTillIndex = j;
            }
        }
        tills[minTillIndex] += customers[i];
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
    int customers1[] = {5, 3, 4};
    printf("%d\n", queueTime(customers1, 3, 1)); // 12

    int customers2[] = {10, 2, 3, 3};
    printf("%d\n", queueTime(customers2, 4, 2)); // 10

    int customers3[] = {2, 3, 10};
    printf("%d\n", queueTime(customers3, 3, 2)); // 12

    int customers4[] = {};
    printf("%d\n", queueTime(customers4, 0, 2)); // 0

    int customers5[] = {1, 2, 3, 4, 5};
    printf("%d\n", queueTime(customers5, 5, 3)); // 7


    return 0;
}