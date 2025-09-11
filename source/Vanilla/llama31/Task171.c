#include <stdio.h>

int countReversePairs(int nums[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] > 2 * nums[j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int nums2[] = {2, 4, 3, 5, 1};
    int nums3[] = {3, 2, 4, 5, 1, 20};
    int nums4[] = {1, 2, 3, 4, 5};
    int nums5[] = {5, 4, 3, 2, 1};

    printf("Reverse pairs for nums1: %d\n", countReversePairs(nums1, 5));
    printf("Reverse pairs for nums2: %d\n", countReversePairs(nums2, 5));
    printf("Reverse pairs for nums3: %d\n", countReversePairs(nums3, 6));
    printf("Reverse pairs for nums4: %d\n", countReversePairs(nums4, 5));
    printf("Reverse pairs for nums5: %d\n", countReversePairs(nums5, 5));

    return 0;
}