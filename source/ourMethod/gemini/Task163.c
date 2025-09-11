#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int longestRun(int nums[], int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    qsort(nums, n, sizeof(int), compare);

    int longest = 1;
    int current = 1;

    for (int i = 1; i < n; i++) {
        if (nums[i] == nums[i - 1] + 1) {
            current++;
        } else if (nums[i] != nums[i - 1]) {
            if (current > longest) {
                longest = current;
            }
            current = 1;
        }
    }

    if (current > longest) {
        longest = current;
    }
    return longest;
}

int main() {
    int nums1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    printf("%d\n", longestRun(nums1, sizeof(nums1) / sizeof(nums1[0]))); // 5

    int nums2[] = {1, 2, 3, 10, 11, 15};
    printf("%d\n", longestRun(nums2, sizeof(nums2) / sizeof(nums2[0]))); // 3

    int nums3[] = {5, 4, 2, 1};
    printf("%d\n", longestRun(nums3, sizeof(nums3) / sizeof(nums3[0]))); // 2

    int nums4[] = {3, 5, 7, 10, 15};
    printf("%d\n", longestRun(nums4, sizeof(nums4) / sizeof(nums4[0]))); // 1

    int nums5[] = {};
    printf("%d\n", longestRun(nums5, sizeof(nums5) / sizeof(nums5[0]))); // 0

    return 0;
}