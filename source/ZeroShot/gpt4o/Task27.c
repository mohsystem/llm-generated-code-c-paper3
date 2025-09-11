#include <stdio.h>

int findOutlier(const int* array, int length) {
    int countEven = 0, countOdd = 0, lastEven = 0, lastOdd = 0;
    
    for (int i = 0; i < length; i++) {
        if (array[i] % 2 == 0) {
            countEven++;
            lastEven = array[i];
        } else {
            countOdd++;
            lastOdd = array[i];
        }
        
        if (countEven > 1 && countOdd == 1) return lastOdd;
        if (countOdd > 1 && countEven == 1) return lastEven;
    }
    
    return 0; // Should never reach here if input is correct
}

int main() {
    int array1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int array2[] = {160, 3, 1719, 19, 11, 13, -21};
    int array3[] = {1, 2, 3};
    int array4[] = {4, 1, 3, 5, 7};
    int array5[] = {2, 6, 8, -10, 3};

    printf("%d\n", findOutlier(array1, 8)); // 11
    printf("%d\n", findOutlier(array2, 7)); // 160
    printf("%d\n", findOutlier(array3, 3)); // 2
    printf("%d\n", findOutlier(array4, 5)); // 4
    printf("%d\n", findOutlier(array5, 5)); // 3

    return 0;
}