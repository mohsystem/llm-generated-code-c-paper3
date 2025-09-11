
#include <stdio.h>

int findOutlier(const int integers[], int length) {
    // Input validation
    if(length < 3) {
        return 0;
    }
    
    // Count first 3 elements to determine array type
    int evenCount = 0;
    for(int i = 0; i < 3; i++) {
        if(integers[i] % 2 == 0) {
            evenCount++;
        }
    }
    
    // Determine if array is mostly even or odd
    int isEvenArray = evenCount >= 2;
    
    // Find outlier based on array type
    for(int i = 0; i < length; i++) {
        if(isEvenArray && integers[i] % 2 != 0) {
            return integers[i]; // Return odd outlier
        } else if(!isEvenArray && integers[i] % 2 == 0) {
            return integers[i]; // Return even outlier
        }
    }
    
    return 0; // Should never reach here given problem constraints
}

int main() {
    // Test cases
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {3, 7, 9, 5, 2, 13};
    int test4[] = {2, 6, 8, 3, 10, 14};
    int test5[] = {1, 3, 5, 7, 8, 9, 11};
    
    printf("%d\\n", findOutlier(test1, 8)); // Should return 11
    printf("%d\\n", findOutlier(test2, 7)); // Should return 160
    printf("%d\\n", findOutlier(test3, 6)); // Should return 2
    printf("%d\\n", findOutlier(test4, 6)); // Should return 3
    printf("%d\\n", findOutlier(test5, 7)); // Should return 8
    
    return 0;
}
