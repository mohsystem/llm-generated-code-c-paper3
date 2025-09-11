#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int queueTime(int customers[], int customerCount, int n) {
    int *tills = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < customerCount; ++i) {
        qsort(tills, n, sizeof(int), compare);
        tills[0] += customers[i];
    }
    int maxTime = 0;
    for (int i = 0; i < n; ++i) {
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

    int customers4[] = {1, 2, 3, 4, 5};
    printf("%d\n", queueTime(customers4, 5, 1)); // 15

    int customers5[] = {};
    printf("%d\n", queueTime(customers5, 0, 1)); // 0

    return 0;
}