#include <stdio.h>
#include <stdlib.h>

int queueTime(int* customers, int size, int n) {
    if (n == 0) n = 1;
    int* tills = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < size; i++) {
        int minIdx = 0;
        for (int j = 1; j < n; j++) {
            if (tills[j] < tills[minIdx]) minIdx = j;
        }
        tills[minIdx] += customers[i];
    }
    int max = tills[0];
    for (int i = 1; i < n; i++) {
        if (tills[i] > max) max = tills[i];
    }
    free(tills);
    return max;
}

int main() {
    int customers1[] = {5, 3, 4};
    int customers2[] = {10, 2, 3, 3};
    int customers3[] = {2, 3, 10};
    int customers4[] = {1, 2, 3, 4};
    int customers5[] = {1, 2, 3, 4, 5};

    printf("%d\n", queueTime(customers1, 3, 1)); // should return 12
    printf("%d\n", queueTime(customers2, 4, 2)); // should return 10
    printf("%d\n", queueTime(customers3, 3, 2)); // should return 12
    printf("%d\n", queueTime(customers4, 4, 1)); // should return 10
    printf("%d\n", queueTime(customers5, 5, 100)); // should return 5

    return 0;
}