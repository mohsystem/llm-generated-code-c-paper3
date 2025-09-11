
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    
    int x = nums1Size;
    int y = nums2Size;
    int low = 0;
    int high = x;
    
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;
        
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == x) ? INT_MAX : nums1[partitionX];
        
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == y) ? INT_MAX : nums2[partitionY];
        
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((x + y) % 2 == 0) {
                return ((double)fmax(maxLeftX, maxLeftY) + 
                        fmin(minRightX, minRightY)) / 2.0;
            } else {
                return (double)fmax(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return -1;  // Error case
}

int main() {
    // Test case 1
    int nums1_1[] = {1,3};
    int nums2_1[] = {2};
    printf("%.5f\\n", findMedianSortedArrays(nums1_1, 2, nums2_1, 1));  // 2.00000
    
    // Test case 2
    int nums1_2[] = {1,2};
    int nums2_2[] = {3,4};
    printf("%.5f\\n", findMedianSortedArrays(nums1_2, 2, nums2_2, 2));  // 2.50000
    
    // Test case 3
    int nums2_3[] = {1};
    printf("%.5f\\n", findMedianSortedArrays(NULL, 0, nums2_3, 1));  // 1.00000
    
    // Test case 4
    int nums1_4[] = {2};
    printf("%.5f\\n", findMedianSortedArrays(nums1_4, 1, NULL, 0));  // 2.00000
    
    // Test case 5
    int nums1_5[] = {1,2,3,4};
    int nums2_5[] = {5,6,7,8};
    printf("%.5f\\n", findMedianSortedArrays(nums1_5, 4, nums2_5, 4));  // 4.50000
    
    return 0;
}
