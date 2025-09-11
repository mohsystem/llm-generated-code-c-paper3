
#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* numbers, int numbersSize, int target) {
    int* result = (int*)malloc(2 * sizeof(int));
    
    for (int i = 0; i < numbersSize - 1; i++) {
        for (int j = i + 1; j < numbersSize; j++) {
            if (numbers[i] + numbers[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    return NULL;
}

int main() {
    // Test case 1
    int nums1[] = {1, 2, 3};
    int* result1 = twoSum(nums1, 3, 4);
    printf("%d,%d\\n", result1[0], result1[1]);  // 0,2
    free(result1);
    
    // Test case 2
    int nums2[] = {3, 2, 4};
    int* result2 = twoSum(nums2, 3, 6);
    printf("%d,%d\\n", result2[0], result2[1]);  // 1,2
    free(result2);
    
    // Test case 3
    int nums3[] = {2, 7, 11, 15};
    int* result3 = twoSum(nums3, 4, 9);
    printf("%d,%d\\n", result3[0], result3[1]);  // 0,1
    free(result3);
    
    // Test case 4
    int nums4[] = {3, 3};
    int* result4 = twoSum(nums4, 2, 6);
    printf("%d,%d\\n", result4[0], result4[1]);  // 0,1
    free(result4);
    
    // Test case 5
    int nums5[] = {-1, -2, -3, -4, -5};
    int* result5 = twoSum(nums5, 5, -8);
    printf("%d,%d\\n", result5[0], result5[1]);  // 2,4
    free(result5);
    
    return 0;
}
