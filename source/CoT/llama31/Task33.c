#include <stdio.h>
#include <stdlib.h>

int queueTime(int customers[], int size, int n) {
    int* tills = (int*)calloc(n, sizeof(int));
    if (!tills) {
        return -1; // Memory allocation failed
    }

    for (int i = 0; i < size; i++) {
        int minIndex = 0;
        for (int j = 1; j < n; j++) {
            if (tills[j] < tills[minIndex]) {
                minIndex = j;
            }
        }
        tills[minIndex] += customers[i];
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
    int customers2[] = {10, 2, 3, 3};
    int customers3[] = {2, 3, 10};
    int customers4[] = {1, 2, 3, 4, 5};
    int customers5[] = {1, 1, 1, 1, 1};

    printf("%d\n", queueTime(customers1, 3, 1)); // should return 12
    printf("%d\n", queueTime(customers2, 4, 2)); // should return 10
    printf("%d\n", queueTime(customers3, 3, 2)); // should return 12
    printf("%d\n", queueTime(customers4, 5, 3)); // should return 6
    printf("%d\n", queueTime(customers5, 5, 5)); // should return 1

    return 0;
}