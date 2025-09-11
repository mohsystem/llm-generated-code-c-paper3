
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if(nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    
    int low = 0;
    int high = nums1Size;
    int combinedLength = nums1Size + nums2Size;
    
    while(low <= high) {
        int partitionX = (low + high)/2;
        int partitionY = (combinedLength + 1)/2 - partitionX;
        
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == nums1Size) ? INT_MAX : nums1[partitionX];
        
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == nums2Size) ? INT_MAX : nums2[partitionY];
        
        if(maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if(combinedLength % 2 == 0) {
                return ((double)fmax(maxLeftX, maxLeftY) + fmin(minRightX, minRightY))/2;
            } else {
                return (double)fmax(maxLeftX, maxLeftY);
            }
        }
        else if(maxLeftX > minRightY) {
            high = partitionX - 1;
        }
        else {
            low = partitionX + 1;
        }
    }
    return 0;
}

int main() {
    // Test case 1
    int nums1[] = {1,3};
    int nums2[] = {2};
    printf("Test 1: %f\\n", findMedianSortedArrays(nums1, 2, nums2, 1));  // Expected: 2.0
    
    // Test case 2
    int nums3[] = {1,2};
    int nums4[] = {3,4};
    printf("Test 2: %f\\n", findMedianSortedArrays(nums3, 2, nums4, 2));  // Expected: 2.5
    
    // Test case 3
    int nums5[] = {0,0};
    int nums6[] = {0,0};
    printf("Test 3: %f\\n", findMedianSortedArrays(nums5, 2, nums6, 2));  // Expected: 0.0
    
    // Test case 4
    int nums8[] = {1};
    printf("Test 4: %f\\n", findMedianSortedArrays(NULL, 0, nums8, 1));  // Expected: 1.0
    
    // Test case 5
    int nums9[] = {2};
    printf("Test 5: %f\\n", findMedianSortedArrays(nums9, 1, NULL, 0));  // Expected: 2.0
    
    return 0;
}
