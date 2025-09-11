#include <stdio.h>
#include <stdlib.h>

// Function to find the length of the longest consecutive subsequence
int longestConsecutive(int* nums, int n) {
    if (n == 0) return 0;

    // Create a hash set
    int* hash_set = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        hash_set[i] = 0;
    }

    // Populate the hash set
    for (int i = 0; i < n; ++i) {
        hash_set[nums[i]] = 1;
    }

    int longest_streak = 0;
    for (int i = 0; i < n; ++i) {
        if (hash_set[nums[i] - 1] == 0) {
            int current_num = nums[i];
            int current_streak = 1;
            while (hash_set[current_num + 1] == 1) {
                current_num += 1;
                current_streak += 1;
            }
            longest_streak = (longest_streak > current_streak) ? longest_streak : current_streak;
        }
    }

    free(hash_set);
    return longest_streak;
}

int main() {
    int nums1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int nums2[] = {1, 2, 3, 10, 11, 15};
    int nums3[] = {5, 4, 2, 1};
    int nums4[] = {3, 5, 7, 10, 15};
    int nums5[] = {};

    printf("Length of the Longest consecutive subsequence is %d\n", longestConsecutive(nums1, sizeof(nums1)/sizeof(nums1[0]))); // 5
    printf("Length of the Longest consecutive subsequence is %d\n", longestConsecutive(nums2, sizeof(nums2)/sizeof(nums2[0]))); // 3
    printf("Length of the Longest consecutive subsequence is %d\n", longestConsecutive(nums3, sizeof(nums3)/sizeof(nums3[0]))); // 2
    printf("Length of the Longest consecutive subsequence is %d\n", longestConsecutive(nums4, sizeof(nums4)/sizeof(nums4[0]))); // 1
    printf("Length of the Longest consecutive subsequence is %d\n", longestConsecutive(nums5, sizeof(nums5)/sizeof(nums5[0]))); // 0

    return 0;
}