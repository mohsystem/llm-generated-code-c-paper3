#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int m = nums1Size;
    int n = nums2Size;
    if (m > n) {
        int* temp = nums1;
        nums1 = nums2;
        nums2 = temp;
        int tmp = m;
        m = n;
        n = tmp;
    }
    int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
    while (iMin <= iMax) {
        int i = (iMin + iMax) / 2;
        int j = halfLen - i;
        if (i < iMax && nums2[j-1] > nums1[i]){
            iMin = i + 1;
        }
        else if (i > iMin && nums1[i-1] > nums2[j]) {
            iMax = i - 1;
        }
        else {
            int maxLeft = 0;
            if (i == 0) { maxLeft = nums2[j-1]; }
            else if (j == 0) { maxLeft = nums1[i-1]; }
            else { maxLeft = (nums1[i-1] > nums2[j-1]) ? nums1[i-1] : nums2[j-1]; }
            if ( (m + n) % 2 == 1 ) { return maxLeft; }

            int minRight = 0;
            if (i == m) { minRight = nums2[j]; }
            else if (j == n) { minRight = nums1[i]; }
            else { minRight = (nums1[i] < nums2[j]) ? nums1[i] : nums2[j]; }

            return (maxLeft + minRight) / 2.0;
        }
    }
    return 0.0;
}

int main() {
    int nums1[] = {1,3};
    int nums2[] = {2};
    printf("%f\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // 2.000000
    int nums3[] = {1,2};
    int nums4[] = {3,4};
    printf("%f\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // 2.500000
    return 0;
}