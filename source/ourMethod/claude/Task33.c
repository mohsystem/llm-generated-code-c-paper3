
#include <stdio.h>
#include <stdlib.h>

int queueTime(const int* customers, int customersLength, int n) {
    if (customers == NULL || customersLength == 0 || n <= 0) {
        return 0;
    }
    
    // Initialize array to track time at each till
    int* tills = (int*)calloc(n, sizeof(int));
    if (tills == NULL) {
        return 0; // Memory allocation failed
    }
    
    // Assign customers to tills
    for (int i = 0; i < customersLength; i++) {
        // Find till with minimum time and add new customer
        int minIndex = 0;
        for (int j = 1; j < n; j++) {
            if (tills[j] < tills[minIndex]) {
                minIndex = j;
            }
        }
        tills[minIndex] += customers[i];
    }
    
    // Find maximum time among all tills
    int maxTime = tills[0];
    for (int i = 1; i < n; i++) {
        if (tills[i] > maxTime) {
            maxTime = tills[i];
        }
    }
    
    free(tills);
    return maxTime;
}

int main() {
    // Test cases
    int test1[] = {5,3,4};
    printf("%d\\n", queueTime(test1, 3, 1));  // Should return 12
    
    int test2[] = {10,2,3,3};
    printf("%d\\n", queueTime(test2, 4, 2));  // Should return 10
    
    int test3[] = {2,3,10};
    printf("%d\\n", queueTime(test3, 3, 2));  // Should return 12
    
    printf("%d\\n", queueTime(NULL, 0, 1));  // Should return 0
    
    int test5[] = {1,2,3,4,5};
    printf("%d\\n", queueTime(test5, 5, 3));  // Should return 6
    
    return 0;
}
