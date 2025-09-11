
#include <stdio.h>
#include <stdlib.h>

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* result = (int*)malloc(numsSize * sizeof(int));
    
    for(int i = 0; i < numsSize; i++) {
        int count = 0;
        for(int j = i+1; j < numsSize; j++) {
            if(nums[j] < nums[i]) {
                count++;
            }
        }
        result[i] = count;
    }
    
    return result;
}

int main() {
    // Test case 1
    int nums1[] = {5,2,6,1};
    int returnSize1;
    int* result1 = countSmaller(nums1, 4, &returnSize1);
    for(int i = 0; i < returnSize1; i++) printf("%d ", result1[i]);
    printf("\\n");
    free(result1);
    
    // Test case 2
    int nums2[] = {-1};
    int returnSize2;
    int* result2 = countSmaller(nums2, 1, &returnSize2);
    for(int i = 0; i < returnSize2; i++) printf("%d ", result2[i]);
    printf("\\n");
    free(result2);
    
    // Test case 3
    int nums3[] = {-1,-1};
    int returnSize3;
    int* result3 = countSmaller(nums3, 2, &returnSize3);
    for(int i = 0; i < returnSize3; i++) printf("%d ", result3[i]);
    printf("\\n");
    free(result3);
    
    // Test case 4
    int nums4[] = {1,2,3,4};
    int returnSize4;
    int* result4 = countSmaller(nums4, 4, &returnSize4);
    for(int i = 0; i < returnSize4; i++) printf("%d ", result4[i]);
    printf("\\n");
    free(result4);
    
    // Test case 5
    int nums5[] = {4,3,2,1};
    int returnSize5;
    int* result5 = countSmaller(nums5, 4, &returnSize5);
    for(int i = 0; i < returnSize5; i++) printf("%d ", result5[i]);
    printf("\\n");
    free(result5);
    
    return 0;
}
