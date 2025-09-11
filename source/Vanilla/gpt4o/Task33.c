#include <stdio.h>

int queueTime(int customers[], int numCustomers, int n) {
    int tills[n];
    for (int i = 0; i < n; i++) {
        tills[i] = 0;
    }
    
    for (int i = 0; i < numCustomers; i++) {
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
    return maxTime;
}

int main() {
    int customers1[] = {5, 3, 4};
    int customers2[] = {10, 2, 3, 3};
    int customers3[] = {2, 3, 10};
    int customers4[] = {1, 2, 3, 4, 5};
    int customers5[] = {};
    
    printf("%d\n", queueTime(customers1, 3, 1)); // 12
    printf("%d\n", queueTime(customers2, 4, 2)); // 10
    printf("%d\n", queueTime(customers3, 3, 2)); // 12
    printf("%d\n", queueTime(customers4, 5, 2)); // 9
    printf("%d\n", queueTime(customers5, 0, 1)); // 0
    
    return 0;
}