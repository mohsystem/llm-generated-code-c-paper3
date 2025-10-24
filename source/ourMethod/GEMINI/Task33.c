#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Calculates the total time required for all customers to check out.
 * 
 * @param customers An array of positive integers representing the time each customer needs.
 * @param customers_length The number of customers.
 * @param n The number of checkout tills.
 * @return The total time required.
 */
int queueTime(const int *customers, int customers_length, int n) {
    if (customers_length == 0) {
        return 0;
    }

    // Use calloc to initialize tills to 0
    int *tills = (int *)calloc(n, sizeof(int));
    if (tills == NULL) {
        // Handle memory allocation failure
        return -1; 
    }

    for (int i = 0; i < customers_length; i++) {
        // Find the till that will be free earliest
        int min_till_idx = 0;
        for (int j = 1; j < n; j++) {
            if (tills[j] < tills[min_till_idx]) {
                min_till_idx = j;
            }
        }
        // Assign the next customer to this till
        tills[min_till_idx] += customers[i];
    }

    // The total time is the time the last till finishes
    int max_time = 0;
    for (int i = 0; i < n; i++) {
        if (tills[i] > max_time) {
            max_time = tills[i];
        }
    }

    free(tills);
    return max_time;
}

int main() {
    // Test cases
    int customers1[] = {5, 3, 4};
    printf("%d\n", queueTime(customers1, 3, 1)); // Expected: 12

    int customers2[] = {10, 2, 3, 3};
    printf("%d\n", queueTime(customers2, 4, 2)); // Expected: 10

    int customers3[] = {2, 3, 10};
    printf("%d\n", queueTime(customers3, 3, 2)); // Expected: 12

    int customers4[] = {};
    printf("%d\n", queueTime(customers4, 0, 1)); // Expected: 0

    int customers5[] = {1, 2, 3, 4, 5};
    printf("%d\n", queueTime(customers5, 5, 100)); // Expected: 5

    return 0;
}