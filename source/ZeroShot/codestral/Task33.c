#include <stdio.h>
#include <limits.h>

int queueTime(int customers[], int n, int size) {
    int tills[n];
    for (int i = 0; i < n; i++) {
        tills[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        int minTime = INT_MAX;
        int minIndex = 0;
        for (int j = 0; j < n; j++) {
            if (tills[j] < minTime) {
                minTime = tills[j];
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
    return maxTime;
}

int main() {
    int customers1[] = {5,3,4};
    int n1 = 1;
    printf("%d\n", queueTime(customers1, n1, sizeof(customers1)/sizeof(customers1[0]))); // should return 12

    int customers2[] = {10,2,3,3};
    int n2 = 2;
    printf("%d\n", queueTime(customers2, n2, sizeof(customers2)/sizeof(customers2[0]))); // should return 10

    int customers3[] = {2,3,10};
    int n3 = 2;
    printf("%d\n", queueTime(customers3, n3, sizeof(customers3)/sizeof(customers3[0]))); // should return 12

    return 0;
}