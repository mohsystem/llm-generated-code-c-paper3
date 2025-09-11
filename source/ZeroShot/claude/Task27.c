
#include <stdio.h>

int findOutlier(const int integers[], int length) {
    int evenCount = 0;
    int firstThree = (length < 3) ? length : 3;
    
    for(int i = 0; i < firstThree; i++) {
        if(integers[i] % 2 == 0) evenCount++;
    }
    
    int isEvenArray = evenCount >= 2;
    
    for(int i = 0; i < length; i++) {
        if(isEvenArray && integers[i] % 2 != 0) return integers[i];
        if(!isEvenArray && integers[i] % 2 == 0) return integers[i];
    }
    return 0;
}

int main() {
    // Test cases
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {1, 3, 5, 7, 9, 10, 11};
    int test4[] = {2, 4, 6, 8, 10, 11, 12};
    int test5[] = {-3, -5, -7, -99, 0, -11};
    
    printf("%d\\n", findOutlier(test1, 8));  // Should return 11
    printf("%d\\n", findOutlier(test2, 7));  // Should return 160
    printf("%d\\n", findOutlier(test3, 7));  // Should return 10
    printf("%d\\n", findOutlier(test4, 7));  // Should return 11
    printf("%d\\n", findOutlier(test5, 6));  // Should return 0
    
    return 0;
}
