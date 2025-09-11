#include <stdio.h>

int findOutlier(int arr[], int len) {
    int evenCount = 0;
    for (int i = 0; i < 3; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        }
    }

    int isEvenOutlier = evenCount < 2;

    for (int i = 0; i < len; i++) {
        if (isEvenOutlier) {
            if (arr[i] % 2 != 0) {
                return arr[i];
            }
        } else {
            if (arr[i] % 2 == 0) {
                return arr[i];
            }
        }
    }

    return 0; // Should not reach here
}

int main() {
    int arr1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    printf("%d\n", findOutlier(arr1, 8)); // 11

    int arr2[] = {160, 3, 1719, 19, 11, 13, -21};
    printf("%d\n", findOutlier(arr2, 7)); // 160

    int arr3[] = {1, 1, 2};
    printf("%d\n", findOutlier(arr3, 3)); // 2
    
    int arr4[] = {2, 6, 8, 10, 3};
    printf("%d\n", findOutlier(arr4, 5)); // 3

    int arr5[] = {1, 3, 5, 7, 8, 9};
    printf("%d\n", findOutlier(arr5, 6)); // 8

    return 0;
}