#include <stdio.h>
#include <stdlib.h>

// Implementation using a simple approach for smaller arrays
// For larger arrays, a hashmap approach would be more efficient

int findOddOccurrence(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count % 2 != 0) {
            return arr[i];
        }
    }
    return -1; // Should not be reached as per the problem statement
}


int main() {
    int test1[] = {7};
    int test2[] = {0};
    int test3[] = {1, 1, 2};
    int test4[] = {0, 1, 0, 1, 0};
    int test5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};

    printf("%d\n", findOddOccurrence(test1, sizeof(test1)/sizeof(test1[0]))); // Expected: 7
    printf("%d\n", findOddOccurrence(test2, sizeof(test2)/sizeof(test2[0]))); // Expected: 0
    printf("%d\n", findOddOccurrence(test3, sizeof(test3)/sizeof(test3[0]))); // Expected: 2
    printf("%d\n", findOddOccurrence(test4, sizeof(test4)/sizeof(test4[0]))); // Expected: 0
    printf("%d\n", findOddOccurrence(test5, sizeof(test5)/sizeof(test5[0]))); // Expected: 4
     return 0;

}