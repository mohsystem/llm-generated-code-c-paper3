#include <stdio.h>
#include <stdlib.h>

// Structure to represent a tuple of two integers
typedef struct {
    int index1;
    int index2;
} Tuple;

// Function to find two different items in the array that sum to the target value
Tuple two_sum(int nums[], int size, int target) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {  // Start j from i+1 to avoid duplicate pairs and self-addition.
            if (nums[i] + nums[j] == target) {
                Tuple result = {i, j};
                return result;
            }
        }
    }
    Tuple result = {-1, -1}; // Return {-1, -1} if no such pair is found.  This shouldn't happen based on the given constraints
    return result;
}

int main() {
    int nums1[] = {1, 2, 3};
    Tuple result1 = two_sum(nums1, 3, 4);
    printf("(%d, %d)\n", result1.index1, result1.index2);

    int nums2[] = {3, 2, 4};
    Tuple result2 = two_sum(nums2, 3, 6);
    printf("(%d, %d)\n", result2.index1, result2.index2);


    int nums3[] = {10, 20, 30, 40};
    Tuple result3 = two_sum(nums3, 4, 50);
    printf("(%d, %d)\n", result3.index1, result3.index2);

    int nums4[] = {-1, -2, -3, -4};
    Tuple result4 = two_sum(nums4, 4, -5);
    printf("(%d, %d)\n", result4.index1, result4.index2);

    int nums5[] = {2, 7, 11, 15};
    Tuple result5 = two_sum(nums5, 4, 9);
    printf("(%d, %d)\n", result5.index1, result5.index2);

    return 0;
}