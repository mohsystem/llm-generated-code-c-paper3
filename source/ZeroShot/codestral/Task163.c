#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int longestRun(int nums[], int size) {
    qsort(nums, size, sizeof(int), cmp);

    int longestSequence = 1;
    int currentStreak = 1;

    for (int i = 1; i < size; i++) {
        if (nums[i] == nums[i - 1] + 1) {
            currentStreak++;
        } else if (nums[i] != nums[i - 1]) {
            longestSequence = (currentStreak > longestSequence) ? currentStreak : longestSequence;
            currentStreak = 1;
        }
    }

    return (currentStreak > longestSequence) ? currentStreak : longestSequence;
}

int main() {
    int nums1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int nums2[] = {1, 2, 3, 10, 11, 15};
    int nums3[] = {5, 4, 2, 1};
    int nums4[] = {3, 5, 7, 10, 15};

    printf("%d\n", longestRun(nums1, sizeof(nums1) / sizeof(nums1[0]))); // 5
    printf("%d\n", longestRun(nums2, sizeof(nums2) / sizeof(nums2[0]))); // 3
    printf("%d\n", longestRun(nums3, sizeof(nums3) / sizeof(nums3[0]))); // 2
    printf("%d\n", longestRun(nums4, sizeof(nums4) / sizeof(nums4[0]))); // 1

    return 0;
}