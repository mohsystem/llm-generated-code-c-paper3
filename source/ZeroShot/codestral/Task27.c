#include <stdio.h>

int findOutlier(int arr[], int n) {
    int oddCount = 0, evenCount = 0, oddNum = 0, evenNum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
            evenNum = arr[i];
        } else {
            oddCount++;
            oddNum = arr[i];
        }
    }
    return oddCount == 1 ? oddNum : evenNum;
}

int main() {
    int arr1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int arr2[] = {160, 3, 1719, 19, 11, 13, -21};
    printf("%d\n", findOutlier(arr1, 8)); // 11
    printf("%d\n", findOutlier(arr2, 7)); // 160
    return 0;
}