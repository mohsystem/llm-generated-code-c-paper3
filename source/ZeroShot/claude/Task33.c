
#include <stdio.h>
#include <stdlib.h>

int queueTime(const int *customers, int customersLength, int n) {
    int *tills = (int*)calloc(n, sizeof(int));
    
    for(int i = 0; i < customersLength; i++) {
        int minTill = 0;
        for(int j = 1; j < n; j++) {
            if(tills[j] < tills[minTill]) {
                minTill = j;
            }
        }
        tills[minTill] += customers[i];
    }
    
    int maxTime = tills[0];
    for(int i = 1; i < n; i++) {
        if(tills[i] > maxTime) {
            maxTime = tills[i];
        }
    }
    
    free(tills);
    return maxTime;
}

int main() {
    // Test case 1
    int customers1[] = {5,3,4};
    printf("%d\\n", queueTime(customers1, 3, 1)); // Expected: 12
    
    // Test case 2
    int customers2[] = {10,2,3,3};
    printf("%d\\n", queueTime(customers2, 4, 2)); // Expected: 10
    
    // Test case 3
    int customers3[] = {2,3,10};
    printf("%d\\n", queueTime(customers3, 3, 2)); // Expected: 12
    
    // Test case 4
    printf("%d\\n", queueTime(NULL, 0, 1)); // Expected: 0
    
    // Test case 5
    int customers5[] = {1,2,3,4,5};
    printf("%d\\n", queueTime(customers5, 5, 100)); // Expected: 5
    
    return 0;
}
