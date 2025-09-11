#include <stdio.h>

int findOutlier(const int* numbers, int length) {
    int evenCount = 0, oddCount = 0, lastEven = 0, lastOdd = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] % 2 == 0) {
            evenCount++;
            lastEven = numbers[i];
        } else {
            oddCount++;
            lastOdd = numbers[i];
        }
        if (evenCount > 1 && oddCount > 0) return lastOdd;
        if (oddCount > 1 && evenCount > 0) return lastEven;
    }
    return 0;
}

int main() {
    int array1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int array2[] = {160, 3, 1719, 19, 11, 13, -21};
    int array3[] = {1, 3, 5, 7, 2};
    int array4[] = {6, 8, 10, 12, 3};
    int array5[] = {-2, -4, -6, -8, -11};
    
    printf("%d\n", findOutlier(array1, 8));
    printf("%d\n", findOutlier(array2, 7));
    printf("%d\n", findOutlier(array3, 5));
    printf("%d\n", findOutlier(array4, 5));
    printf("%d\n", findOutlier(array5, 5));
    
    return 0;
}