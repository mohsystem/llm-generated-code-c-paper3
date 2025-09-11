
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // Ensure nums1 is the smaller array
    if (nums1Size > nums2Size) {
        int* temp = nums1;
        nums1 = nums2;
        nums2 = temp;
        int tempSize = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tempSize;
    }
    
    int low = 0;
    int high = nums1Size;
    
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (nums1Size + nums2Size + 1) / 2 - partitionX;
        
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == nums1Size) ? INT_MAX : nums1[partitionX];
        
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == nums2Size) ? INT_MAX : nums2[partitionY];
        
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((nums1Size + nums2Size) % 2 == 0) {
                return ((double)fmax(maxLeftX, maxLeftY) + fmin(minRightX, minRightY)) / 2.0;
            } else {
                return fmax(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return 0.0; // Error case
}

int main() {
    // Test case 1
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%.5f\\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // Expected: 2.00000
    
    // Test case 2
    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%.5f\\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // Expected: 2.50000
    
    // Test case 3
    int nums5[] = {1};
    printf("%.5f\\n", findMedianSortedArrays(NULL, 0, nums5, 1)); // Expected: 1.00000
    
    // Test case 4
    int nums6[] = {2};
    printf("%.5f\\n", findMedianSortedArrays(nums6, 1, NULL, 0)); // Expected: 2.00000
    
    // Test case 5
    int nums7[] = {1, 2, 3, 4, 5};
    int nums8[] = {6, 7, 8, 9, 10};
    printf("%.5f\\n", findMedianSortedArrays(nums7, 5, nums8, 5)); // Expected: 5.50000
    
    return 0;
}
