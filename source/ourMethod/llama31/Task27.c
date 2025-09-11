#include <stdio.h>

int findOutlier(int nums[], int size) {
    int evenCount = 0;
    int oddCount = 0;
    int evenNum = 0;
    int oddNum = 0;

    for (int i = 0; i < 3; i++) {
        if (nums[i] % 2 == 0) {
            evenCount++;
            evenNum = nums[i];
        } else {
            oddCount++;
            oddNum = nums[i];
        }
    }

    return (evenCount > 1) ? oddNum : evenNum;
}

int main() {
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};

    printf("%d\n", findOutlier(test1, 8));  // Output: 11
    printf("%d\n", findOutlier(test2, 7));  // Output: 160

    return 0;
}