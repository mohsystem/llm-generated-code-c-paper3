
#include <stdio.h>

int findOutlier(const int integers[], int size) {
    int evenCount = 0;
    
    for(int i = 0; i < 3; i++) {
        if(integers[i] % 2 == 0)
            evenCount++;
    }
    
    int isEvenArray = evenCount >= 2;
    
    for(int i = 0; i < size; i++) {
        if(isEvenArray && integers[i] % 2 != 0)
            return integers[i];
        if(!isEvenArray && integers[i] % 2 == 0)
            return integers[i];
    }
    return 0;
}

int main() {
    // Test cases
    int arr1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int arr2[] = {160, 3, 1719, 19, 11, 13, -21};
    int arr3[] = {1, 2, 3};
    int arr4[] = {2, 6, 8, 10, 3};
    int arr5[] = {1, 1, 0, 1, 1};
    
    printf("%d\\n", findOutlier(arr1, 8));  // 11
    printf("%d\\n", findOutlier(arr2, 7));  // 160
    printf("%d\\n", findOutlier(arr3, 3));  // 2
    printf("%d\\n", findOutlier(arr4, 5));  // 3
    printf("%d\\n", findOutlier(arr5, 5));  // 0
    
    return 0;
}
