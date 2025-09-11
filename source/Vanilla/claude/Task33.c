
#include <stdio.h>
#include <stdlib.h>

int queueTime(const int *customers, int customersLength, int n) {
    int *tills = (int*)calloc(n, sizeof(int));
    
    for(int i = 0; i < customersLength; i++) {
        int minTillIndex = 0;
        for(int j = 1; j < n; j++) {
            if(tills[j] < tills[minTillIndex]) {
                minTillIndex = j;
            }
        }
        tills[minTillIndex] += customers[i];
    }
    
    int maxTime = 0;
    for(int i = 0; i < n; i++) {
        if(tills[i] > maxTime) {
            maxTime = tills[i];
        }
    }
    
    free(tills);
    return maxTime;
}

int main() {
    // Test case 1
    int test1[] = {5,3,4};
    printf("%d\\n", queueTime(test1, 3, 1));  // Expected: 12
    
    // Test case 2
    int test2[] = {10,2,3,3};
    printf("%d\\n", queueTime(test2, 4, 2));  // Expected: 10
    
    // Test case 3
    int test3[] = {2,3,10};
    printf("%d\\n", queueTime(test3, 3, 2));  // Expected: 12
    
    // Test case 4
    int test4[] = {1,2,3,4,5};
    printf("%d\\n", queueTime(test4, 5, 3));  // Expected: 5
    
    // Test case 5
    printf("%d\\n", queueTime(NULL, 0, 1));  // Expected: 0
    
    return 0;
}
