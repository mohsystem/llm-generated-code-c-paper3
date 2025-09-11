#include <stdio.h>
#include <stdlib.h>

int queueTime(int* customers, int n, int customersLen) {
    int* tills = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < customersLen; i++) {
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
    int customers1[] = {5,3,4};
    printf("%d\n", queueTime(customers1, 1, 3)); // should return 12
    int customers2[] = {10,2,3,3};
    printf("%d\n", queueTime(customers2, 2, 4)); // should return 10
    int customers3[] = {2,3,10};
    printf("%d\n", queueTime(customers3, 2, 3)); // should return 12
    return 0;
}