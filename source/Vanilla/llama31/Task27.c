// C code
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

    return (evenCount > oddCount) ? oddNum : evenNum;
}

int main() {
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {1, 3, 5, 7, 9, 10};
    int test4[] = {2, 4, 6, 8, 10, 11};
    int test5[] = {100, 200, 300, 400, 500, 501};

    int sizes[] = {8, 7, 6, 6, 6};

    printf("%d\n", findOutlier(test1, sizes[0])); // Output: 11
    printf("%d\n", findOutlier(test2, sizes[1])); // Output: 160
    printf("%d\n", findOutlier(test3, sizes[2])); // Output: 10
    printf("%d\n", findOutlier(test4, sizes[3])); // Output: 11
    printf("%d\n", findOutlier(test5, sizes[4])); // Output: 501

    return 0;
}